# Validation — 2026-10-28

- `python3 tools/check.py`: bundled SHAYPE fixtures pass; source SHA-256 hashes and local documentation links pass.
- All 18 distro manifests were checked against their exact GitHub commit trees. Every listed target path exists. This verifies paths, not feature compatibility.
- The sequencer patch applies cleanly to its recorded Switch Blade base and reproduces all 15 firmware/test files from the recorded target commit byte-for-byte.
- The patched tree’s `drum_seq_test.c` passes 33 checks. This host test used generated headers from the existing Switch Blade build; building the donor from source regenerates those headers.

No other distro was rebuilt or hardware-tested as part of packaging this kit. The Switch Blade feature was previously installed on a test unit; listening acceptance remains outstanding. No universal installer or cross-distro compatibility guarantee is provided.
