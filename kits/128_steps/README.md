# 128-step extension

128 steps at 1/16 cover eight bars in 4/4. Both melodic and drum tracks get eight pages. Per-step nudge resolution remains unchanged; individual hit timing is a separate feature.

## Reference patch

The [patch](../../patches/switchblade-128-steps.patch) applies only to WaveLoop Switch Blade at `ca460a2fd2be87da391b5cde33f527e04cb232e7`, reproducing firmware/tests at `201d86a96a162466d8170abe4f214af247a507e2`. It includes a synthetic legacy fixture, never a device backup.

```sh
git clone https://github.com/ELI7VH/switchblade.git
cd switchblade
git switch -c codex/128-step-port ca460a2fd2be87da391b5cde33f527e04cb232e7
git apply --check /path/to/fm1-waveloop-kits/patches/switchblade-128-steps.patch
git apply /path/to/fm1-waveloop-kits/patches/switchblade-128-steps.patch
```

Use the donor's BUILDING.md. Test with seq_128_test.c, storage_128_test.c and the standard regression suite. [Full implementation notes and verification](https://github.com/ELI7VH/switchblade/blob/201d86a96a162466d8170abe4f214af247a507e2/docs/128-STEPS.md).

## Porting boundaries

- core.h: 128-step arrays and nine-bit automation addresses. Audit byte-sized addresses and every 64-bit step bitmap.
- project.c: FOR5 (6400 bytes), FOR4 import, length encoding, wider automation, backup staging and flash-backed slot caches.
- storage.c: atomic A/B base-plus-extension records. The retired-sample ranges belong to this Switch Blade fork; audit another distro's map before adapting.
- motion.c, UI and editor: high-step routing, holds, locks, undo, sequence tools, eight-page navigation and extended-capacity discovery.
- Song-chain helpers: full-length pattern copies and wider arrangement-duration metadata.

Older firmware cannot load newly saved FOR5 projects. Older browser editors still show only the first 64 steps; the hardware handles all eight pages. This extension is not a verified port for the other mapped distros.

Credit: Elijah Lucian / Lucian Labs' extension and tests, over Felucca / Switch Blade's sequencer and storage. GPL-3.0-only; preserve the [original credits](../../CREDITS.md).

## Played hold timing (optional follow-up)

[Played-holds patch](../../patches/switchblade-played-holds.patch) keeps start quantization while recording synth release times in 1/256-step units. It applies only to `1bb03f2c928e75c6045b93716e584fe97aae7732` and produces `1934f1c042cc0fc2e3f5807417d23e3c33e07e9e`. See [provenance](../../provenance-holds.json) and the [implementation notes](https://github.com/ELI7VH/switchblade/blob/1934f1c042cc0fc2e3f5807417d23e3c33e07e9e/docs/PLAYED-HOLDS.md).

This follow-up uses FOR6, retaining FOR5's 6400-byte flash extent and importing FOR4/FOR5 with their old GATE/TIE behavior. Port `core.h`, `seq.c`, `project.c`, `voice.c` and the explicit LEN override in `ui.c` together: duration timers must survive ties, and engine switches must distinguish synth durations from drum masks. K1 step entry and drum one-shots remain unchanged. Run `played_hold_test.c` and the donor's project/MIDI/arp tests. Hardware installation and listening are pending. The other distro path maps identify adaptation points; this patch is not a verified port to those distros.

Credit: Elijah Lucian / Lucian Labs' held-duration extension over the original Felucca / Switch Blade sequencing code; retain source headers and [credits](../../CREDITS.md). GPL-3.0-only.
