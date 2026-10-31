#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-only
"""Deny a distro build when anything it fetches or runs is not fingerprinted by a hash.

Reads the committed tree only (git objects, no checkout, nothing executed). Exit 0 ALLOWED,
1 DENIED, 2 usage error. A pass means every fetch site found is hash-pinned; it is not a review.
"""
import argparse
import json
import re
import subprocess
import sys

BUILD_FILE = re.compile(r'(^|/)(Makefile[^/]*|[^/]*\.(sh|bash|py|mk|cmake|ps1|bat|cmd)|CMakeLists\.txt|'
                        r'Dockerfile[^/]*|[^/]*\.dockerfile|requirements[^/]*\.txt|package\.json|'
                        r'\.github/workflows/[^/]+\.ya?ml|\.gitlab-ci\.yml|build\.gradle[^/]*)$')
HEX64 = re.compile(r'\b[0-9a-f]{64}\b')
HEX40 = re.compile(r'\b[0-9a-f]{40}\b')
SHA_CHECK = re.compile(r'sha256sum|shasum|hashlib\.sha256|sha256\(|Get-FileHash|--require-hashes|integrity')
HASH_SOURCE = re.compile(r'''\[["']sha256["']\]|\.get\(["']sha256["']|SHA256SUMS|\.sha256\b''')   # expected hash read from a committed manifest
RUNS = re.compile(r'subprocess|os\.system|check_call|check_output|Popen|\brun\(|urlopen\(|urlretrieve\(|requests\.get\(|httpx\.get\(')
FETCH = re.compile(r'\b(curl|wget|aria2c|Invoke-WebRequest|iwr|urlretrieve|urlopen|requests\.get|'
                   r'httpx\.get|Start-BitsTransfer)\b')
GIT_FETCH = re.compile(r'\bgit\s+(clone|fetch|pull|submodule\s+add)\b')
USES = re.compile(r'^\s*-?\s*uses:\s*["\']?([^"\'\s#]+)')
IMAGE = re.compile(r'(^\s*FROM\s+(?:--platform=\S+\s+)?(\S+))|(\bdocker\s+(?:run|pull|create)\b.*)|'
                   r'(^\s*(?:image|container):\s*["\']?([^"\'\s#{]+))|(\b[A-Z_]*IMAGE\s*=.*["\']([^"\']+)["\'])')
INSTALLER = re.compile(r'\b(apt(-get)?\s+install|apk\s+add|brew\s+install|choco\s+install|winget\s+install|'
                       r'pacman\s+-S|dnf\s+install|yum\s+install|go\s+(get|install)|rustup\b|'
                       r'emsdk\s+install|(?<![/\w])npx\s+[@\w]|pipx\s+install|conda\s+install)\b')
LOCK_NAME = re.compile(r'(^|/)[^/]*(lock|pins?|SHA256SUMS|\.sha256)[^/]*$', re.I)
PIP = re.compile(r'\bpip3?\s+install\b|\bpython3?\s+-m\s+pip\s+install\b')
NPM = re.compile(r'\b(npm\s+(install|i|add)\b|yarn\s+(add|install)\b|pnpm\s+(add|install|i)\b|npm\s+ci\b)')
CARGO = re.compile(r'\bcargo\s+install\b')


def git(source, *args):
    return subprocess.run(['git', '-C', source, *args], check=True, capture_output=True).stdout


def code_lines(text, path):
    hash_comment = not path.endswith(('.bat', '.cmd'))
    for n, line in enumerate(text.splitlines(), 1):
        s = line.strip()
        if not s or (hash_comment and s.startswith('#') and not s.startswith('#!')) or s.startswith('//'):
            continue
        yield n, line


