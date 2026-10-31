#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-only
"""Build a committed distro snapshot offline without mounting the host checkout."""
import argparse
import hashlib
import json
import os
from pathlib import Path
import re
import subprocess
import tempfile


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--source', type=Path, required=True)
    p.add_argument('--commit', required=True, help='Full reviewed Git commit')
    p.add_argument('--image', required=True, help='Local sha256 image ID or repository@sha256 digest')
    p.add_argument('--workspace', type=Path, required=True, help='New directory for source and build outputs')
    p.add_argument('--input', nargs=3, action='append', default=[], metavar=('NAME', 'FILE', 'SHA256'),
                   help='Mount a verified toolchain/SDK archive read-only at /inputs/NAME')
    p.add_argument('command', nargs=argparse.REMAINDER)
    a = p.parse_args()
    if not re.fullmatch(r'[0-9a-f]{40}', a.commit):
        p.error('--commit must be a full 40-character Git commit')
    if not re.fullmatch(r'(?:sha256:|[a-zA-Z0-9./:_-]+@sha256:)[0-9a-f]{64}', a.image):
        p.error('--image must be immutable, not a tag')
    command = a.command[1:] if a.command[:1] == ['--'] else a.command
    if not command:
        p.error('supply a build command after --')
    if os.getuid() == 0:
        p.error('run as a non-root host user')
    source = a.source.resolve(strict=True)
    inputs = []
    names = {'source.tar'}
    for name, filename, expected in a.input:
        if not re.fullmatch(r'[A-Za-z0-9][A-Za-z0-9._-]*', name) or name in names:
            p.error('input names must be unique simple filenames; source.tar is reserved')
        names.add(name)
        path = Path(filename).resolve(strict=True)
        if ',' in str(path):
            p.error('Docker mount paths cannot contain commas')
        if not re.fullmatch(r'[0-9a-f]{64}', expected):
            p.error('each input requires an expected SHA-256')
        inputs.append((name, path, expected))
    workspace = a.workspace.absolute()
    if ',' in str(workspace):
        p.error('Docker mount paths cannot contain commas')
    # mkdir is exclusive: never mount an existing checkout or overwrite previous outputs.
    workspace.mkdir(mode=0o700)
    with tempfile.TemporaryDirectory(prefix='fm1-offline-build-') as temp:
        staging = Path(temp)
        snapshot = staging / 'source.tar'
        with snapshot.open('wb') as out:
            subprocess.run(['git', '-C', str(source), 'archive', '--format=tar', a.commit],
                           stdout=out, check=True)
        verified = []
        # Copy first, then hash exactly the bytes Docker receives (not a mutable original).
        for name, original, expected in inputs:
            dest = staging / name
            digest = hashlib.sha256()
            with original.open('rb') as src, dest.open('xb') as dst:
                while block := src.read(1024 * 1024):
                    dst.write(block)
                    digest.update(block)
            if digest.hexdigest() != expected:
                raise SystemExit(f'Input fingerprint mismatch: {name}; build not started')
            verified.append({'name': name, 'sha256': expected})
        cmd = ['docker', 'run', '--rm', '--pull=never', '--platform=linux/amd64',
               '--network=none', '--read-only', '--cap-drop=ALL',
               '--security-opt=no-new-privileges', '--pids-limit=256', '--memory=4g', '--cpus=2',
               '--user', f'{os.getuid()}:{os.getgid()}', '--tmpfs', '/tmp:rw,nosuid,nodev,size=1g',
               '--mount', f'type=bind,src={workspace},dst=/work',
               '--mount', f'type=bind,src={staging},dst=/inputs,readonly',
               '--workdir=/work', '--env=HOME=/tmp', '--env=JIELI_DOCKER=0',
               '--entrypoint=/bin/sh', a.image, '-eu', '-c',
               'tar -xf /inputs/source.tar -C /work; exec "$@"', 'build', *command]
        result = subprocess.run(cmd)
        print(json.dumps({'commit': a.commit, 'image': a.image, 'inputs': verified,
                          'exit_code': result.returncode, 'workspace': str(workspace)}))
        raise SystemExit(result.returncode)


if __name__ == '__main__':
    main()
