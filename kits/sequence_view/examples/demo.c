/* SPDX-License-Identifier: GPL-3.0-only
 * Copyright (C) 2026 Elijah Lucian / Lucian Labs */
#include "../sequence_view.h"
#include "../../bank_themes/bank_themes.h"
#include <stdio.h>
static fm1sv_step steps[4][FM1SV_MAX_STEPS];
static void read_step(void *u,unsigned i,fm1sv_step *s){*s=((fm1sv_step *)u)[i];}
static void rect(void *u,int x,int y,int w,int h,uint32_t color){
    fprintf(u,"<rect x='%d' y='%d' width='%d' height='%d' fill='#%06x'/>\n",x,y,w,h,(unsigned)color);
}
static void text(void *u,int x,int y,int width,unsigned face,const char *value,uint32_t color){
    FILE *f=u;
    fprintf(f,"<svg x='%d' y='%d' width='%d' height='14' overflow='hidden'><text x='0' y='11' font-family='monospace' font-size='%u' fill='#%06x'>",x,y,width,face==FM1SV_SMALL?9:11,(unsigned)color);
    for(;*value;value++) {if(*value=='&')fputs("&amp;",f);else if(*value=='<')fputs("&lt;",f);else if(*value=='>')fputs("&gt;",f);else fputc(*value,f);}
    fputs("</text></svg>\n",f);
}
int main(void){
    const char *bank[4]={"OB-Z 01","WAVE 02","NANO 03","WAVELOOP 01"};
    const char *patch[4]={"SAW LEAD","GLASS","ACID TRAX","808"};
    fm1sv_canvas canvas={stdout,rect,text};
    const fm1_bank_theme obz={"OB-Z",{0x071015,0x10202b,0xe8eef3,0x687780,0xff8264,0x263640,0x80c6ed}};
    const fm1_bank_theme wave={"WAVE",{0x17120b,0x261c10,0xffebc9,0x998464,0xffc060,0x40301d,0xe6aa4c}};
    const fm1_bank_theme nano={"NANO",{0xc5c9c4,0xe0e3dc,0x202b29,0x747e77,0xb64830,0x9ba49c,0x355e58}};
    const fm1_bank_theme_binding banks[]={{10,&obz},{20,&wave},{30,&nano},{40,&FM1_THEME_WAVELOOP}};
    puts("<svg xmlns='http://www.w3.org/2000/svg' width='720' height='480' viewBox='0 0 240 160'>");
    for(unsigned t=0;t<4;t++){
        for(unsigned i=0;i<128;i++) steps[t][i].kind=FM1SV_REST;
        for(unsigned i=0;i<128;i+=4){
            fm1sv_step *s=&steps[t][i];s->kind=FM1SV_NOTE;
            if(t==3){s->hits=(uint8_t)(1u<<((i/4)%8));if(i%16==0)s->hits|=1;}
            else{s->count=1;s->note[0]=(uint8_t)(48+t*12+(i/8)%12);s->hold_q8=384;}
        }
        const fm1_bank_palette *p=&fm1_theme_for_bank(banks,4,(t+1)*10,&obz)->colors;
        fm1sv_colors row={p->background,p->surface,p->text,p->muted,p->accent,p->grid,p->selected};
        fm1sv_track track={bank[t],patch[t],t+1,128,31+t*32,t==3,1,t==0,0,0,steps[t],read_step};
        if(fm1sv_draw_track(&canvas,&row,&track,(fm1sv_box){0,(int)t*40,240,40}))return 1;
    }
    puts("</svg>");return 0;
}
