# Porting to another distro

A common FM-1 board does not imply a common firmware API. Start from a buildable source revision with its license and toolchain; record both before editing.

| Boundary | Contract to implement |
| --- | --- |
| Clock/events | One timing authority; internal/external clock, note lengths, reset and stop |
| Pattern state | Native track ownership, bounded arrays and explicit melodic/drum routing |
| Voices/banks | GM lane map, kit IDs, choke rules, sample rate and voice budget |
| UI | Native key/encoder IDs, page routing, gesture lifetime and draw budget |
| Storage | Versioned serialization, old defaults, CRC/atomic writes and allocated sectors |
| Resources | Linker flash/RAM report and worst-case audio cost with all tracks |

Port one feature at a time. For a Felucca-shaped tree, follow the pinned source map. For a different architecture, wrap the same behavioral contracts in its native modules; do not transplant an amalgamated engine wholesale.

## Security intake

Before executing a new distro’s tools, complete the [code audit and offline Docker build review](security/REVIEW.md). Repeat for changed source or build dependencies. Record actual findings and review limits; a path map does not imply security approval.

## Acceptance gate

1. Build and run the target’s existing regression tests, then feature parity tests.
2. Load old songs; save/reboot the new format; test full storage and interrupted writes.
3. Exercise internal/external MIDI timing, stop, engine switches and maximum simultaneous drum hits.
4. Back up the target’s actual occupied storage before installation. Recheck flash addresses against that exact build.
5. Install on a test unit and listen. Record the source commit, binary hash and what was actually tested.

Bundled SHAYPE parity and patch checks do not certify other firmware builds. There is no universal binary patch or flash allocation in this kit.
