# switchblade

Reference implementation for all four features. Sequencer patch supplied; listening acceptance remains outstanding.

[Source at `5d570beea20c`](https://github.com/ELI7VH/switchblade/tree/5d570beea20c020f00de51b3188baccb2384663e)

Use the pinned WaveLoop fork, not the upstream stock tree. The patch applies only to its recorded base commit.

## shape

Follow the [shape recipe](../kits/shape/README.md), using these target files:

- [`firmware/src/arp_shape.c`](https://github.com/ELI7VH/switchblade/blob/5d570beea20c020f00de51b3188baccb2384663e/firmware/src/arp_shape.c)
- [`firmware/src/core.h`](https://github.com/ELI7VH/switchblade/blob/5d570beea20c020f00de51b3188baccb2384663e/firmware/src/core.h)
- [`firmware/src/seq.c`](https://github.com/ELI7VH/switchblade/blob/5d570beea20c020f00de51b3188baccb2384663e/firmware/src/seq.c)
- [`firmware/src/ui_arp.c`](https://github.com/ELI7VH/switchblade/blob/5d570beea20c020f00de51b3188baccb2384663e/firmware/src/ui_arp.c)

## persistent songs

Follow the [persistent songs recipe](../kits/persistent_songs/README.md), using these target files:

- [`firmware/src/project.c`](https://github.com/ELI7VH/switchblade/blob/5d570beea20c020f00de51b3188baccb2384663e/firmware/src/project.c)
- [`firmware/src/setlist.c`](https://github.com/ELI7VH/switchblade/blob/5d570beea20c020f00de51b3188baccb2384663e/firmware/src/setlist.c)
- [`firmware/src/song_chain.c`](https://github.com/ELI7VH/switchblade/blob/5d570beea20c020f00de51b3188baccb2384663e/firmware/src/song_chain.c)
- [`firmware/src/storage.c`](https://github.com/ELI7VH/switchblade/blob/5d570beea20c020f00de51b3188baccb2384663e/firmware/src/storage.c)

## drums 808

Follow the [drums 808 recipe](../kits/drums_808/README.md), using these target files:

- [`firmware/src/drum_voice.c`](https://github.com/ELI7VH/switchblade/blob/5d570beea20c020f00de51b3188baccb2384663e/firmware/src/drum_voice.c)
- [`firmware/src/eng_drum.c`](https://github.com/ELI7VH/switchblade/blob/5d570beea20c020f00de51b3188baccb2384663e/firmware/src/eng_drum.c)
- [`firmware/src/voice.c`](https://github.com/ELI7VH/switchblade/blob/5d570beea20c020f00de51b3188baccb2384663e/firmware/src/voice.c)

## drum sequencer

Follow the [drum sequencer recipe](../kits/drum_sequencer/README.md), using these target files:

- [`firmware/src/core.h`](https://github.com/ELI7VH/switchblade/blob/5d570beea20c020f00de51b3188baccb2384663e/firmware/src/core.h)
- [`firmware/src/project.c`](https://github.com/ELI7VH/switchblade/blob/5d570beea20c020f00de51b3188baccb2384663e/firmware/src/project.c)
- [`firmware/src/seq.c`](https://github.com/ELI7VH/switchblade/blob/5d570beea20c020f00de51b3188baccb2384663e/firmware/src/seq.c)
- [`firmware/src/ui.c`](https://github.com/ELI7VH/switchblade/blob/5d570beea20c020f00de51b3188baccb2384663e/firmware/src/ui.c)
- [`firmware/src/ui_drum.c`](https://github.com/ELI7VH/switchblade/blob/5d570beea20c020f00de51b3188baccb2384663e/firmware/src/ui_drum.c)
- [`firmware/src/ui_input.c`](https://github.com/ELI7VH/switchblade/blob/5d570beea20c020f00de51b3188baccb2384663e/firmware/src/ui_input.c)

## Acceptance

Build with this distro’s own toolchain. Check flash/RAM/audio budgets, old-project import, external clock, note-off behavior, save/reboot and song switching. Then listen on a test unit. See [porting checklist](../PORTING.md).

## Modular HOME sequence view

The [sequence-view module](../kits/sequence_view/README.md) has a separate adapter pinned to `4f0de78c982d478e9f64388ea2c93ab771c4e2db`. It displays bank/patch and complete track patterns. Its [bank-theme module](../kits/bank_themes/README.md) preserves native per-machine palettes and binds DRUM to WaveLoop. These newer module pins do not replace the older exact-base patches above.
