# felucca-kit

Existing SHAYPE, persistent setlist and modified drums donor. Drum-grid editor requires porting.

[Source at `8e5c90b3a192`](https://github.com/ELI7VH/Felucca/tree/8e5c90b3a192712efc699559334c896a892442c2)

Keep the existing SHAYPE and drum controls; merge only missing grid hooks. Audit FOR4 reserved fields before adopting the Switch Blade lane masks.

## shape

Follow the [shape recipe](../kits/shape/README.md), using these target files:

- [`firmware/src/arp_shape.c`](https://github.com/ELI7VH/Felucca/blob/8e5c90b3a192712efc699559334c896a892442c2/firmware/src/arp_shape.c)
- [`firmware/src/core.h`](https://github.com/ELI7VH/Felucca/blob/8e5c90b3a192712efc699559334c896a892442c2/firmware/src/core.h)
- [`firmware/src/seq.c`](https://github.com/ELI7VH/Felucca/blob/8e5c90b3a192712efc699559334c896a892442c2/firmware/src/seq.c)
- [`firmware/src/ui_arp.c`](https://github.com/ELI7VH/Felucca/blob/8e5c90b3a192712efc699559334c896a892442c2/firmware/src/ui_arp.c)

## persistent songs

Follow the [persistent songs recipe](../kits/persistent_songs/README.md), using these target files:

- [`firmware/src/project.c`](https://github.com/ELI7VH/Felucca/blob/8e5c90b3a192712efc699559334c896a892442c2/firmware/src/project.c)
- [`firmware/src/setlist.c`](https://github.com/ELI7VH/Felucca/blob/8e5c90b3a192712efc699559334c896a892442c2/firmware/src/setlist.c)
- [`firmware/src/song_chain.c`](https://github.com/ELI7VH/Felucca/blob/8e5c90b3a192712efc699559334c896a892442c2/firmware/src/song_chain.c)
- [`firmware/src/storage.c`](https://github.com/ELI7VH/Felucca/blob/8e5c90b3a192712efc699559334c896a892442c2/firmware/src/storage.c)

## drums 808

Follow the [drums 808 recipe](../kits/drums_808/README.md), using these target files:

- [`firmware/src/drum_control.c`](https://github.com/ELI7VH/Felucca/blob/8e5c90b3a192712efc699559334c896a892442c2/firmware/src/drum_control.c)
- [`firmware/src/drum_voice.c`](https://github.com/ELI7VH/Felucca/blob/8e5c90b3a192712efc699559334c896a892442c2/firmware/src/drum_voice.c)
- [`firmware/src/eng_drum.c`](https://github.com/ELI7VH/Felucca/blob/8e5c90b3a192712efc699559334c896a892442c2/firmware/src/eng_drum.c)
- [`firmware/src/voice.c`](https://github.com/ELI7VH/Felucca/blob/8e5c90b3a192712efc699559334c896a892442c2/firmware/src/voice.c)

## drum sequencer

Follow the [drum sequencer recipe](../kits/drum_sequencer/README.md), using these target files:

- [`firmware/src/core.h`](https://github.com/ELI7VH/Felucca/blob/8e5c90b3a192712efc699559334c896a892442c2/firmware/src/core.h)
- [`firmware/src/project.c`](https://github.com/ELI7VH/Felucca/blob/8e5c90b3a192712efc699559334c896a892442c2/firmware/src/project.c)
- [`firmware/src/seq.c`](https://github.com/ELI7VH/Felucca/blob/8e5c90b3a192712efc699559334c896a892442c2/firmware/src/seq.c)
- [`firmware/src/ui.c`](https://github.com/ELI7VH/Felucca/blob/8e5c90b3a192712efc699559334c896a892442c2/firmware/src/ui.c)
- [`firmware/src/ui_input.c`](https://github.com/ELI7VH/Felucca/blob/8e5c90b3a192712efc699559334c896a892442c2/firmware/src/ui_input.c)

## Acceptance

Build with this distro’s own toolchain. Check flash/RAM/audio budgets, old-project import, external clock, note-off behavior, save/reboot and song switching. Then listen on a test unit. See [porting checklist](../PORTING.md).
