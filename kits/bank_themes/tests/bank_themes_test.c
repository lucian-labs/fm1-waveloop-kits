/* SPDX-License-Identifier: GPL-3.0-only */
#include "../bank_themes.h"
#include <assert.h>
#include <stdio.h>
int main(void){
    const fm1_bank_theme fallback={"Other",{0}};
    const fm1_bank_theme_binding bindings[]={{77,&fallback},{999,&FM1_THEME_WAVELOOP}};
    assert(fm1_theme_for_bank(bindings,2,77,0)==&fallback);
    assert(fm1_theme_for_bank(bindings,2,999,0)==&FM1_THEME_WAVELOOP);
    assert(fm1_theme_for_bank(bindings,2,1,&fallback)==&fallback);
    assert(fm1_theme_for_bank(0,999,1,&fallback)==&fallback);
    const fm1_bank_theme_binding missing={1,0};
    assert(fm1_theme_for_bank(&missing,1,1,&fallback)==&fallback);
    for(unsigned i=0;i<65536;i++)assert(fm1_theme_rgb565(fm1_theme_rgb888((uint16_t)i))==i);
    assert(FM1_THEME_WAVELOOP.colors.background==0x141920);
    puts("bank themes: arbitrary bank IDs, fallback, WaveLoop tokens, all RGB565 round trips pass");
    return 0;
}
