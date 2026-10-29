#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-only
"""Check portable sequence-view/theme modules; optionally compile the pinned adapter."""
import hashlib
import json
import os
from pathlib import Path
import shlex
import subprocess
import tempfile
import xml.etree.ElementTree as ET

ROOT = Path(__file__).resolve().parents[1]
PIN = json.loads((ROOT / 'provenance-sequence-view.json').read_text())
for item in PIN['files']:
    assert hashlib.sha256((ROOT / item['path']).read_bytes()).hexdigest() == item['sha256'], item['path']
CC = shlex.split(os.environ.get('CC', 'cc'))
VIEW = ROOT / 'kits/sequence_view'
THEME = ROOT / 'kits/bank_themes'
with tempfile.TemporaryDirectory(prefix='fm1-view-') as folder:
    tmp = Path(folder)
    for name, sources in [
        ('view', [VIEW/'sequence_view.c', VIEW/'tests/sequence_view_test.c']),
        ('themes', [THEME/'bank_themes.c', THEME/'tests/bank_themes_test.c']),
        ('demo', [VIEW/'sequence_view.c', THEME/'bank_themes.c', VIEW/'examples/demo.c'])
    ]:
        binary = tmp / name
        subprocess.run(CC + ['-std=c99', '-Wall', '-Wextra', '-Werror'] +
                       [str(p) for p in sources] + ['-o', str(binary)], check=True)
        result = subprocess.check_output([str(binary)], text=True)
        if name == 'demo':
            svg = ET.fromstring(result)
            assert svg.attrib['viewBox'] == '0 0 240 160'
            assert 'WAVELOOP 01' in result and '#141920' in result
        else:
            print(result.strip())

    donor = Path(os.environ.get('SWITCHBLADE_DIR', str(ROOT.parent/'switchblade')))
    if donor.is_dir() and (donor/'build/gen/ui_fonts.h').exists():
        revision = PIN['donor']['commit']
        archive = subprocess.Popen(['git', 'archive', revision, 'firmware', 'tests'], cwd=donor, stdout=subprocess.PIPE)
        subprocess.run(['tar', '-xf', '-', '-C', str(tmp)], stdin=archive.stdout, check=True)
        archive.stdout.close()
        assert archive.wait() == 0
        (tmp/'build').mkdir()
        (tmp/'build/gen').symlink_to((donor/'build/gen').resolve(), target_is_directory=True)
        for p in [VIEW/'sequence_view.c', VIEW/'sequence_view.h', THEME/'bank_themes.c', THEME/'bank_themes.h']:
            (tmp/'firmware/src'/p.name).write_bytes(p.read_bytes())
        (tmp/'firmware/src/fm1sv_adapter.h').write_bytes((VIEW/'examples/switchblade_adapter.h').read_bytes())
        ui = tmp/'firmware/src/ui_big.c'
        source = ui.read_text().replace('#define HS_X', '#include "sequence_view.c"\n#include "bank_themes.c"\n#include "fm1sv_adapter.h"\n#define HS_X', 1)
        a = source.index('static void home_unit(uint32_t c)')
        b = source.index('/* HOME\'s cell labels', a)
        source = source[:a] + 'static void home_unit(uint32_t c) { fm1sv_switchblade_home_row(c); }\n\n' + source[b:]
        ui.write_text(source)
        (tmp/'adapter_test.c').write_text('''
#define UI_TEST_NO_MAIN 1
#include "tests/ui_test.c"
#include <assert.h>
int main(void) {
 ui_power_on();go_home();frame();
 assert(swap16(host_screen[145*240])==fm1_theme_rgb565(FM1_THEME_WAVELOOP.colors.background));
 assert(swap16(host_screen[65*240])==UI_MACHINE_PALS[ENGI_WAVE].bg);
 song.sel=3;ui.force=1;frame();
 assert(swap16(host_screen[145*240])==fm1_theme_rgb565(FM1_THEME_WAVELOOP.colors.surface));
 assert(swap16(host_screen[25*240])==UI_MACHINE_PALS[ENGI_OBX].bg);
 set_engine_of(&trk[1],ENGI_DRIFT);frame();
 assert(swap16(host_screen[65*240])==UI_MACHINE_PALS[ENGI_DRIFT].bg);
 puts("Switch Blade adapter: pinned source compiles/renders; native bank palettes and WaveLoop DRUM pass");
 return 0;
}
''')
        subprocess.run(CC + ['-O1', '-w', '-Ibuild/gen', '-Ifirmware/src', '-Itests',
                       'adapter_test.c',
                       '-lm', '-o', str(tmp/'adapter-test')], cwd=tmp, check=True)
        print(subprocess.check_output([str(tmp/'adapter-test')], cwd=tmp, text=True).strip().splitlines()[-1])
    else:
        print('Adapter compile NOT CHECKED: set SWITCHBLADE_DIR to the donor checkout with build/gen tables.')
print('PASS: module hashes, strict C99 builds, sequence rendering, theme lookup and SVG demo')
