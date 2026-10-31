# ChoralRoot — targeted source review, 2026-10-31

Source: ELI7VH/ChoralRootFM1, `fd99c3dfbc7ce61dd253082866c2ef53026e7ce4`.
Review: Codex; executable code/build paths inspected without treating instructions or comments as evidence.

- Traced compiler acquisition/use (`tools/get_toolchain.sh`, `tools/build.py`), two grain preview
  helpers, console command dispatch, firmware entry/USB paths and browser installer/network calls.
- Compiler URL is downloaded directly into `tar`, without an expected SHA-256. Build execution trusts
  the installed compiler. Container default is a mutable Debian tag. These remain unresolved.
- SDK files have expected SHA-256 values, but mismatches only print warnings and continue.
  This corrects an earlier description that implied enforcement. Change to fail-closed before adoption
  under the new build policy; separately establish trusted compiler/SDK fingerprints.
- `tools/grain_sketch.c` and `tools/grain_listen.c` interpolate an argument into a single-quoted
  `mkdir` shell command. An apostrophe can break quoting. Developer tools, not firmware runtime.
- Reviewed console dispatch exposes local diagnostic memory/flash reads and explicit bootloader entry.
  Reviewed browser installer downloads verify firmware hashes before installation; factory packs are
  fetched for the manager. No obvious malicious behavior found in the inspected paths.
- Build dependencies/vendor binaries were not independently audited. This was not a complete review
  of every source line, dependency, artifact or hardware behavior. No malware-free certification.

Decision: reviewed with unresolved findings. The earlier hardware trial is archived; this report does
not approve another installation. No firmware was built or installed as part of this policy change.
The separate Docker wrapper passed a live isolation smoke check using a local immutable Debian image:
`sha256:7c7b2c966bc9ee8cedfeef67e0e279108992c77681fa595db4a9d65c06ccc587`.
Non-root execution, read-only root/inputs, no IPv4 routes, no capabilities, no-new-privileges,
no mounted USB/socket, writable output and invalid-hash/tag rejection were checked.
A full distro build through that wrapper remains unverified pending reviewed dependency inputs.
