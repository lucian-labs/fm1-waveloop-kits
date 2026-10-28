# estampie

Source paths inspected; all four integrations require adaptation and target testing.

[Source at `a5eb02a96b3f`](https://github.com/ocean/estampie/tree/a5eb02a96b3fa9303bce0772315f9467382aa57c)

Preserve this distro’s native engines, page routing and project format. These paths are integration targets, not evidence that WaveLoop features are already present.

## shape

Follow the [shape recipe](../kits/shape/README.md), using these target files:

- [`firmware/src/core.h`](https://github.com/ocean/estampie/blob/a5eb02a96b3fa9303bce0772315f9467382aa57c/firmware/src/core.h)
- [`firmware/src/seq.c`](https://github.com/ocean/estampie/blob/a5eb02a96b3fa9303bce0772315f9467382aa57c/firmware/src/seq.c)

## persistent songs

Follow the [persistent songs recipe](../kits/persistent_songs/README.md), using these target files:

- [`firmware/src/project.c`](https://github.com/ocean/estampie/blob/a5eb02a96b3fa9303bce0772315f9467382aa57c/firmware/src/project.c)
- [`firmware/src/song_chain.c`](https://github.com/ocean/estampie/blob/a5eb02a96b3fa9303bce0772315f9467382aa57c/firmware/src/song_chain.c)
- [`firmware/src/storage.c`](https://github.com/ocean/estampie/blob/a5eb02a96b3fa9303bce0772315f9467382aa57c/firmware/src/storage.c)

## drums 808

Follow the [drums 808 recipe](../kits/drums_808/README.md), using these target files:

- [`firmware/src/drum_voice.c`](https://github.com/ocean/estampie/blob/a5eb02a96b3fa9303bce0772315f9467382aa57c/firmware/src/drum_voice.c)
- [`firmware/src/eng_drum.c`](https://github.com/ocean/estampie/blob/a5eb02a96b3fa9303bce0772315f9467382aa57c/firmware/src/eng_drum.c)
- [`firmware/src/voice.c`](https://github.com/ocean/estampie/blob/a5eb02a96b3fa9303bce0772315f9467382aa57c/firmware/src/voice.c)

## drum sequencer

Follow the [drum sequencer recipe](../kits/drum_sequencer/README.md), using these target files:

- [`firmware/src/core.h`](https://github.com/ocean/estampie/blob/a5eb02a96b3fa9303bce0772315f9467382aa57c/firmware/src/core.h)
- [`firmware/src/project.c`](https://github.com/ocean/estampie/blob/a5eb02a96b3fa9303bce0772315f9467382aa57c/firmware/src/project.c)
- [`firmware/src/seq.c`](https://github.com/ocean/estampie/blob/a5eb02a96b3fa9303bce0772315f9467382aa57c/firmware/src/seq.c)
- [`firmware/src/ui.c`](https://github.com/ocean/estampie/blob/a5eb02a96b3fa9303bce0772315f9467382aa57c/firmware/src/ui.c)
- [`firmware/src/ui_input.c`](https://github.com/ocean/estampie/blob/a5eb02a96b3fa9303bce0772315f9467382aa57c/firmware/src/ui_input.c)

## Acceptance

Build with this distro’s own toolchain. Check flash/RAM/audio budgets, old-project import, external clock, note-off behavior, save/reboot and song switching. Then listen on a test unit. See [porting checklist](../PORTING.md).
