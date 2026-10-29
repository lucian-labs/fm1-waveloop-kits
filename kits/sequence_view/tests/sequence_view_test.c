/* SPDX-License-Identifier: GPL-3.0-only
 * Copyright (C) 2026 Elijah Lucian / Lucian Labs */
#include "../sequence_view.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
static fm1sv_step data[128];
static fm1sv_box bounds;
static unsigned reads,notes,accents,final_ink,wrap_ink,texts;
static uint32_t pixels[240*40];
static const fm1sv_colors colors={1,2,3,4,5,6,7};
static void read_step(void *u,unsigned i,fm1sv_step *s){
    unsigned length=*(unsigned *)u;assert(i<length);reads++;*s=data[i];
}
static void rect(void *u,int x,int y,int w,int h,uint32_t color){
    (void)u;
    assert(w>0&&h>0&&x>=bounds.x&&y>=bounds.y&&x+w<=bounds.x+bounds.width&&y+h<=bounds.y+bounds.height);
    assert(x+w<=240&&y+h<=40);
    if(color==colors.selected||color==colors.text) {
        notes++;if(x+w==bounds.x+bounds.width)final_ink++;
        if(x==bounds.x)wrap_ink++;
    }
    if(color==colors.accent)accents++;
    for(int j=y;j<y+h;j++)for(int i=x;i<x+w;i++)pixels[j*240+i]=color;
}
static void text(void *u,int x,int y,int w,unsigned face,const char *s,uint32_t color){
    (void)u;(void)color;assert(s&&w>0&&face<=FM1SV_NORMAL);
    assert(x>=bounds.x&&y>=bounds.y&&x+w<=bounds.x+bounds.width);texts++;
}
static void clear(void){
    memset(data,0,sizeof data);for(unsigned i=0;i<128;i++)data[i].kind=FM1SV_REST;
    memset(pixels,0,sizeof pixels);reads=notes=accents=final_ink=wrap_ink=texts=0;
}
int main(void){
    fm1sv_canvas canvas={0,rect,text};unsigned len=128;
    fm1sv_track t={"DRUM 01","808",1,128,127,0,0,1,0,0,&len,read_step};
    bounds=(fm1sv_box){26,17,208,18};clear();
    data[127]=(fm1sv_step){FM1SV_NOTE,1,{72},0,0,256};
    fm1sv_step before[128];memcpy(before,data,sizeof data);
    assert(!fm1sv_draw_sequence(&canvas,&colors,&t,bounds)&&final_ink&&notes==1);
    assert(!memcmp(before,data,sizeof data));
    /* A recorded hold wraps across the end; legacy TIE cells give the same span. */
    clear();data[127]=(fm1sv_step){FM1SV_NOTE,1,{60},0,0,512};
    assert(!fm1sv_draw_sequence(&canvas,&colors,&t,bounds)&&final_ink&&wrap_ink);
    clear();data[127]=(fm1sv_step){FM1SV_NOTE,1,{60},0,0,0};data[0].kind=FM1SV_TIE;
    assert(!fm1sv_draw_sequence(&canvas,&colors,&t,bounds)&&final_ink&&wrap_ink);
    /* Eighth lane and its accent must stay visible at the final step. */
    clear();t.drums=1;data[127]=(fm1sv_step){FM1SV_NOTE,0,{0},128,128,0};
    assert(!fm1sv_draw_sequence(&canvas,&colors,&t,bounds)&&accents==1);
    assert(pixels[(17+7*18/8)*240+233]==colors.accent);
    /* Muting suppresses the accent color too. */
    t.muted=1;accents=0;assert(!fm1sv_draw_sequence(&canvas,&colors,&t,bounds)&&!accents);
    /* Playhead stays visible at the right edge; out-of-range playheads are ignored. */
    clear();t.drums=t.muted=0;t.playing=1;
    assert(!fm1sv_draw_sequence(&canvas,&colors,&t,bounds)&&accents==1);
    t.playhead=128;accents=0;assert(!fm1sv_draw_sequence(&canvas,&colors,&t,bounds)&&!accents);
    /* Every supported length, including chords, at narrow/wide row sizes. */
    for(len=1;len<=128;len++)for(int w=96;w<=240;w+=16){
        clear();t.length=len;t.playing=0;t.drums=0;
        data[len-1]=(fm1sv_step){FM1SV_NOTE,4,{0,48,72,127},0,0,65535};
        bounds=(fm1sv_box){0,0,w,40};
        assert(!fm1sv_draw_track(&canvas,&colors,&t,bounds)&&texts==4);
    }
    t.length=0;assert(fm1sv_draw_track(&canvas,&colors,&t,bounds)==-1);
    t.length=129;assert(fm1sv_draw_track(&canvas,&colors,&t,bounds)==-1);
    t.length=128;assert(fm1sv_draw_track(&canvas,&colors,&t,(fm1sv_box){0,0,240,37})==-1);
    assert(fm1sv_draw_track(0,&colors,&t,bounds)==-1);
    puts("sequence view: final step, holds/ties/wrap, drums, mute, playhead, 128 lengths, bounds and read-only state pass");
    return 0;
}
