# melodee

Existing persistent songs and modified drums donor. SHAYPE and drum-grid editor require porting.

[Source at `aaaf5e4a5f78`](https://github.com/ELI7VH/melodee/tree/aaaf5e4a5f78f2c3dfdcf5d6ae2e44eb99a5ef72)

The living setlist is in resume_sounds.c and uses project slots A–D. Retain the four-slot model unless flash allocation is redesigned; do not graft Switch Blade’s twelve-song addresses.

## shape

Follow the [shape recipe](../kits/shape/README.md), using these target files:

- [`firmware/src/core.h`](https://github.com/ELI7VH/melodee/blob/aaaf5e4a5f78f2c3dfdcf5d6ae2e44eb99a5ef72/firmware/src/core.h)
- [`firmware/src/seq.c`](https://github.com/ELI7VH/melodee/blob/aaaf5e4a5f78f2c3dfdcf5d6ae2e44eb99a5ef72/firmware/src/seq.c)

## persistent songs

Follow the [persistent songs recipe](../kits/persistent_songs/README.md), using these target files:

- [`firmware/src/project.c`](https://github.com/ELI7VH/melodee/blob/aaaf5e4a5f78f2c3dfdcf5d6ae2e44eb99a5ef72/firmware/src/project.c)
- [`firmware/src/resume_sounds.c`](https://github.com/ELI7VH/melodee/blob/aaaf5e4a5f78f2c3dfdcf5d6ae2e44eb99a5ef72/firmware/src/resume_sounds.c)
- [`firmware/src/song_chain.c`](https://github.com/ELI7VH/melodee/blob/aaaf5e4a5f78f2c3dfdcf5d6ae2e44eb99a5ef72/firmware/src/song_chain.c)
- [`firmware/src/storage.c`](https://github.com/ELI7VH/melodee/blob/aaaf5e4a5f78f2c3dfdcf5d6ae2e44eb99a5ef72/firmware/src/storage.c)

## drums 808

Follow the [drums 808 recipe](../kits/drums_808/README.md), using these target files:

- [`firmware/src/drum_control.c`](https://github.com/ELI7VH/melodee/blob/aaaf5e4a5f78f2c3dfdcf5d6ae2e44eb99a5ef72/firmware/src/drum_control.c)
- [`firmware/src/drum_voice.c`](https://github.com/ELI7VH/melodee/blob/aaaf5e4a5f78f2c3dfdcf5d6ae2e44eb99a5ef72/firmware/src/drum_voice.c)
- [`firmware/src/eng_drum.c`](https://github.com/ELI7VH/melodee/blob/aaaf5e4a5f78f2c3dfdcf5d6ae2e44eb99a5ef72/firmware/src/eng_drum.c)
- [`firmware/src/voice.c`](https://github.com/ELI7VH/melodee/blob/aaaf5e4a5f78f2c3dfdcf5d6ae2e44eb99a5ef72/firmware/src/voice.c)

## drum sequencer

Follow the [drum sequencer recipe](../kits/drum_sequencer/README.md), using these target files:

- [`firmware/src/core.h`](https://github.com/ELI7VH/melodee/blob/aaaf5e4a5f78f2c3dfdcf5d6ae2e44eb99a5ef72/firmware/src/core.h)
- [`firmware/src/pattern.c`](https://github.com/ELI7VH/melodee/blob/aaaf5e4a5f78f2c3dfdcf5d6ae2e44eb99a5ef72/firmware/src/pattern.c)
- [`firmware/src/project.c`](https://github.com/ELI7VH/melodee/blob/aaaf5e4a5f78f2c3dfdcf5d6ae2e44eb99a5ef72/firmware/src/project.c)
- [`firmware/src/seq.c`](https://github.com/ELI7VH/melodee/blob/aaaf5e4a5f78f2c3dfdcf5d6ae2e44eb99a5ef72/firmware/src/seq.c)
- [`firmware/src/ui.c`](https://github.com/ELI7VH/melodee/blob/aaaf5e4a5f78f2c3dfdcf5d6ae2e44eb99a5ef72/firmware/src/ui.c)
- [`firmware/src/ui_input.c`](https://github.com/ELI7VH/melodee/blob/aaaf5e4a5f78f2c3dfdcf5d6ae2e44eb99a5ef72/firmware/src/ui_input.c)

## Acceptance

Build with this distro’s own toolchain. Check flash/RAM/audio budgets, old-project import, external clock, note-off behavior, save/reboot and song switching. Then listen on a test unit. See [porting checklist](../PORTING.md).
