# Bank-theme module

Reusable **bank → theme** mapping. This is independent of the sequence view,
fonts, widgets and any firmware's bank numbering.

- [bank_themes.h](bank_themes.h) / [bank_themes.c](bank_themes.c): palette tokens,
  immutable bindings, fallback lookup and RGB888/RGB565 conversion.
- [Tests](tests/bank_themes_test.c): bank IDs, missing bindings and all RGB565 colors.

```c
#include "bank_themes.h"

const fm1_bank_theme_binding themes[] = {
    { MY_DRUM_BANK, &FM1_THEME_WAVELOOP },
    { MY_SYNTH_BANK, &my_synth_theme }
};
const fm1_bank_theme *theme = fm1_theme_for_bank(
    themes, sizeof themes / sizeof themes[0], current_bank, &default_theme);
/* Any screen can use theme->colors: bank browser, patch editor, mixer, etc. */
```

Bank IDs are host-owned `uint32_t` values. First matching binding wins; an absent
or null theme uses the caller's fallback. Bindings and theme objects must remain
alive while used. Selection is passed to the lookup, never stored globally.

The built-in **WaveLoop** theme uses navy surfaces, white ink, blue selection and
gold accents from WaveLoop's design tokens. Fonts/assets are not bundled. Colors
are RGB888; use `fm1_theme_rgb565` at a 16-bit display boundary. The reverse helper
preserves every RGB565 value on a round trip.

The [sequence-view adapter](../sequence_view/examples/switchblade_adapter.h)
shows how to retain Switch Blade's native per-machine palettes while overriding
its drum bank with WaveLoop. Other screens can reuse this module without linking
`sequence_view.c`.

Elijah Lucian / Lucian Labs. GPL-3.0-only. Token/source pins and hashes are in
[provenance](../../provenance-sequence-view.json).
