# felucca-stock

Source paths inspected; all four integrations require adaptation and target testing.

[Source at `63f88ec18b71`](https://github.com/hugelton/Felucca/tree/63f88ec18b71c6ed4371d03d6f04dd93f4193ad3)

This is upstream Felucca, not the WaveLoop Kit. Port feature state, UI and storage hooks together. Preserve sample storage.

## shape

Follow the [shape recipe](../kits/shape/README.md), using these target files:

- [`firmware/src/core.h`](https://github.com/hugelton/Felucca/blob/63f88ec18b71c6ed4371d03d6f04dd93f4193ad3/firmware/src/core.h)
- [`firmware/src/seq.c`](https://github.com/hugelton/Felucca/blob/63f88ec18b71c6ed4371d03d6f04dd93f4193ad3/firmware/src/seq.c)

## persistent songs

Follow the [persistent songs recipe](../kits/persistent_songs/README.md), using these target files:

- [`firmware/src/project.c`](https://github.com/hugelton/Felucca/blob/63f88ec18b71c6ed4371d03d6f04dd93f4193ad3/firmware/src/project.c)
- [`firmware/src/song_chain.c`](https://github.com/hugelton/Felucca/blob/63f88ec18b71c6ed4371d03d6f04dd93f4193ad3/firmware/src/song_chain.c)
- [`firmware/src/storage.c`](https://github.com/hugelton/Felucca/blob/63f88ec18b71c6ed4371d03d6f04dd93f4193ad3/firmware/src/storage.c)

## drums 808

Follow the [drums 808 recipe](../kits/drums_808/README.md), using these target files:

- [`firmware/src/drum_voice.c`](https://github.com/hugelton/Felucca/blob/63f88ec18b71c6ed4371d03d6f04dd93f4193ad3/firmware/src/drum_voice.c)
- [`firmware/src/eng_drum.c`](https://github.com/hugelton/Felucca/blob/63f88ec18b71c6ed4371d03d6f04dd93f4193ad3/firmware/src/eng_drum.c)
- [`firmware/src/voice.c`](https://github.com/hugelton/Felucca/blob/63f88ec18b71c6ed4371d03d6f04dd93f4193ad3/firmware/src/voice.c)

## drum sequencer

Follow the [drum sequencer recipe](../kits/drum_sequencer/README.md), using these target files:

- [`firmware/src/core.h`](https://github.com/hugelton/Felucca/blob/63f88ec18b71c6ed4371d03d6f04dd93f4193ad3/firmware/src/core.h)
- [`firmware/src/project.c`](https://github.com/hugelton/Felucca/blob/63f88ec18b71c6ed4371d03d6f04dd93f4193ad3/firmware/src/project.c)
- [`firmware/src/seq.c`](https://github.com/hugelton/Felucca/blob/63f88ec18b71c6ed4371d03d6f04dd93f4193ad3/firmware/src/seq.c)
- [`firmware/src/ui.c`](https://github.com/hugelton/Felucca/blob/63f88ec18b71c6ed4371d03d6f04dd93f4193ad3/firmware/src/ui.c)
- [`firmware/src/ui_input.c`](https://github.com/hugelton/Felucca/blob/63f88ec18b71c6ed4371d03d6f04dd93f4193ad3/firmware/src/ui_input.c)

## Acceptance

Build with this distro’s own toolchain. Check flash/RAM/audio budgets, old-project import, external clock, note-off behavior, save/reboot and song switching. Then listen on a test unit. See [porting checklist](../PORTING.md).
