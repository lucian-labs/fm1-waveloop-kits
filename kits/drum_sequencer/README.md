# Kit-lane drum sequencer

WaveLoop’s eight-lane editor uses the host’s existing timing, chance, ratchet, MIDI and transport. It pairs canonical lane hits with the drum bank selected on the track.

## Apply to the exact Switch Blade base

The [patch](../../patches/switchblade-drum-sequencer.patch) contains firmware and tests only. It depends on the WaveLoop drum engine already present at this base:

```sh
git clone https://github.com/ELI7VH/switchblade.git
cd switchblade
git switch -c codex/drum-kit-port ac2a12e8066d79c49070e8c268d18c76bb5a112b
git apply --check /path/to/fm1-waveloop-kits/patches/switchblade-drum-sequencer.patch
git apply /path/to/fm1-waveloop-kits/patches/switchblade-drum-sequencer.patch
```

Use that firmware’s BUILDING.md and tests/run_tests.sh. Do not apply this patch blindly to upstream Switch Blade or another fork.

## Adapt to another distro

1. Add the lane editor (`ui_drum.c`) through the target’s page/input/draw routing.
2. Store eight hit bits and eight accent bits per step. In this donor only, DRUM uses existing FOR4 `hit`/`acc` bytes; audit target meanings or introduce a new versioned extension.
3. Expand scheduling scratch capacity for eight lanes plus four legacy notes. Retain exact legacy MIDI notes, avoid duplicate triggers and preserve gate/nudge/chance/ratchet behavior.
4. Record drum hits as one-shots without ties. Keep per-step velocity semantics: this implementation does not provide independent velocity per lane.
5. Save/import masks only for the appropriate engine. Preserve old projects and document downgrade loss: older firmware may ignore the new masks.
6. Test step edits during playback, page persistence, overdubbing, note variants, simultaneous hits, stop, external MIDI clock and project round trips.

## Reference controls

- Sixteen white keys toggle steps on release; first eight black keys choose a lane.
- K1 lane, K2 page, K3 length, K4 swing.
- Hold steps: K3 velocity, K4 accent. EDIT affects the selected lane at the cursor.

The 909 bank has extra variants through MIDI/keyboard; this remains an eight-lane grid, not eleven independent 909 lanes.

Credit: Elijah Lucian / Lucian Labs’ kit-lane editor and integration, built on **Leo Kuroshita / Hügelton’s Felucca sequencer** and **Ollie Nicklin’s Switch Blade**, with inherited ratchet work credited to **zednaked**. Preserve upstream contributor credits when distributing the complete firmware.
