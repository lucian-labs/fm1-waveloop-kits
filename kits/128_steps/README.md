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
