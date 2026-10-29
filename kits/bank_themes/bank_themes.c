/* SPDX-License-Identifier: GPL-3.0-only
 * Copyright (C) 2026 Elijah Lucian / Lucian Labs
 * WaveLoop colors: ds/src/tokens.css, pinned in provenance-sequence-view.json. */
#include "bank_themes.h"
const fm1_bank_theme FM1_THEME_WAVELOOP={"WaveLoop",{
    0x141920, /* --wl-navy */
    0x202833, /* --wl-navy-lift */
    0xeaecf2, /* --ink */
    0xaaafbd, /* --muted */
    0xffa40a, /* --accent-2, gold */
    0x383c4a, /* --line */
    0x7eb7ff  /* --wl-blue-hi */
}};
const fm1_bank_theme *fm1_theme_for_bank(const fm1_bank_theme_binding *bindings,
        size_t count,uint32_t bank,const fm1_bank_theme *fallback) {
    if(bindings)for(size_t i=0;i<count;i++)if(bindings[i].bank==bank)
        return bindings[i].theme?bindings[i].theme:fallback;
    return fallback;
}
uint16_t fm1_theme_rgb565(uint32_t c) {
    return (uint16_t)(((c>>19)&31u)<<11|((c>>10)&63u)<<5|((c>>3)&31u));
}
uint32_t fm1_theme_rgb888(uint16_t c) {
    uint32_t r=c>>11,g=(c>>5)&63u,b=c&31u;
    return ((r<<3|r>>2)<<16)|((g<<2|g>>4)<<8)|(b<<3|b>>2);
}
