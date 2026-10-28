# fm1-dub

Source paths inspected; all four integrations require adaptation and target testing.

[Source at `e6fe7b8f8f31`](https://github.com/sbegueria/fm1-dub/tree/e6fe7b8f8f3114019bb36b5b536ad458eacd2c2d)

Preserve this distro’s native engines, page routing and project format. These paths are integration targets, not evidence that WaveLoop features are already present. This uses the app/seq/dsp layout: the Felucca amalgamated C files are not drop-in. Write adapters for event scheduling, voice triggering and serialization. A separate sequencer.c was not found at this revision; locate the transport owner under firmware/src/app before implementing either sequencer feature.

## shape

Follow the [shape recipe](../kits/shape/README.md), using these target files:

No matching implementation file found. Add a new adapter after identifying the native engine/transport owner; do not invent a target path.

## persistent songs

Follow the [persistent songs recipe](../kits/persistent_songs/README.md), using these target files:

- [`firmware/src/app/project.c`](https://github.com/sbegueria/fm1-dub/blob/e6fe7b8f8f3114019bb36b5b536ad458eacd2c2d/firmware/src/app/project.c)
- [`firmware/src/storage.c`](https://github.com/sbegueria/fm1-dub/blob/e6fe7b8f8f3114019bb36b5b536ad458eacd2c2d/firmware/src/storage.c)

## drums 808

Follow the [drums 808 recipe](../kits/drums_808/README.md), using these target files:

No matching implementation file found. Add a new adapter after identifying the native engine/transport owner; do not invent a target path.

## drum sequencer

Follow the [drum sequencer recipe](../kits/drum_sequencer/README.md), using these target files:

- [`firmware/src/app/project.c`](https://github.com/sbegueria/fm1-dub/blob/e6fe7b8f8f3114019bb36b5b536ad458eacd2c2d/firmware/src/app/project.c)
- [`firmware/src/app/ui.c`](https://github.com/sbegueria/fm1-dub/blob/e6fe7b8f8f3114019bb36b5b536ad458eacd2c2d/firmware/src/app/ui.c)

## Acceptance

Build with this distro’s own toolchain. Check flash/RAM/audio budgets, old-project import, external clock, note-off behavior, save/reboot and song switching. Then listen on a test unit. See [porting checklist](../PORTING.md).
