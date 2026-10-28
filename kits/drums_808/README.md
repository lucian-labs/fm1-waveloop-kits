# WaveLoop modified 808 drums

The WaveLoop revoicing adds fuller 808 kick/snare/clap behavior and per-drum shaping to Felucca’s drum synthesis. The bank and sequencer share eight canonical lanes.

| Lane | GM note |
| --- | --- |
| KICK | 36 |
| SNARE | 38 |
| CLAP | 39 |
| HATCL | 42 |
| HATOP | 46 |
| TOM | 45 |
| RIM | 37 |
| BELL | 56 |

## Source and provenance

Pinned Switch Blade donor in `provenance.json`: `firmware/src/drum_voice.c` and `eng_drum.c`. The latter records the port chain: WaveLoop Felucca revoicing `08913fe` / `b3e1f84`, per-drum controls `0bf4181`, through Melodee `fd4e003`. Resolve those history abbreviations within the linked WaveLoop forks; the pinned Switch Blade tree is the reproducible current donor.

Felucca Kit/Melodee keep controls in `drum_control.c`; Switch Blade integrates them in `eng_drum.c`. Consult the per-distro paths.

## Port

1. Adapt `drum_voice.c` to the target DSP types, sample rate, oscillator tables, RNG and filter helpers; it is not a freestanding compilation unit.
2. Register the bank with the engine selector and map GM notes to lane/variant. Preserve closed-hat choking, natural one-shot endings and the shared voice budget.
3. Carry per-lane pitch, tone, decay, snap, level, pan and send. A live hit selects the edit lane; sequencer playback must not keep changing editor focus.
4. Serialize bank IDs and per-drum overrides with a versioned migration. Avoid reinterpreting older stored IDs when adding banks.
5. If adding per-drum pan/send, adapt the mixer and effects buses too; controls without those paths do not complete the port.
6. Compare rendered/listened kick, snare, clap, hat choke, simultaneous hits and extreme controls; check CPU peaks while other tracks run.

The current Switch Blade engine also includes optional Yama-bruh and 909. An 808-only port must remove those dispatch branches deliberately, or bring their dependency files and notices. Do not copy `eng_drum.c` alone and expect it to build.

## Credits

Base voices/kit: **Leo Kuroshita (@kurogedelic), Hügelton Instruments**, GPL-3.0-only. WaveLoop revoicing/control work: **Elijah Lucian / Lucian Labs**. Retain the original copyright header.

Optional Yama-bruh: **Lucian Labs**, MIT. Optional 909: **athousanddetails’ 9W9**, after **Matthew Cieplak’s ER-99**, via **Charles Vestal’s fm1-x0x** and WaveLoop Melodee, GPL-3.0. These are distinct from the modified 808 voices. See [credits](../../CREDITS.md).
