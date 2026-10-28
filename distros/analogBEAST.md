# analogBEAST

Source paths inspected; all four integrations require adaptation and target testing.

[Source at `8bbee0c6b15c`](https://github.com/dzwerg/analogBEAST/tree/8bbee0c6b15ca4fca5cc50bddd581e738886558f)

Preserve this distro’s native engines, page routing and project format. These paths are integration targets, not evidence that WaveLoop features are already present.

## shape

Follow the [shape recipe](../kits/shape/README.md), using these target files:

- [`firmware/src/core.h`](https://github.com/dzwerg/analogBEAST/blob/8bbee0c6b15ca4fca5cc50bddd581e738886558f/firmware/src/core.h)
- [`firmware/src/seq.c`](https://github.com/dzwerg/analogBEAST/blob/8bbee0c6b15ca4fca5cc50bddd581e738886558f/firmware/src/seq.c)

## persistent songs

Follow the [persistent songs recipe](../kits/persistent_songs/README.md), using these target files:

- [`firmware/src/project.c`](https://github.com/dzwerg/analogBEAST/blob/8bbee0c6b15ca4fca5cc50bddd581e738886558f/firmware/src/project.c)
- [`firmware/src/song_chain.c`](https://github.com/dzwerg/analogBEAST/blob/8bbee0c6b15ca4fca5cc50bddd581e738886558f/firmware/src/song_chain.c)
- [`firmware/src/storage.c`](https://github.com/dzwerg/analogBEAST/blob/8bbee0c6b15ca4fca5cc50bddd581e738886558f/firmware/src/storage.c)

## drums 808

Follow the [drums 808 recipe](../kits/drums_808/README.md), using these target files:

- [`firmware/src/drum_voice.c`](https://github.com/dzwerg/analogBEAST/blob/8bbee0c6b15ca4fca5cc50bddd581e738886558f/firmware/src/drum_voice.c)
- [`firmware/src/eng_drum.c`](https://github.com/dzwerg/analogBEAST/blob/8bbee0c6b15ca4fca5cc50bddd581e738886558f/firmware/src/eng_drum.c)
- [`firmware/src/voice.c`](https://github.com/dzwerg/analogBEAST/blob/8bbee0c6b15ca4fca5cc50bddd581e738886558f/firmware/src/voice.c)

## drum sequencer

Follow the [drum sequencer recipe](../kits/drum_sequencer/README.md), using these target files:

- [`firmware/src/core.h`](https://github.com/dzwerg/analogBEAST/blob/8bbee0c6b15ca4fca5cc50bddd581e738886558f/firmware/src/core.h)
- [`firmware/src/project.c`](https://github.com/dzwerg/analogBEAST/blob/8bbee0c6b15ca4fca5cc50bddd581e738886558f/firmware/src/project.c)
- [`firmware/src/seq.c`](https://github.com/dzwerg/analogBEAST/blob/8bbee0c6b15ca4fca5cc50bddd581e738886558f/firmware/src/seq.c)
- [`firmware/src/ui.c`](https://github.com/dzwerg/analogBEAST/blob/8bbee0c6b15ca4fca5cc50bddd581e738886558f/firmware/src/ui.c)
- [`firmware/src/ui_input.c`](https://github.com/dzwerg/analogBEAST/blob/8bbee0c6b15ca4fca5cc50bddd581e738886558f/firmware/src/ui_input.c)

## Acceptance

Build with this distro’s own toolchain. Check flash/RAM/audio budgets, old-project import, external clock, note-off behavior, save/reboot and song switching. Then listen on a test unit. See [porting checklist](../PORTING.md).
