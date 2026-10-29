/* SPDX-License-Identifier: GPL-3.0-only
 * Copyright (C) 2026 Elijah Lucian / Lucian Labs
 * Full-pattern layout adapted from WaveLoop Switch Blade, based on Felucca's UI.
 * Upstream firmware UI: Leo Kuroshita / Hugelton Instruments and Ollie Nicklin.
 */
#include "sequence_view.h"
#include <limits.h>

static int fm1sv_valid(const fm1sv_canvas *c, const fm1sv_colors *p,
                 const fm1sv_track *t, fm1sv_box b, int minw, int minh) {
    return c && p && t && c->rect && t->read_step &&
        t->length && t->length <= FM1SV_MAX_STEPS &&
        b.x >= 0 && b.y >= 0 && b.width >= minw && b.height >= minh &&
        b.width <= 4096 && b.height <= 4096 &&
        b.x <= INT_MAX-b.width && b.y <= INT_MAX-b.height;
}
static void fm1sv_read(const fm1sv_track *t, unsigned i, fm1sv_step *s) {
    *s = (fm1sv_step){0};
    t->read_step(t->user, i, s);
    if (s->count > FM1SV_MAX_NOTES) s->count = FM1SV_MAX_NOTES;
    for (unsigned j=0;j<s->count;j++) if(s->note[j]>127) s->note[j]=127;
}
static void fm1sv_number(char *s, unsigned v) {
    char reverse[10]; unsigned n=0;
    do { reverse[n++]=(char)('0'+v%10);v/=10; } while(v);
    for(unsigned i=0;i<n;i++) s[i]=reverse[n-i-1];
    s[n]=0;
}
int fm1sv_draw_sequence(const fm1sv_canvas *c, const fm1sv_colors *p,
                       const fm1sv_track *t, fm1sv_box b) {
    if(!fm1sv_valid(c,p,t,b,1,16)) return -1;
    unsigned lo=127,hi=0,len=t->length;
    uint32_t ink=t->muted?p->dim:t->selected?p->selected:p->text;
    for(unsigned i=0;i<len;i++) {
        fm1sv_step s;fm1sv_read(t,i,&s);
        if(s.kind==FM1SV_NOTE) for(unsigned j=0;j<s.count;j++) {
            if(s.note[j]<lo)lo=s.note[j];if(s.note[j]>hi)hi=s.note[j];
        }
    }
    if(hi<lo)lo=48,hi=60;
    if(hi-lo<12)hi=lo+12;
    for(unsigned i=0;i<len;i+=16)
        c->rect(c->user,b.x+(int)(i*(unsigned)b.width/len),b.y,1,b.height,p->grid);
    if(t->playing && t->playhead<len)
        c->rect(c->user,b.x+(int)(t->playhead*(unsigned)b.width/len),b.y,1,b.height,p->accent);
    for(unsigned i=0;i<len;i++) {
        fm1sv_step s;fm1sv_read(t,i,&s);
        if(s.kind!=FM1SV_NOTE)continue;
        unsigned x=i*(unsigned)b.width/len,x1=(i+1)*(unsigned)b.width/len;
        if(t->drums) {
            for(unsigned j=0;j<8;j++) if((s.hits>>j)&1)
                c->rect(c->user,b.x+(int)x,b.y+(int)(j*(unsigned)b.height/8),
                        (int)(x1>x?x1-x:1),1,t->muted?p->dim:(s.accents>>j)&1?p->accent:ink);
        } else if(s.count) {
            unsigned n=1,q=s.hold_q8;
            if(!q) {
                fm1sv_step next;
                while(n<len) { fm1sv_read(t,(i+n)%len,&next);if(next.kind!=FM1SV_TIE)break;n++; }
                q=n*256;
            }
            if(q>len*256)q=len*256;
            unsigned w=((i*256+q)*(unsigned)b.width/(len*256))-x;
            if(!w)w=1;
            for(unsigned j=0;j<s.count;j++) {
                int y=b.y+b.height-2-(int)(((s.note[j]<lo?lo:s.note[j]>hi?hi:s.note[j])-lo)*(unsigned)(b.height-3)/(hi-lo));
                unsigned tail=(unsigned)b.width-x;
                c->rect(c->user,b.x+(int)x,y,(int)(w>tail?tail:w),2,ink);
                if(w>tail)c->rect(c->user,b.x,y,(int)(w-tail),2,ink);
            }
        }
    }
    return 0;
}
int fm1sv_draw_track(const fm1sv_canvas *c, const fm1sv_colors *p,
                    const fm1sv_track *t, fm1sv_box b) {
    if(!fm1sv_valid(c,p,t,b,96,38)||!c->text) return -1;
    uint32_t bg=t->selected?p->selected_background:p->background;
    uint32_t ink=t->muted?p->dim:p->text;
    char value[11];
    c->rect(c->user,b.x,b.y,b.width,b.height,bg);
    c->rect(c->user,b.x+4,b.y+b.height-1,b.width-8,1,p->grid);
    if(t->selected)c->rect(c->user,b.x+2,b.y+2,3,b.height-5,p->selected);
    fm1sv_number(value,t->number);
    c->text(c->user,b.x+8,b.y+3,16,FM1SV_NORMAL,value,ink);
    fm1sv_number(value,t->length);
    c->text(c->user,b.x+4,b.y+24,21,FM1SV_SMALL,value,p->dim);
    if(t->recording)c->rect(c->user,b.x+11,b.y+20,4,3,p->accent);
    int bankw=(b.width-32)*36/100,patchx=26+bankw+3;
    c->text(c->user,b.x+26,b.y+2,bankw,FM1SV_SMALL,t->bank?t->bank:"",t->muted?p->dim:p->selected);
    c->text(c->user,b.x+patchx,b.y+1,b.width-patchx-6,FM1SV_NORMAL,t->patch?t->patch:"",ink);
    return fm1sv_draw_sequence(c,p,t,(fm1sv_box){b.x+26,b.y+17,b.width-32,b.height-22});
}
