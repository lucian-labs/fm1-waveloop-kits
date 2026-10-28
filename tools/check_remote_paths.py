#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-only
"""Verify pinned GitHub source paths. Requires authenticated GitHub CLI (gh)."""
import concurrent.futures
import json
from pathlib import Path
import subprocess

root = Path(__file__).resolve().parents[1]
manifest = json.loads((root / 'distros/manifest.json').read_text())

def verify(distro):
    repo = distro['repository'].split('https://github.com/', 1)[1]
    endpoint = f"repos/{repo}/git/trees/{distro['commit']}?recursive=1"
    tree = json.loads(subprocess.check_output(['gh', 'api', endpoint], text=True))
    if tree.get('truncated'):
        raise RuntimeError(f'Truncated tree: {repo}')
    paths = {item['path'] for item in tree['tree'] if item['type'] == 'blob'}
    for files in distro['seams'].values():
        for path in files:
            if path not in paths:
                raise RuntimeError(f'Missing {repo}: {path}')
    return distro['id']

with concurrent.futures.ThreadPoolExecutor(max_workers=4) as pool:
    verified = list(pool.map(verify, manifest['distros']))
print(f'PASS: {len(verified)} pinned GitHub source trees')
