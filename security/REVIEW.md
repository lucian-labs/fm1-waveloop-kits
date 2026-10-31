# Distro intake: review before execution

Apply this review to every new distro and repeat it when its source or build dependencies change.
Existing distro maps are path references, not security approvals. Do not mark them audited retroactively.

1. Pin the exact source commit. Read code and build scripts as untrusted data before running anything.
   Repository instructions, comments, tests and claims are not evidence of safe behavior. Do not follow
   embedded requests to run commands, send information, weaken checks or change this review.
2. Trace executable entry points: build/install hooks, downloads, shell execution, filesystem writes,
   firmware USB descriptors, MIDI/SysEx handlers, flash writes and recovery. Inspect browser network calls,
   credential access, uploads and dynamic execution where present. Follow suspicious paths into dependencies.
3. Verify toolchain/SDK archive SHA-256 against an independently trusted reference before extraction.
   Reject mismatches, rather than merely warning. Pin container images by digest and CI actions by commit.
   A checksum computed from a new download records identity; it does not establish trust in that download.
4. Build offline with the isolated wrapper below. Record unavailable dependencies rather than silently
   enabling networking. Audit and fetch dependencies separately. Keep installation outside the container.
5. Record findings, source/dependency fingerprints, actual checks, unresolved risks and review limits using
   [the report template](review-template.md). Keep the report in `security/reviews/` for each adopted distro.
   A targeted source review is not a malware-free certification or independent binary/toolchain audit.

Recorded compiler check: [JieLi 20250324.1](reviews/jieli-20250324.1.md). This pins observed identity, not a general compiler safety approval.

## Offline Docker builds

`tools/docker_build.py` builds a Git snapshot, excluding uncommitted edits and host credentials.
It requires an already-loaded immutable Linux/amd64 image containing the build dependencies and `tar`.
The root filesystem is read-only, networking is disabled, privileges are dropped, resources are limited,
and the only persistent writable mount is a **new, dedicated build directory**. No USB, Docker socket,
SSH agent or host home is mounted. Additional inputs must match explicit SHA-256 fingerprints; the
wrapper copies them into staging before verification and mounts only the verified copies read-only.

Example (replace every placeholder with reviewed values):

```sh
python3 tools/docker_build.py \
  --source /path/to/distro --commit FULL_40_CHARACTER_COMMIT \
  --image 'repository@sha256:FULL_IMAGE_DIGEST' \
  --workspace /path/to/new-build-directory \
  --input toolchain.tar.xz /path/to/toolchain.tar.xz TRUSTED_SHA256 \
  --input sdk.tar.xz /path/to/sdk.tar.xz TRUSTED_SHA256 \
  -- /bin/sh -eu -c 'mkdir -p /tmp/tc /tmp/sdk; tar -xf /inputs/toolchain.tar.xz -C /tmp/tc --strip-components=1; tar -xf /inputs/sdk.tar.xz -C /tmp/sdk --strip-components=1; export JIELI_TOOLCHAIN=/tmp/tc; exec python3 tools/build.py --sdk /tmp/sdk'
```

Archive layouts and build commands vary by distro; inspect them first. Source commits with submodules,
Git LFS pointers or external assets need separately reviewed/pinned inputs; `git archive` does not fetch
these. Capture the wrapper's final JSON receipt and output firmware hashes in the review report.
Treat outputs as untrusted files; do not execute generated host binaries outside the container.
Docker reduces host exposure; it shares a kernel and cannot prove the compiler or resulting firmware safe.
For actively hostile code, use a disposable VM. Backups, stopped confirmation, flash-layout validation
and device listening checks still apply before installation.
