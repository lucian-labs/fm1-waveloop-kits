# Persistent songs

The current song is a living document: edits autosave when stopped and idle, leaving a changed song saves it first, and power-on resumes the last song. Duplication claims a free slot; a full setlist must not silently overwrite another song.

## Donors

- Switch Blade and WaveLoop Felucca Kit: `firmware/src/setlist.c`, `project.c`, `storage.c`, `ui_input.c`, `ui_draw.c`.
- WaveLoop Melodee: `firmware/src/resume_sounds.c`, `project.c`, `storage.c`, `ui_input.c`, `ui_stage.c`.
- Follow the pinned paths in the distro map; these files depend on their host’s project and storage types.

## Port

1. Reuse the target project serializer for the complete song: sounds, steps, automation, arrangement and name. Track a dirty signature/revision.
2. Define a slot map from the target linker/storage layout. Keep every active sample, preset and calibration region intact.
3. Use the target’s validated A/B record, CRC and generation mechanism. Commit the new valid record before invalidating the old; propagate failed writes to the UI.
4. Save after the reference’s ten-second stopped/idle interval, and before changing songs. If a save fails, keep the current song recoverable and do not report success.
5. Persist the current-song identity with the serialized state. Restore only validated records. Duplicate into an unused slot; provide a full-list result.
6. Test power interruption, corrupt/newest records, full storage, failed writes, old projects and reboot after switching songs.

Switch Blade’s twelve songs use `0xA0000..0xB7FFF`, retired sample storage in that particular fork. **Never copy those addresses into a sampler distro.** Melodee uses four existing project slots A–D. JIANT/SLOOP have native song concepts that must be preserved or explicitly migrated.

Credit: Elijah Lucian / Lucian Labs’ persistent-song workflow and integration, built on the host firmware’s project/storage system. SLOOP’s native song architecture is by isod89; JIANT credits its use. This is not a claim that every host’s song system originated in WaveLoop.
