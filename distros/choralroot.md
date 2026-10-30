# ChoralRoot FM-1 + SHAYPE

**Prepared next candidate; not installed on hardware.** TEST remains on CoralFlower wlshape2.
[Public fork](https://github.com/ELI7VH/ChoralRootFM1/tree/dc018a0fcc81e59e63abec2505726915688ea4f4) ·
[controls and developer guide](https://github.com/ELI7VH/ChoralRootFM1/blob/dc018a0fcc81e59e63abec2505726915688ea4f4/docs/SHAYPE.md).
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
SHAYPE pages and produces audio. No physical installation, listening or CPU/headroom certification is claimed.
The next TEST install requires a fresh CoralFlower backup, stopped confirmation and the native installer's
compatibility check/official-V15 bridge if refused. SHOW and GHOUL are excluded.

Paths/hashes: [manifest](manifest.json), [provenance](../provenance-choralroot.json).
The fork is opt-in; no upstream PR or developer message was sent.

SHAYPE design/adapter: Elijah Lucian / Lucian Labs. ChoralRoot: Quixotic7 and contributors, after their monome-grid
choralroot engine. Felucca: Leo Kuroshita / Hügelton Instruments. Other engines/fonts keep upstream credits.
GPL-3.0-only, original notices retained. This kit does not bundle firmware binaries, backups or SDK files.
