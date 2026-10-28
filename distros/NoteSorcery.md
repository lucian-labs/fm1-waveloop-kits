# NoteSorcery

Source paths inspected; all four integrations require adaptation and target testing.

[Source at `73d6cdd6d2a0`](https://github.com/catacombius/NoteSorcery/tree/73d6cdd6d2a006fad9df4f2227757b8131fe6ef6)

Preserve this distro’s native engines, page routing and project format. These paths are integration targets, not evidence that WaveLoop features are already present.

## shape

Follow the [shape recipe](../kits/shape/README.md), using these target files:

- [`firmware/src/core.h`](https://github.com/catacombius/NoteSorcery/blob/73d6cdd6d2a006fad9df4f2227757b8131fe6ef6/firmware/src/core.h)
- [`firmware/src/seq.c`](https://github.com/catacombius/NoteSorcery/blob/73d6cdd6d2a006fad9df4f2227757b8131fe6ef6/firmware/src/seq.c)

## persistent songs

Follow the [persistent songs recipe](../kits/persistent_songs/README.md), using these target files:

- [`firmware/src/project.c`](https://github.com/catacombius/NoteSorcery/blob/73d6cdd6d2a006fad9df4f2227757b8131fe6ef6/firmware/src/project.c)
- [`firmware/src/storage.c`](https://github.com/catacombius/NoteSorcery/blob/73d6cdd6d2a006fad9df4f2227757b8131fe6ef6/firmware/src/storage.c)

## drums 808

Follow the [drums 808 recipe](../kits/drums_808/README.md), using these target files:

- [`firmware/src/voice.c`](https://github.com/catacombius/NoteSorcery/blob/73d6cdd6d2a006fad9df4f2227757b8131fe6ef6/firmware/src/voice.c)
- [`firmware/src/x0x/drum808.c`](https://github.com/catacombius/NoteSorcery/blob/73d6cdd6d2a006fad9df4f2227757b8131fe6ef6/firmware/src/x0x/drum808.c)
- [`firmware/src/x0x/drum808.h`](https://github.com/catacombius/NoteSorcery/blob/73d6cdd6d2a006fad9df4f2227757b8131fe6ef6/firmware/src/x0x/drum808.h)

## drum sequencer

Follow the [drum sequencer recipe](../kits/drum_sequencer/README.md), using these target files:

- [`firmware/src/core.h`](https://github.com/catacombius/NoteSorcery/blob/73d6cdd6d2a006fad9df4f2227757b8131fe6ef6/firmware/src/core.h)
- [`firmware/src/project.c`](https://github.com/catacombius/NoteSorcery/blob/73d6cdd6d2a006fad9df4f2227757b8131fe6ef6/firmware/src/project.c)
- [`firmware/src/seq.c`](https://github.com/catacombius/NoteSorcery/blob/73d6cdd6d2a006fad9df4f2227757b8131fe6ef6/firmware/src/seq.c)
- [`firmware/src/ui.c`](https://github.com/catacombius/NoteSorcery/blob/73d6cdd6d2a006fad9df4f2227757b8131fe6ef6/firmware/src/ui.c)
- [`firmware/src/ui_input.c`](https://github.com/catacombius/NoteSorcery/blob/73d6cdd6d2a006fad9df4f2227757b8131fe6ef6/firmware/src/ui_input.c)

## Acceptance

Build with this distro’s own toolchain. Check flash/RAM/audio budgets, old-project import, external clock, note-off behavior, save/reboot and song switching. Then listen on a test unit. See [porting checklist](../PORTING.md).
