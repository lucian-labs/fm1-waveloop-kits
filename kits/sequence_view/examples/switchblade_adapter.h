/* SPDX-License-Identifier: GPL-3.0-only
 * Copyright (C) 2026 Elijah Lucian / Lucian Labs
 * Example for Switch Blade 4f0de78. Include after home_sound_of in ui_big.c.
 * Copy both modules to firmware/src; include their C files once in felucca.c.
 * The host decides when to redraw; include steps, LEN, names, selection, mute,
 * transport and playhead in its dirty signature. No hardware/storage writes. */
#include "sequence_view.h"
#include "bank_themes.h"
static void fm1sv_sb_read(void *user, unsigned i, fm1sv_step *out) {
    const track_t *t = user;
    const step_t *s = &seq_steps(t)[i];
    *out = (fm1sv_step){0};
    out->kind = s->time == ST_NOTE ? FM1SV_NOTE : s->time == ST_TIE ? FM1SV_TIE : FM1SV_REST;
    out->count = s->n > 4 ? 4 : s->n;
    for(unsigned j=0;j<out->count;j++)out->note[j]=s->note[j];
    if(t->eng_req == ENGI_DRUM) {
        out->hits=s->hit;out->accents=s->acc;
        for(unsigned j=0;j<out->count;j++)out->hits|=(uint8_t)(1u<<drum_lane(out->note[j]));
    } else out->hold_q8=(uint16_t)step_hold_q8(s);
}
static void fm1sv_sb_rect(void *user,int x,int y,int w,int h,uint32_t color) {
    (void)user;cv_rect(x,y,w,h,(uint16_t)color);
}
static void fm1sv_sb_text(void *user,int x,int y,int width,unsigned face,const char *s,uint32_t color) {
    uint16_t bg=*(const uint16_t *)user;
    cv_free_text(x,y,face==FM1SV_SMALL?&AF_S:&AF_M,s,(uint16_t)color,bg,width);
}
/* Call for a dirty HOME row only. The caller retains existing knob/footer code. */
static void fm1sv_switchblade_home_row(unsigned index) {
    const track_t *t=&trk[index];
    char cat[16],num[16],patch[16],bank[20];
    home_sound_of(t,cat,num,patch);
    str_cpy(bank,t->eng_req==ENGI_DRUM?"WAVELOOP":user_of(t)<UP_SLOTS?"USER":ENGINES[t->eng_req%NENGINES]->name,sizeof bank);
    str_cpy(bank+str_len(bank)," ",2);
    {unsigned n=num[0]=='S'?5u:0u;char digits[3]={num[n],num[n+1],0};str_cpy(bank+str_len(bank),digits,3);}
    /* Theme follows THIS row's bank, not the currently selected track's palette. */
    const ui_pal_t *p=&UI_MACHINE_PALS[t->eng_req%NENGINES];
    fm1_bank_theme native={ENGINES[t->eng_req%NENGINES]->name,{
        fm1_theme_rgb888(p->bg),fm1_theme_rgb888(p->surf),fm1_theme_rgb888(p->text),
        fm1_theme_rgb888(ux_mix(p->bg,p->text,35)),fm1_theme_rgb888(p->accent),
        fm1_theme_rgb888(ux_mix(p->bg,p->text,10)),fm1_theme_rgb888(p->theme)}};
    static const fm1_bank_theme_binding bindings[]={{ENGI_DRUM,&FM1_THEME_WAVELOOP}};
    const fm1_bank_palette *theme=&fm1_theme_for_bank(bindings,1,t->eng_req%NENGINES,&native)->colors;
    fm1sv_colors colors={fm1_theme_rgb565(theme->background),
        fm1_theme_rgb565(ux.style?theme->background:theme->surface),
        fm1_theme_rgb565(theme->text),fm1_theme_rgb565(theme->muted),fm1_theme_rgb565(theme->accent),
        fm1_theme_rgb565(theme->grid),fm1_theme_rgb565(theme->selected)};
    uint16_t bg=index==song.sel?(uint16_t)colors.selected_background:(uint16_t)colors.background;
    fm1sv_canvas canvas={&bg,fm1sv_sb_rect,fm1sv_sb_text};
    fm1sv_track view={bank,patch,index+1,(unsigned)clamp(t->p[P_SLEN],1,NSTEP),t->seq_idx,
        t->eng_req==ENGI_DRUM,song.playing,index==song.sel,t->p[P_MUTE]!=0,
        (uint8_t)((song.rec>>index)&1u),(void *)t,fm1sv_sb_read};
    cv_begin(240,40,bg);
    (void)fm1sv_draw_track(&canvas,&colors,&view,(fm1sv_box){0,0,240,40});
    cv_blit(0,H_HEAD+index*40u);
}
