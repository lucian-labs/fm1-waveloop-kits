# ChoralRoot FM-1 + SHAYPE

**Installed on TEST as ChoralRoot 0.27-wlshape3.** SHAYPE Pattern 13 selected; Perform enabled.
[Public fork](https://github.com/ELI7VH/ChoralRootFM1/tree/9b2b3c086104135ba4e49d84fde115cc9a020dc1) ·
[controls and developer guide](https://github.com/ELI7VH/ChoralRootFM1/blob/9b2b3c086104135ba4e49d84fde115cc9a020dc1/docs/SHAYPE.md).
Upstream: Quixotic7/ChoralRootFM1 at `ec9c54fdd7a0a544e8ec82bec196db745868f057`.

## SHAYPE implementation

SHAYPE is native Pattern **13**: hold ARP → SELECT Pattern → K1 SHAYPE.
OCT−/+ switch Play, Shape and Draw; HOME closes. Native coloured knob cells, theme and grid rendering.
The playhead redraws the grid band only. Seven starters, 62 stored notes, eight rows, 1–64 steps,
note lengths, WYNDO/SHYFT and other movement, root floor and wrap/octave boundaries.

Native rate IDs are retained. Straight/triplet/dotted choices reach 1/64, with the original 2/1 retained
(22 choices). The native rational scheduler joins the global grid and rate changes retain melodic position.
ChoralRoot owns chord gestures, note registry, MIDI clock, bass and release; HOLD/LOCK remain native.
This adapter does not copy CoralFlower's NOW/NOTE/CYCLE attachment controls.

Save with native **global SAVE** (hold SAVE). Settings stay 192 bytes; session v2 appends SHAYPE at offset
1024 and grows to 1156 bytes inside its existing A/B object. Old session fields keep their offsets and
old sessions migrate with a default SHAYPE pattern. No new sectors or wider flash guards.
Backup object **69** carries the saved session; the supplied CLI/browser restore it **after settings 1**,
whose native PUT clears an old session. Keep pre-upgrade backups for downgrades.

| Other feature | Status / integration seam |
| --- | --- |
| Persistent songs | ChoralRoot's native global session and chord-loop system (`cr_settings.c`, `cr_loop.c`, `cr_ui.c`). WaveLoop's persistent-song/autosave workflow is not ported. |
| Modified 808 | Not included. `eng_drum.c` / `drum_voice.c` are kept source, but `choralroot.c` disables DRUM. A port needs a deliberate engine, routing and UI design. |
| Drum sequencer | Not included. ChoralRoot's `cr_loop.c` and `cr_ui.c` provide chord-loop/step-entry seams, not a drum-lane implementation. |

## Verification and next step

Core parity; 2800 existing engine, 483 loop, 296 settings, 236 backup, 2012 focused SHAYPE under full UBSan,
13 UI/save/restore/redraw and 34 MIDI checks pass. Output-routing, CLI-installer and browser-backup tests pass.
Standard and one-core target packages build with native guards enabled. Native emulator input renders
SHAYPE pages and produces audio. Installed on TEST after stopped confirmation and a fresh CoralFlower
wlshape3 backup, using the official-V15 bridge and native installers without force. Reboot/version verified.
A four-second real-target key/chord test produced 28 chord note-ons and 12 polyphonic pairs, with no attacks
after release grace. Temporary MIDI Keys mapping removed; selected settings read back exactly, all other
objects unchanged from first boot. An unrecognized legacy settings record was preserved in that backup;
the new selected settings use ChoralRoot's native boot defaults. Session69 remains empty until global SAVE.
Physical listening and broad CPU/headroom acceptance remain pending. SHOW/GHOUL were not modified.

Paths/hashes: [manifest](manifest.json), [provenance](../provenance-choralroot.json).
The fork is opt-in; no upstream PR or developer message was sent.

SHAYPE design/adapter: Elijah Lucian / Lucian Labs. ChoralRoot: Quixotic7 and contributors, after their monome-grid
choralroot engine. Felucca: Leo Kuroshita / Hügelton Instruments. Other engines/fonts keep upstream credits.
GPL-3.0-only, original notices retained. This kit does not bundle firmware binaries, backups or SDK files.

## Octave update — wlshape2

Shape-page K4 replaces ROOT pitch floor with signed **Octave −2…+2**. Every generated SHAYPE
note shifts12semitones per detent, affecting upcoming attacks without resetting the pattern.
The prior reserved byte stores octave; legacy root remains in the record but is ignored.
Older sessions use octave0; SHAYPE132bytes/sessionv2 1156bytes unchanged. Native globalSAVE persists it.
2030SHAYPE fullUBSan and16UI/save/revert checks pass alongside native/core/build guards.
Native emulator label inspected. wlshape2 installed; actual target MIDI confirmed exact±12shifts, all saved objects preserved. TEST is now wlshape3 below.
FM1 transfer clients must distinguish this from wlshape1's ROOT floor; preserve signed octave on read/modify/write.

## Scale Keys — wlshape3 installed

Options → Chord Keys → **Scale Keys**: roots C4up follow selected Major/Minor key/scale.
F/G/A/B select root/first/second/third inversion. Hold F♯/G♯/B♭ for diatonic7/9/13, alone or combined;
release removes that extension. Classic/FM-1 remain selectable. White key release keeps inversion.
Layout uses raw_sound bit6 (0x40); settings192/session1156 bytes unchanged. Preserve this flag
when transferring other settings. Musical pattern/inversion state still uses native globalSAVE.
10,759 Scale Keys fullUBSan and23nativeUI/save/restore checks pass alongside existing suites and
targetguards. Actual TEST MIDI verified Major/Minor chords, all inversions, seven extension sets,
independent removal, SHAYPE walking the six-note chord and clean release. All original stored
objects matched after firmware update; only selected Scale Keys option changed afterward, readback exact.
Temporary MIDIKeys routing/test scales removed. Physical listening/broad CPU acceptance remain separate.
