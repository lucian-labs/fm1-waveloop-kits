# jiant

Source paths inspected; all four integrations require adaptation and target testing.

[Source at `61a132e3eae1`](https://github.com/juanjiant-bit/JIANT/tree/61a132e3eae15ed3d7819a9e2d7c86f3069b7a22)

Map uses public JIANT, not the private WaveLoop fork. Preserve native projects and sections. Adapt SHAYPE scheduling to its sequencer; do not replace its song architecture or assume spare flash.

## shape

Follow the [shape recipe](../kits/shape/README.md), using these target files:

- [`firmware/src/core.h`](https://github.com/juanjiant-bit/JIANT/blob/61a132e3eae15ed3d7819a9e2d7c86f3069b7a22/firmware/src/core.h)
- [`firmware/src/seq.c`](https://github.com/juanjiant-bit/JIANT/blob/61a132e3eae15ed3d7819a9e2d7c86f3069b7a22/firmware/src/seq.c)

## persistent songs

Follow the [persistent songs recipe](../kits/persistent_songs/README.md), using these target files:

- [`firmware/src/project.c`](https://github.com/juanjiant-bit/JIANT/blob/61a132e3eae15ed3d7819a9e2d7c86f3069b7a22/firmware/src/project.c)
- [`firmware/src/song_chain.c`](https://github.com/juanjiant-bit/JIANT/blob/61a132e3eae15ed3d7819a9e2d7c86f3069b7a22/firmware/src/song_chain.c)
- [`firmware/src/song_main.c`](https://github.com/juanjiant-bit/JIANT/blob/61a132e3eae15ed3d7819a9e2d7c86f3069b7a22/firmware/src/song_main.c)
- [`firmware/src/storage.c`](https://github.com/juanjiant-bit/JIANT/blob/61a132e3eae15ed3d7819a9e2d7c86f3069b7a22/firmware/src/storage.c)

## drums 808

Follow the [drums 808 recipe](../kits/drums_808/README.md), using these target files:

- [`firmware/src/eng_drum.c`](https://github.com/juanjiant-bit/JIANT/blob/61a132e3eae15ed3d7819a9e2d7c86f3069b7a22/firmware/src/eng_drum.c)
- [`firmware/src/voice.c`](https://github.com/juanjiant-bit/JIANT/blob/61a132e3eae15ed3d7819a9e2d7c86f3069b7a22/firmware/src/voice.c)

## drum sequencer

Follow the [drum sequencer recipe](../kits/drum_sequencer/README.md), using these target files:

- [`firmware/src/core.h`](https://github.com/juanjiant-bit/JIANT/blob/61a132e3eae15ed3d7819a9e2d7c86f3069b7a22/firmware/src/core.h)
- [`firmware/src/project.c`](https://github.com/juanjiant-bit/JIANT/blob/61a132e3eae15ed3d7819a9e2d7c86f3069b7a22/firmware/src/project.c)
- [`firmware/src/seq.c`](https://github.com/juanjiant-bit/JIANT/blob/61a132e3eae15ed3d7819a9e2d7c86f3069b7a22/firmware/src/seq.c)
- [`firmware/src/ui.c`](https://github.com/juanjiant-bit/JIANT/blob/61a132e3eae15ed3d7819a9e2d7c86f3069b7a22/firmware/src/ui.c)
- [`firmware/src/ui_input.c`](https://github.com/juanjiant-bit/JIANT/blob/61a132e3eae15ed3d7819a9e2d7c86f3069b7a22/firmware/src/ui_input.c)

## Acceptance

Build with this distro’s own toolchain. Check flash/RAM/audio budgets, old-project import, external clock, note-off behavior, save/reboot and song switching. Then listen on a test unit. See [porting checklist](../PORTING.md).
