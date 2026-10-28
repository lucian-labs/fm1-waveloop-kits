# fm1-tribe

Source paths inspected; all four integrations require adaptation and target testing.

[Source at `32c51f1591da`](https://github.com/apiel/fm1-tribe/tree/32c51f1591dade6ebf3b0c7880fda7046b10197b)

Preserve this distro’s native engines, page routing and project format. These paths are integration targets, not evidence that WaveLoop features are already present. This uses the app/seq/dsp layout: the Felucca amalgamated C files are not drop-in. Write adapters for event scheduling, voice triggering and serialization.

## shape

Follow the [shape recipe](../kits/shape/README.md), using these target files:

- [`firmware/src/app/engine.h`](https://github.com/apiel/fm1-tribe/blob/32c51f1591dade6ebf3b0c7880fda7046b10197b/firmware/src/app/engine.h)
- [`firmware/src/seq/sequencer.c`](https://github.com/apiel/fm1-tribe/blob/32c51f1591dade6ebf3b0c7880fda7046b10197b/firmware/src/seq/sequencer.c)

## persistent songs

Follow the [persistent songs recipe](../kits/persistent_songs/README.md), using these target files:

- [`firmware/src/app/project.c`](https://github.com/apiel/fm1-tribe/blob/32c51f1591dade6ebf3b0c7880fda7046b10197b/firmware/src/app/project.c)
- [`firmware/src/storage.c`](https://github.com/apiel/fm1-tribe/blob/32c51f1591dade6ebf3b0c7880fda7046b10197b/firmware/src/storage.c)
- [`firmware/src/tribe/project.c`](https://github.com/apiel/fm1-tribe/blob/32c51f1591dade6ebf3b0c7880fda7046b10197b/firmware/src/tribe/project.c)

## drums 808

Follow the [drums 808 recipe](../kits/drums_808/README.md), using these target files:

- [`firmware/src/app/engine.h`](https://github.com/apiel/fm1-tribe/blob/32c51f1591dade6ebf3b0c7880fda7046b10197b/firmware/src/app/engine.h)
- [`firmware/src/dsp/drum808.c`](https://github.com/apiel/fm1-tribe/blob/32c51f1591dade6ebf3b0c7880fda7046b10197b/firmware/src/dsp/drum808.c)
- [`firmware/src/dsp/drum808.h`](https://github.com/apiel/fm1-tribe/blob/32c51f1591dade6ebf3b0c7880fda7046b10197b/firmware/src/dsp/drum808.h)

## drum sequencer

Follow the [drum sequencer recipe](../kits/drum_sequencer/README.md), using these target files:

- [`firmware/src/app/project.c`](https://github.com/apiel/fm1-tribe/blob/32c51f1591dade6ebf3b0c7880fda7046b10197b/firmware/src/app/project.c)
- [`firmware/src/app/ui.c`](https://github.com/apiel/fm1-tribe/blob/32c51f1591dade6ebf3b0c7880fda7046b10197b/firmware/src/app/ui.c)
- [`firmware/src/seq/pattern.c`](https://github.com/apiel/fm1-tribe/blob/32c51f1591dade6ebf3b0c7880fda7046b10197b/firmware/src/seq/pattern.c)
- [`firmware/src/seq/pattern.h`](https://github.com/apiel/fm1-tribe/blob/32c51f1591dade6ebf3b0c7880fda7046b10197b/firmware/src/seq/pattern.h)
- [`firmware/src/seq/sequencer.c`](https://github.com/apiel/fm1-tribe/blob/32c51f1591dade6ebf3b0c7880fda7046b10197b/firmware/src/seq/sequencer.c)
- [`firmware/src/tribe/project.c`](https://github.com/apiel/fm1-tribe/blob/32c51f1591dade6ebf3b0c7880fda7046b10197b/firmware/src/tribe/project.c)
- [`firmware/src/tribe/ui.c`](https://github.com/apiel/fm1-tribe/blob/32c51f1591dade6ebf3b0c7880fda7046b10197b/firmware/src/tribe/ui.c)

## Acceptance

Build with this distro’s own toolchain. Check flash/RAM/audio budgets, old-project import, external clock, note-off behavior, save/reboot and song switching. Then listen on a test unit. See [porting checklist](../PORTING.md).
