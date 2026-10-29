# FM-1 WaveLoop Kits

Port **SHAYPE**, **persistent songs**, **WaveLoop’s modified 808 drums**, the **kit-lane drum sequencer**, and the **full-track sequence view** into FM-1 source firmware. Reuse bank themes across screens.

By Elijah Lucian / Lucian Labs, building on the credited firmware authors below.

## Start here

1. Pick your [distro map](#distro-maps).
2. Follow the feature recipe and [porting checklist](PORTING.md).
3. Run `python3 tools/check.py` to verify the bundled SHAYPE core and kit integrity.

| Feature | Included | Guide |
| --- | --- | --- |
| Sequence view | Portable C renderer, full-pattern previews and Switch Blade adapter | [Sequence view](kits/sequence_view/README.md) |
| Bank themes | Reusable bank-to-theme mapping; WaveLoop drum theme | [Themes](kits/bank_themes/README.md) |
| SHAYPE / Shape Arp | Portable C core and parity fixtures | [Shape](kits/shape/README.md) |
| Persistent songs | Autosave/resume contract and donor paths | [Songs](kits/persistent_songs/README.md) |
| Modified 808 drums | Voice, controls and bank integration recipe | [808](kits/drums_808/README.md) |
| Drum sequencer | Exact-base Switch Blade patch and adaptation recipe | [Sequencer](kits/drum_sequencer/README.md) |

This is a source porting kit, not a universal firmware installer. Switch Blade is the reference implementation; other rows state what is present and what still needs porting. Shared hardware does not make project formats or flash layouts interchangeable.

## Distro maps

- [switchblade](distros/switchblade.md)
- [melodee](distros/melodee.md)
- [jiant](distros/jiant.md)
- [sloop-fm1](distros/sloop-fm1.md)
- [felucca-kit](distros/felucca-kit.md)
- [felucca-stock](distros/felucca-stock.md)
- [FM1-MOVE](distros/FM1-MOVE.md)
- [NoteSorcery](distros/NoteSorcery.md)
- [analogBEAST](distros/analogBEAST.md)
- [estampie](distros/estampie.md)
- [fm1-dub](distros/fm1-dub.md)
- [fm1-tribe](distros/fm1-tribe.md)
- [fm1-x0x](distros/fm1-x0x.md)
- [ghoulbox-fm1-dungeon-synth](distros/ghoulbox-fm1-dungeon-synth.md)
- [hortator](distros/hortator.md)
- [orbit](distros/orbit.md)
- [pigeon](distros/pigeon.md)
- [skiff](distros/skiff.md)

Other source distros: use the [generic integration contract](PORTING.md). No exact map is claimed yet for Prysm, april-os, mc-1, unibox, zp12, fm1-base or fm1_open. Closed vendor firmware requires an available, appropriately licensed source/build path; this kit cannot patch an opaque binary.

## Controller setup tool

Use [Arturia MiniLab CLI](https://github.com/ELI7VH/arturia-minilab-cli) to back up,
compare and upload MiniLab 3 User presets without MIDI Control Center. Uploads
back up the target slot automatically and verify all319 mapping fields.

Follow its setup instructions, then upload your native `.minilab3` file:

```sh
minilab preset upload YOUR-PRESET.minilab3 --slot 1
```

Choose your intended User slot (1–5). The
[fm1-sb-live preset](https://github.com/ELI7VH/switchblade/blob/2bd136d/controllers/fm1-sb-live.minilab3)
maps K1–4 to ADSR and K5–8 to repeat, dirt, delay and filter on the matching
WaveLoop Switch Blade build. Other distros need matching MIDI assignments.
The CLI is tested with MiniLab 3 firmware1.2.0.69, including restart persistence;
it programs controller mappings and does not install FM-1 firmware.

## Credits and license

Read [CREDITS.md](CREDITS.md) before reusing code. Bundled source, fixtures and patch are GPL-3.0-only; original notices remain intact. This kit includes no firmware binaries, device backups, SDK blobs or sample packs. Linked optional dependencies retain their own licenses.

Pinned source revisions and hashes live in [provenance.json](provenance.json); exact distro paths live in [manifest.json](distros/manifest.json).

## 128-step extension

[Eight-bar patterns at 1/16](kits/128_steps/README.md): exact-base Switch Blade patch, legacy import and atomic extended saves. Other distros need their own storage audit.
