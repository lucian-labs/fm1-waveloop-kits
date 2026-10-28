# Credits and source licenses

## WaveLoop additions

**Elijah Lucian / Lucian Labs**: SHAYPE design/ports, persistent-song workflow, modified 808 voicing and per-drum controls, and the Switch Blade kit-lane editor/integration. This credits the modifications, not the underlying synthesis, clock or storage systems.

## Firmware foundations

- **Leo Kuroshita (@kurogedelic), Hügelton Instruments** — [Felucca](https://github.com/hugelton/Felucca), base drum voices/kits, sequencer, project/storage and firmware foundation; GPL-3.0-only.
- **Ollie Nicklin** — [Switch Blade](https://github.com/OllieNicklinUK/switchblade).
- **keremimo** — [Melodee](https://github.com/keremimo/melodee).
- **isod89** — [SLOOP](https://github.com/isod89/sloop-fm1), including its native song architecture.
- **juanjiant-bit** — [JIANT](https://github.com/juanjiant-bit/JIANT), including its native integration of SLOOP song ideas.
- **zednaked** — inherited Felucca ratchets. Full contributor attribution: [donor CREDITS.md](https://github.com/ELI7VH/switchblade/blob/777aff21f6f00312095965bc826dbb4d9759974f/CREDITS.md).

Other mapped distributions retain their own authorship and licenses; the map is a link/index, not redistributed code from those projects.

## Optional drum dependencies (not bundled)

- **Lucian Labs, Yama-bruh** — [MIT source](https://github.com/lucian-labs/yama-bruh/tree/3eca861383e63e6c507c30402a204499faf79887). Firmware port `drum_yama.c` requires its MIT notice.
- **athousanddetails, 9W9**, after **Matthew Cieplak, ER-99**, via **Charles Vestal, fm1-x0x** — [pinned 909 source](https://github.com/charlesvestal/fm1-x0x/tree/201e5c5c1ac056a028a006bd1eabb23ac1bb174d), GPL-3.0; passed through WaveLoop Melodee. Preserve source notices and associated table-generator provenance.

## Distribution

Bundled files and patch retain GPL-3.0-only; see [LICENSE](LICENSE). Kit-authored documentation/tools are also GPL-3.0-only. See [donor LICENSING.md](https://github.com/ELI7VH/switchblade/blob/777aff21f6f00312095965bc826dbb4d9759974f/LICENSING.md) for the complete firmware’s dependency notices. This source kit does not relicense the full host firmware or optional dependencies. A patch is not a substitute for the complete corresponding source of a distributed firmware build.

No vendor firmware, SDK boot files, samples or font assets are included. FM-1 and other product names belong to their respective owners; this is an independent porting kit.
