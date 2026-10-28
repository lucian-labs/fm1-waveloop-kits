# hortator

Source paths inspected; all four integrations require adaptation and target testing.

[Source at `2d7a0b19f5c3`](https://github.com/DeadActive/hortator/tree/2d7a0b19f5c3fd5d23bec6d4e91f6038d46d1a70)

Preserve this distro’s native engines, page routing and project format. These paths are integration targets, not evidence that WaveLoop features are already present.

## shape

Follow the [shape recipe](../kits/shape/README.md), using these target files:

- [`firmware/src/core.h`](https://github.com/DeadActive/hortator/blob/2d7a0b19f5c3fd5d23bec6d4e91f6038d46d1a70/firmware/src/core.h)
- [`firmware/src/seq.c`](https://github.com/DeadActive/hortator/blob/2d7a0b19f5c3fd5d23bec6d4e91f6038d46d1a70/firmware/src/seq.c)

## persistent songs

Follow the [persistent songs recipe](../kits/persistent_songs/README.md), using these target files:

- [`firmware/src/project.c`](https://github.com/DeadActive/hortator/blob/2d7a0b19f5c3fd5d23bec6d4e91f6038d46d1a70/firmware/src/project.c)
- [`firmware/src/song.c`](https://github.com/DeadActive/hortator/blob/2d7a0b19f5c3fd5d23bec6d4e91f6038d46d1a70/firmware/src/song.c)
- [`firmware/src/storage.c`](https://github.com/DeadActive/hortator/blob/2d7a0b19f5c3fd5d23bec6d4e91f6038d46d1a70/firmware/src/storage.c)

## drums 808

Follow the [drums 808 recipe](../kits/drums_808/README.md), using these target files:

No matching implementation file found. Add a new adapter after identifying the native engine/transport owner; do not invent a target path.

## drum sequencer

Follow the [drum sequencer recipe](../kits/drum_sequencer/README.md), using these target files:

- [`firmware/src/core.h`](https://github.com/DeadActive/hortator/blob/2d7a0b19f5c3fd5d23bec6d4e91f6038d46d1a70/firmware/src/core.h)
- [`firmware/src/project.c`](https://github.com/DeadActive/hortator/blob/2d7a0b19f5c3fd5d23bec6d4e91f6038d46d1a70/firmware/src/project.c)
- [`firmware/src/seq.c`](https://github.com/DeadActive/hortator/blob/2d7a0b19f5c3fd5d23bec6d4e91f6038d46d1a70/firmware/src/seq.c)
- [`firmware/src/ui.c`](https://github.com/DeadActive/hortator/blob/2d7a0b19f5c3fd5d23bec6d4e91f6038d46d1a70/firmware/src/ui.c)
- [`firmware/src/ui_input.c`](https://github.com/DeadActive/hortator/blob/2d7a0b19f5c3fd5d23bec6d4e91f6038d46d1a70/firmware/src/ui_input.c)

## Acceptance

Build with this distro’s own toolchain. Check flash/RAM/audio budgets, old-project import, external clock, note-off behavior, save/reboot and song switching. Then listen on a test unit. See [porting checklist](../PORTING.md).
