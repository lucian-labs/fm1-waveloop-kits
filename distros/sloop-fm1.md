# sloop-fm1

Source paths inspected; all four integrations require adaptation and target testing.

[Source at `19bdaa7f55db`](https://github.com/ELI7VH/sloop-fm1/tree/19bdaa7f55db9de2fbbafb7b457c002569c53383)

Preserve SLOOP’s native song and sample model. Add dirty-song autosave to its existing serializer. Reserve drum voices and storage without stealing sample regions.

## shape

Follow the [shape recipe](../kits/shape/README.md), using these target files:

- [`firmware/src/core.h`](https://github.com/ELI7VH/sloop-fm1/blob/19bdaa7f55db9de2fbbafb7b457c002569c53383/firmware/src/core.h)
- [`firmware/src/seq.c`](https://github.com/ELI7VH/sloop-fm1/blob/19bdaa7f55db9de2fbbafb7b457c002569c53383/firmware/src/seq.c)

## persistent songs

Follow the [persistent songs recipe](../kits/persistent_songs/README.md), using these target files:

- [`firmware/src/project.c`](https://github.com/ELI7VH/sloop-fm1/blob/19bdaa7f55db9de2fbbafb7b457c002569c53383/firmware/src/project.c)
- [`firmware/src/storage.c`](https://github.com/ELI7VH/sloop-fm1/blob/19bdaa7f55db9de2fbbafb7b457c002569c53383/firmware/src/storage.c)

## drums 808

Follow the [drums 808 recipe](../kits/drums_808/README.md), using these target files:

- [`firmware/src/voice.c`](https://github.com/ELI7VH/sloop-fm1/blob/19bdaa7f55db9de2fbbafb7b457c002569c53383/firmware/src/voice.c)

## drum sequencer

Follow the [drum sequencer recipe](../kits/drum_sequencer/README.md), using these target files:

- [`firmware/src/core.h`](https://github.com/ELI7VH/sloop-fm1/blob/19bdaa7f55db9de2fbbafb7b457c002569c53383/firmware/src/core.h)
- [`firmware/src/project.c`](https://github.com/ELI7VH/sloop-fm1/blob/19bdaa7f55db9de2fbbafb7b457c002569c53383/firmware/src/project.c)
- [`firmware/src/seq.c`](https://github.com/ELI7VH/sloop-fm1/blob/19bdaa7f55db9de2fbbafb7b457c002569c53383/firmware/src/seq.c)
- [`firmware/src/ui.c`](https://github.com/ELI7VH/sloop-fm1/blob/19bdaa7f55db9de2fbbafb7b457c002569c53383/firmware/src/ui.c)
- [`firmware/src/ui_input.c`](https://github.com/ELI7VH/sloop-fm1/blob/19bdaa7f55db9de2fbbafb7b457c002569c53383/firmware/src/ui_input.c)

## Acceptance

Build with this distro’s own toolchain. Check flash/RAM/audio budgets, old-project import, external clock, note-off behavior, save/reboot and song switching. Then listen on a test unit. See [porting checklist](../PORTING.md).
