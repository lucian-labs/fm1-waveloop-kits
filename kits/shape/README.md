# SHAYPE / Shape Arp

WaveLoop’s drawn pattern maps rows to held chord notes. Eight rows, 1–64 steps, note lengths, chord voicing, WRAP/OCT and UP/DOWN/PEND/WYNDO/SHYFT movement.

## Source

Bundled core: [arp_shape.c](../../reference/firmware/src/arp_shape.c). It has no voice, UI or clock dependency. The supplied tests include the C file directly, as the firmware does.

Reference integration: [Switch Blade at 777aff21f6f0](https://github.com/ELI7VH/switchblade/tree/777aff21f6f00312095965bc826dbb4d9759974f/firmware/src): `seq.c` (`arp_fire`), `ui_arp.c`, `core.h`, `params.c`, `project.c`.

## Port

1. Include the core once in the target build. Keep the native clock as the timing authority.
2. Feed a sorted held-note set and pattern into the core; connect emitted pitch/length events to native note-on/off scheduling. Release notes on stop, chord change and engine switch.
3. Add pattern editing to native input/page routing. Do not reuse Switch Blade key IDs without checking the target UI.
4. Store a versioned per-track pattern. The reference packs 62 notes into 128 bytes; check the target’s wire format and old-project defaults.
5. Integrate gate, reset, sync and attach modes explicitly. Keep DRUM tracks outside the melodic arpeggiator unless designing a separate drum mapping.

Run the bundled parity fixtures, then target tests for internal/external clock, chord changes and held-note release. Core parity does not verify the target scheduler.

Credits: SHAYPE design and WaveLoop ports by Elijah Lucian / Lucian Labs; surrounding firmware/transport by the authors in [CREDITS](../../CREDITS.md).
