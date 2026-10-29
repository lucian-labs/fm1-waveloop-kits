#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-only
"""Check packaged source hashes, local documentation links and SHAYPE parity."""
import hashlib
import json
import os
from pathlib import Path
import re
import shlex
import subprocess
import tempfile
import sys

ROOT = Path(__file__).resolve().parents[1]
provenance = json.loads((ROOT / 'provenance.json').read_text())
for item in provenance['files']:
    actual = hashlib.sha256((ROOT / item['path']).read_bytes()).hexdigest()
    assert actual == item['sha256'], item['path']
for doc in ROOT.rglob('*.md'):
    for target in re.findall(r'\]\(([^)]+)\)', doc.read_text()):
        if '://' in target or target.startswith('#'):
            continue
        assert (doc.parent / target.split('#')[0]).exists(), (doc, target)
manifest = json.loads((ROOT / 'distros/manifest.json').read_text())
for distro in manifest['distros']:
    assert re.fullmatch('[0-9a-f]{40}', distro['commit'])
    assert set(distro['seams']) == {'shape', 'persistent_songs', 'drums_808', 'drum_sequencer'}
    for paths in distro['seams'].values():
        assert all(not p.startswith('/') and '..' not in Path(p).parts for p in paths)
with tempfile.TemporaryDirectory(prefix='fm1-kits-') as tmp:
    binary = str(Path(tmp) / 'shape-test')
    subprocess.run(shlex.split(os.environ.get('CC', 'cc')) + [
        '-O1', '-w', '-Ireference/firmware/src', '-Ireference/tests',
        'reference/tests/arp_shape_test.c', '-o', binary], cwd=ROOT, check=True)
    result = subprocess.run([binary], text=True, capture_output=True)
    if result.returncode:
        print(result.stdout)
        print(result.stderr)
        raise SystemExit(result.returncode)
    print(result.stdout.strip().splitlines()[-1])
subprocess.run([sys.executable, str(ROOT / "tools/check_sequence_view.py")], check=True)
print(f"PASS: source hashes, local links, {len(manifest['distros'])} distro maps, SHAYPE parity")
