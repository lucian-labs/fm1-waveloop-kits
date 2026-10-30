# CoralFlower

**SHAYPE is implemented** in the [WaveLoop fork](https://github.com/ELI7VH/CoralFlower/tree/0d0d5a711824c5df1f7922a5a39a96efc6842dbd),
using CoralFlower's own interface and chord/sequencer players. Based on
[FicusFicusov/CoralFlower](https://github.com/FicusFicusov/CoralFlower) at `272cad9e85a444d879d72598807b7ca01a098d6d`.

Use the [play/edit and developer guide](https://github.com/ELI7VH/CoralFlower/blob/0d0d5a711824c5df1f7922a5a39a96efc6842dbd/docs/SHAYPE.md)
and [fork release packages](https://github.com/ELI7VH/CoralFlower/releases).
This is an opt-in fork; no upstream PR or developer outreach has been sent.

| Feature | Paths and status |
| --- | --- |
| SHAYPE | `arp_shape.c`, `cf_arp.c`, `cf_play.c`, `cf_seqp.c`: polyphonic player adapter. `cf_ui.c`, `cf_views.c`, `cf_screens.c`: five native pages and editable grid. `cf_settings.c`, `storage.c`, `cf_backup.c`: independent saved pattern and object 68. Implemented; core parity, 1,854 integration/timing checks, 134 backup checks and native build guards pass. |
| Persistent songs | Native `cf_sequi.c`, `cf_seqp.c`, `cf_settings.c`; CoralFlower's own pattern/song/resume system. WaveLoop's song workflow has not been ported. |
| Modified 808 | `drum_voice.c`, `eng_drum.c` are integration seams. CoralFlower keeps its upstream drums; WaveLoop's 808 modifications are not included. |
| Drum sequencer | `cf_seqd.c`, `cf_sequi.c`, `cf_seqp.c` retain CoralFlower's native drum sequencer. The kit-lane editor has not been ported. |

All firmware paths above are relative to `firmware/src/`. Full pinned paths and file hashes:
[provenance](../provenance-coralflower.json), [manifest](manifest.json).

## Controls and storage

ARP → K2 MODE: SHAYPE → K1 On. SELECT moves between Pattern, Feel, Shape, Draw and Attach.
K4 on Draw adds/removes a note; K3 edits its length. Seven starters, 1–64 steps, eight rows,
62 stored notes, eight active pitches per player. CHORDS and LAYER have independent runtime gates
and share the edited pattern/settings. Native arp modes, bass and interface remain.

The WHS1 record uses `0xA0000 / 0xA1000`, unused while CoralFlower's CZ engine is disabled.
It autosaves after 1.5 seconds without edits once audio is quiet, uses native A/B writes, and
adds validated backup/restore object 68. No upstream settings or sequencer format change.
Rate changes join the next beat-grid slot without resetting pattern position; a stopped grid
retains CoralFlower's native free-run behavior. Back up before changing firmware families.

SHAYPE and port: Elijah Lucian / Lucian Labs. CoralFlower: FicusFicusov and contributors;
ChoralRoot: Quixotic7; Felucca: Leo Kuroshita / Hügelton Instruments; FM engine: Kerem Kilic / Melodee;
Departure Mono: Helena Zhang. GPL-3.0-only; retain all original headers and dependency notices.

## Hardware smoke check — 2026-10-30

Installed/rebooted on FM1-TEST after a full Switch Blade backup and the installer's required official-V15 bridge.
SHAYPE enabled; native settings and default pattern read back exactly after restart. Actual target MIDI output:
16 chord note-ons, eight polyphonic pairs, clean release. A separate six-second default-pattern organ test
added no late buffers, sheds or steals. Two earlier late-buffer counts were observed during setup and not
isolated to a cause; no general CPU/stress claim is made. Physical listening remains with the user.
SHOW and GHOUL were not modified. [Release](https://github.com/ELI7VH/CoralFlower/releases/tag/v0.6.1-wlshape1).

## Rate extension — wlshape2

RATE has 21 entries: straight, triplet (T) and dotted (D) for each division from 1/1 through 1/64.
Dotted lasts 1.5×; triplet 2/3×. Original saved IDs 0–8 retain their meanings. The fine arp clock
runs at 96 PPQN with incoming MIDI-pulse interpolation; native sequencing/MIDI output stay at 24 PPQN.
No pattern or settings format change. All rate-pair/swing, duration and grid tests pass, including UBSan.
`cf_out.c` is the added fine-grid integration seam. TEST's 27 song/settings objects are verified after installation.
[Release](https://github.com/ELI7VH/CoralFlower/releases/tag/v0.6.1-wlshape2).
