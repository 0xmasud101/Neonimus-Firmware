#ifndef NEONIMUS_CONFIG_H
#define NEONIMUS_CONFIG_H
/*
 * Neonimus Firmware - branding layer
 * This is the ONLY file Phase 2 ("apply Neonimus branding") should need
 * to touch. It is pulled in via `-include neonimus_config.h` in
 * boards/neonimus-core/neonimus-core.ini, so it applies before any
 * upstream header is compiled - no upstream source file is edited for
 * branding.
 *
 * Bruce already supports most of this at runtime through its own theme
 * system (src/core/theme.h): a JSON theme file + boot image/sound can
 * be dropped onto the SD card / LittleFS without touching firmware at
 * all. Use THIS file only for things that must be baked in at compile
 * time (default colors before a theme file is ever loaded, the name
 * shown before first boot, feature-module gates).
 */

// ---------------------------------------------------------------------
// Identity
// ---------------------------------------------------------------------
#ifndef DEVICE_NAME
#define DEVICE_NAME "Neonimus"
#endif
#define NEONIMUS_FW_VARIANT "neonimus-core"

// ---------------------------------------------------------------------
// Default theme colors (RGB565), used until a theme JSON overrides them.
// Bruce's defaults live in src/core/theme.h as DEFAULT_PRICOLOR /
// DEFAULT_SECCOLOR (0xA80F / 0xCB76) - override here instead of editing
// that upstream file.
// ---------------------------------------------------------------------
#undef DEFAULT_PRICOLOR
#undef DEFAULT_SECCOLOR
#define DEFAULT_PRICOLOR 0x07FF // TODO: pick your Neonimus accent (cyan placeholder)
#define DEFAULT_SECCOLOR 0xF81F // TODO: pick your Neonimus secondary (magenta placeholder)

// ---------------------------------------------------------------------
// Boot logo
// Bruce boot images are loaded at runtime from the theme's boot_img
// path (see src/core/theme.h -> themeFiles::boot_img), not compiled
// in. Put your logo as an on-disk asset instead of a byte array here:
//   sd_files/theme/neonimus/boot.jpg  (or whatever format the running
//   Bruce version's theme loader expects - check sd_files/ layout in
//   upstream after forking, it may have changed between versions)
// If you later DO need a compiled-in splash (e.g. shown before the SD
// card / LittleFS theme loads), that's a genuine new feature, not a
// branding-layer swap - track it in modules/ instead of here.
// ---------------------------------------------------------------------
// #define NEONIMUS_LOGO_BYTES { ... }  // intentionally left unset, see above

// ---------------------------------------------------------------------
// Phase 6 optional-module compile-time gates
// Mirrors the commented-out build_flags in neonimus-core.ini - flip
// both in step with each other.
// ---------------------------------------------------------------------
// #define NEONIMUS_HAS_CC1101  1
// #define NEONIMUS_HAS_PN532   1
// #define NEONIMUS_HAS_IR      1
// #define NEONIMUS_HAS_NRF24   1
// #define NEONIMUS_HAS_GPS     1
// #define NEONIMUS_HAS_VOICE       1 // Phase 3
// #define NEONIMUS_HAS_MCP_BRIDGE  1 // Phase 4

#endif /* NEONIMUS_CONFIG_H */