def scan(source, commit):
    names = git(source, 'ls-tree', '-r', '--name-only', commit).decode().splitlines()
    tree = set(names)
    out = []
    # committed lock files that hold hashes: a script reading one by name and checking SHA-256 is pinned
    locks = set()
    for p in (p for p in names if LOCK_NAME.search(p)):
        try:
            if HEX64.search(git(source, 'show', f'{commit}:{p}').decode('utf-8', 'replace')):
                locks.add(p.rpartition('/')[2])
        except subprocess.CalledProcessError:
            pass

    def deny(rule, path, n, line, why):
        out.append({'rule': rule, 'file': path, 'line': n, 'text': line.strip()[:160], 'why': why})

    for path in (p for p in names if BUILD_FILE.search(p)):
        try:
            text = git(source, 'show', f'{commit}:{path}').decode('utf-8', 'replace')
        except subprocess.CalledProcessError:
            continue
        reads_lock = any(l in text for l in locks)
        verifies = bool(SHA_CHECK.search(text)) and bool(HEX64.search(text) or HASH_SOURCE.search(text) or reads_lock)
        python = path.endswith('.py')
        pins_commit = bool(HEX40.search(text)) or (reads_lock and 'checkout' in text)
        digest_from_lock = reads_lock and '@sha256:' in text
        workflow = path.startswith('.github/workflows/') or path == '.gitlab-ci.yml'   # nested copies never run
        if not workflow and ('.github/workflows/' in path or path.endswith('.gitlab-ci.yml')):
            continue
        if path.endswith('package.json'):
            if not any(p in tree for p in (path[:-len('package.json')] + l for l in
                                           ('package-lock.json', 'npm-shrinkwrap.json', 'pnpm-lock.yaml', 'yarn.lock'))):
                if re.search(r'"(dependencies|devDependencies)"\s*:\s*\{\s*"', text):
                    deny('npm', path, 1, 'package.json', 'dependencies with no lockfile (no integrity hashes)')
            continue
        if re.search(r'(^|/)requirements[^/]*\.txt$', path):
            for n, line in code_lines(text, path):
                if not line.strip().startswith('-') and '--hash=sha256:' not in line:
                    deny('pip', path, n, line, 'requirement without --hash=sha256')
            continue
        for n, line in code_lines(text, path):
            # prose names tools it never runs: Python counts only lines that execute, shell drops echoed/died hints
            run = (line if RUNS.search(line) else '') if python else re.sub(r'''\b(echo|printf|die|warn|fail|say)\s+(["']).*?\2''', '', line)
            if FETCH.search(run) and not verifies:
                deny('fetch', path, n, line, 'download with no SHA-256 check in this file')
            if GIT_FETCH.search(run) and not pins_commit:
                deny('git', path, n, line, 'git fetch with no 40-hex commit pin in this file')
            m = USES.match(line) if workflow else None
            if m and not m.group(1).startswith(('./', 'docker://')):
                ref = m.group(1).rpartition('@')[2]
                if not re.fullmatch(r'[0-9a-f]{40}', ref):
                    deny('action', path, n, line, 'action/reusable workflow not pinned to a commit SHA')
            if m and m.group(1).startswith('docker://') and '@sha256:' not in m.group(1):
                deny('image', path, n, line, 'container image not pinned by digest')
            im = IMAGE.search(line)
            if im and '@sha256:' not in line and not re.search(r'\bsha256:[0-9a-f]{64}\b', line) and not digest_from_lock:
                if im.group(2) and im.group(2).lower() == 'scratch':
                    pass
                elif im.group(1) or im.group(3) or (workflow and im.group(5)) or im.group(6):
                    deny('image', path, n, line, 'container image by tag, not by digest')
            if INSTALLER.search(run):
                deny('installer', path, n, line, 'package installer without hash-pinned packages')
            if PIP.search(run) and '--require-hashes' not in line:
                deny('pip', path, n, line, 'pip install without --require-hashes')
            if NPM.search(run):
                lock = any(l in tree for l in ('package-lock.json', 'npm-shrinkwrap.json', 'pnpm-lock.yaml', 'yarn.lock'))
                frozen = re.search(r'\bnpm\s+ci\b|--frozen-lockfile|--immutable', line)
                if not (lock and frozen):
                    deny('npm', path, n, line, 'npm/yarn/pnpm without a frozen lockfile install')
            if CARGO.search(run) and '--locked' not in line:
                deny('cargo', path, n, line, 'cargo install without --locked')
    if '.gitattributes' in tree and b'filter=lfs' in git(source, 'show', f'{commit}:.gitattributes'):
        deny('lfs', '.gitattributes', 1, 'filter=lfs', 'Git LFS content is outside the reviewed snapshot')
    seen, kept = {}, []
    for f in out:   # one line per file and rule: the first site, and how many more
        k = (f['rule'], f['file'])
        if k in seen:
            seen[k]['more'] += 1
        else:
            f['more'] = 0; seen[k] = f; kept.append(f)
    return kept


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--source', required=True)
    p.add_argument('--commit', required=True, help='Full reviewed Git commit')
    p.add_argument('--json', action='store_true')
    a = p.parse_args()
    if not re.fullmatch(r'[0-9a-f]{40}', a.commit):
        p.error('--commit must be a full 40-character Git commit')
    findings = scan(a.source, a.commit)
    if a.json:
        print(json.dumps({'commit': a.commit, 'decision': 'DENIED' if findings else 'ALLOWED', 'findings': findings}))
    else:
        for f in findings:
            more = f" (+{f['more']} more)" if f['more'] else ''
            print(f"DENY {f['rule']:9} {f['file']}:{f['line']}{more}  {f['why']}\n     {f['text']}")
        print(f"{'DENIED' if findings else 'ALLOWED'}: {len(findings)} unpinned input(s) at {a.commit}")
    sys.exit(1 if findings else 0)


if __name__ == '__main__':
    main()
