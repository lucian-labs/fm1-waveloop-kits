/* SPDX-License-Identifier: GPL-3.0-only
 * Copyright (C) 2026 Elijah Lucian / Lucian Labs
 * Adapted from WaveLoop Switch Blade's HOME overview; see README.md and CREDITS.md. */
#ifndef FM1_SEQUENCE_VIEW_H
#define FM1_SEQUENCE_VIEW_H
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
#define FM1SV_MAX_STEPS 128u
#define FM1SV_MAX_NOTES 4u
enum { FM1SV_NOTE, FM1SV_TIE, FM1SV_REST };
enum { FM1SV_SMALL, FM1SV_NORMAL };
typedef struct {
    uint8_t kind, count, note[FM1SV_MAX_NOTES];
    uint8_t hits, accents; /* eight drum lanes, bit 0..7 */
    uint16_t hold_q8;     /* synth duration in 1/256 steps; 0 follows TIE cells */
} fm1sv_step;
typedef struct {
    void *user;
    void (*rect)(void *, int x, int y, int w, int h, uint32_t color);
    /* Draw from the top-left, clipping to width. The host supplies its fonts. */
    void (*text)(void *, int x, int y, int width, unsigned face,
                 const char *value, uint32_t color);
} fm1sv_canvas;
typedef struct {
    uint32_t background, selected_background, text, dim, accent, grid, selected;
} fm1sv_colors;
typedef struct { int x, y, width, height; } fm1sv_box;
typedef struct {
    const char *bank;  /* e.g. "OB-Z 01" or "USER 07" */
    const char *patch;
    unsigned number, length, playhead;
    uint8_t drums, playing, selected, muted, recording;
    void *user;
    /* Read only index < length. No allocation, scheduling or storage callbacks. */
    void (*read_step)(void *, unsigned index, fm1sv_step *out);
} fm1sv_track;
/* Return 0 on success, -1 on invalid arguments. Never change musical data.
 * The host owns redraw/dirty tracking and a coherent snapshot while drawing. */
int fm1sv_draw_sequence(const fm1sv_canvas *, const fm1sv_colors *,
                       const fm1sv_track *, fm1sv_box);
int fm1sv_draw_track(const fm1sv_canvas *, const fm1sv_colors *,
                    const fm1sv_track *, fm1sv_box);
#ifdef __cplusplus
}
#endif
#endif
