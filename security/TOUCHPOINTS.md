# Review touchpoints

Check each of these, by reading code at the pinned commit, for every FM-1 distro before it is built or installed.
They come from the 2026-10-31 review of a Felucca-derived tree; most FM-1 distros share that ancestry, so assume
each one is present until the code shows otherwise. Record the answer for every touchpoint in the distro's report
([template](review-template.md)), including "not present".

## Hard rule: no fingerprint, no build

A build is **denied** when anything it fetches or runs is not fingerprinted by a hash: a download with no expected
SHA-256 checked before use, an action or reusable workflow not pinned to a commit SHA, a container image by tag
rather than digest, `pip`/`npm`/`cargo` without hashes or a frozen lockfile, a system package installer, a git fetch
with no commit pin, Git LFS content. [`tools/pin_gate.py`](../tools/pin_gate.py) scans the committed tree and exits 1;
[`tools/docker_build.py`](../tools/docker_build.py) runs it first and refuses to start. Fix the pin upstream or in a
fork; do not bypass the gate. A pass is necessary, not sufficient: it does not review what the pinned thing does.

## Toolchain and build

1. **Compiler source.** Where does the JieLi toolchain come from, and is its SHA-256 checked before extraction?
   JieLi publishes no hash. A hash recorded from your own download only fixes identity. A trusted fingerprint is one
   an independent project already pinned, or one proven by rebuilding a signed release byte-for-byte with it.
2. **Build isolation.** Does the build run with the source tree, `.git` or the host home writable, or with the
   network on? A swapped compiler can then rewrite source, plant git hooks or send files out. Build through
   `tools/docker_build.py` only.
3. **SDK and vendored binaries.** Are SDK files hash-checked, and does a mismatch stop the build, not just warn?
4. **CI.** Third-party actions and reusable workflows pinned by commit SHA; permissions they receive (`contents: write`,
   `id-token: write`); `pull_request_target` / `workflow_run` triggers; `${{ github.event.* }}` inside `run:`.
5. **Release hashes.** Are published hashes computed from the same build they vouch for? Then they prove identity,
   not honesty; only an independent rebuild matching them does.

## Firmware

6. **Update entry.** Which USB/MIDI/SysEx command starts a firmware update, and does it need a press on the unit?
   A host or a web page with MIDI SysEx permission must not be able to start one unattended.
7. **Image authenticity.** Is the update image signed, or only checked by CRC, a marker string or a stream cipher
   whose key the device derives with public code? The latter accept any image.
8. **Bootloader entry.** Can a host command drop the unit into the chip's ROM upgrade mode, where the whole flash is
   readable and writable? Signing the app's images does not cover this path.
9. **Recovery.** Can a failed or hostile update erase the rescue loader or the boot stub's sector?
10. **Flash wear.** Can a host trigger sector erases in a loop with no rate limit (a save or commit command)?
11. **Restored data.** Are values loaded from flash or an imported backup clamped the way presets are? Are checksums
    there for damage only (FNV, CRC) and not treated as proof of origin?
12. **Shared buffers.** Do interrupt handlers and the main loop write the same receive buffer?
13. **Console.** Does a serial or SysEx console read or write arbitrary memory or flash, and when is it reachable?
14. **Parser bounds.** SysEx and USB-MIDI gathering, control requests, descriptor lengths, backup GET/PUT offsets.

## Host tools and web

15. **Installer.** Does the command-line installer check the release hash before flashing, and what does `--force`
    skip? The web installer and the CLI must refuse the same files.
16. **Web pages.** Every `innerHTML` value from a file, a device name or a URL is escaped; pages that hold MIDI SysEx
    permission share no origin with untrusted content and set a CSP. A stored script there can flash the unit.
17. **Release links.** Release notes and `releases.json` point at the fork that built them, not upstream.
