/* SPDX-License-Identifier: GPL-3.0-only
 * Copyright (C) 2026 Elijah Lucian / Lucian Labs */
#ifndef FM1_BANK_THEMES_H
#define FM1_BANK_THEMES_H
#include <stddef.h>
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
/* RGB888 tokens, independent of any widget, bank numbering or framebuffer. */
typedef struct {
    uint32_t background, surface, text, muted, accent, grid, selected;
} fm1_bank_palette;
typedef struct { const char *name; fm1_bank_palette colors; } fm1_bank_theme;
typedef struct { uint32_t bank; const fm1_bank_theme *theme; } fm1_bank_theme_binding;
extern const fm1_bank_theme FM1_THEME_WAVELOOP;
/* First matching binding wins; a missing/NULL binding uses the caller's fallback.
 * Caller owns bindings/themes and keeps them alive. No mutable global selection. */
const fm1_bank_theme *fm1_theme_for_bank(const fm1_bank_theme_binding *, size_t count,
                                       uint32_t bank, const fm1_bank_theme *fallback);
uint16_t fm1_theme_rgb565(uint32_t rgb888);
uint32_t fm1_theme_rgb888(uint16_t rgb565);
#ifdef __cplusplus
}
#endif
#endif
