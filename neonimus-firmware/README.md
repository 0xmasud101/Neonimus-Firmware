# Neonimus Firmware

Neonimus is an open-source fork of [Bruce](https://github.com/pr3y/Bruce),
built for the author's own custom handheld hardware. It is a multi-tool
for **authorized** WiFi/BLE/RF security testing, RFID/IR work, and (new
in this fork) on-device voice control and an MCP bridge for LLM-assisted
operation.

> **Status:** Phase 1 (board bring-up) in progress. See
> [Build order](#build-order) below.

## ⚠️ Authorized use only

This firmware includes tools that can disrupt or intercept wireless
traffic - WiFi deauthentication, BLE spam, Evil Portal captive-portal
testing, Sub-GHz replay, and more (inherited from upstream Bruce, plus
whatever Neonimus adds on top).

- Only use these features on networks, devices, and accounts **you own**
  or have **explicit written authorization** to test.
- Unauthorized use of deauth, rogue-AP/captive-portal, or signal-replay
  tools against networks or devices you don't own or control is illegal
  in most jurisdictions and is **not** an intended or supported use of
  this project.
- The maintainers and contributors accept no liability for misuse. If
  you're not sure whether a test is authorized, don't run it.

## Hardware (BOM)

| Part | Spec | Notes |
|---|---|---|
| MCU | ESP32-S3-DevKitC-1 N16R8 | 16MB flash, 8MB octal PSRAM, WiFi 2.4GHz + BLE |
| Display | 1.8" TFT, ST7735 driver, 128x160 | [source](https://iotnest.bd/18-tft-lcd-display-st7735-driver) - verify tab-color variant, see `boards/neonimus-core/pins_arduino.h` |
| Storage | microSD module, SPI | shares bus with display, own CS |
| Mic | INMP441, I2S | voice command input |
| Speaker amp | MAX98357A, I2S | voice feedback output |
| Sub-GHz *(optional)* | CC1101 | feature-gated, Phase 6 |
| RFID/NFC *(optional)* | PN532, I2C | feature-gated, Phase 6 |
| IR *(optional)* | IR LED + receiver | feature-gated, Phase 6 |
| 2.4GHz RF *(optional)* | NRF24L01 | feature-gated, Phase 6 - mousejacking/spectrum |
| GPS *(optional)* | NEO-6M or ATGM336H, UART | feature-gated, Phase 6 - wardriving/location tagging |
| 5GHz WiFi *(optional)* | external module | **hardware-dependent, not guaranteed** - ESP32-S3's native radio is 2.4GHz-only; this needs a board/antenna setup that actually supports it |
| Enclosure | 3D-printed handheld, console-style | USB-C, SD slot, speaker grille, mic hole, power switch all accessible |

**Note:** the brief for this build described a 4-5" screen form factor,
but the display actually sourced is a 1.8" panel. That's a real size
mismatch for a "pocket router"-style console face - worth deciding now
whether the case design shrinks to match the 1.8" screen, or a larger
panel gets swapped in before the enclosure is finalized, since the pin
map below is specific to the ST7735 wiring either way.

See `boards/neonimus-core/pins_arduino.h` for the full, commented pin
assignment, including which GPIOs are permanently unavailable on the
N16R8 (octal PSRAM) variant.

### Wiring diagram

Placeholder - `docs/wiring/README.md`. Fill in with a Fritzing export or
hand-drawn diagram once the board is wired.

## Repo layout

```
neonimus-firmware/            (this repo = your fork of pr3y/Bruce)
├── boards/
│   ├── neonimus-core/        # NEW - this hardware's pin map + board .ini
│   │   ├── neonimus-core.ini
│   │   ├── pins_arduino.h
│   │   └── interface.cpp
│   ├── _boards_json/
│   │   └── neonimus-core.json
│   └── pinouts/pins_arduino.h  # UPSTREAM, shared dispatcher - 1-line patch, see PATCHES.md
├── branding/
│   └── neonimus_config.h     # NEW - name/colors/feature-gate header (Phase 2)
├── modules/
│   ├── voice/                 # NEW - Phase 3, ESP-SR voice commands
│   └── mcp_bridge/            # NEW - Phase 4, PC-side MCP bridge
├── partitions/
│   └── neonimus_16mb_ota.csv # NEW - 16MB partition table w/ OTA + LittleFS
├── docs/
│   ├── wiring/                # wiring diagram placeholder
│   └── flasher/                # Phase 5, web flasher assets
├── PATCHES.md                 # the short, tracked list of upstream edits
├── LICENSE                    # AGPL-3.0, same as upstream Bruce
└── README.md                  # this file
```

Everything under `boards/neonimus-core/`, `branding/`, `modules/`, and
`partitions/` is **new, additive files** - upstream Bruce code
(`src/`, `lib/`, the rest of `boards/`) stays untouched, so
`git fetch upstream && git rebase upstream/main` (or periodic merges)
stays clean. The **one** necessary edit to a shared upstream file is
tracked, with its exact diff, in `PATCHES.md` - keep that list short.

## Build instructions

1. Fork `pr3y/Bruce` on GitHub, clone your fork.
2. Copy this repo's `boards/`, `branding/`, `modules/`, and
   `partitions/` directories on top of your fork's root (same relative
   paths).
3. Apply the one-line dispatcher patch in `PATCHES.md`.
4. `pio run -e neonimus-core`

## Flashing instructions

**USB (now):**
```sh
pio run -e neonimus-core -t upload --upload-port /dev/ttyACM0
```
or, from a prebuilt binary:
```sh
esptool.py --port /dev/ttyACM0 write_flash 0x0 Neonimus-neonimus-core.bin
```

**Browser-based web flasher (planned, Phase 5):** an
[ESP Web Tools](https://esphome.github.io/esp-web-tools/)-style page,
following the same pattern as Bruce's own flasher at
[bruce.computer/flasher](https://bruce.computer/flasher). Placeholder
in `docs/flasher/`.

## Build order

- **Phase 1** - get Bruce's existing WiFi/BLE toolset compiling and
  running on `neonimus-core` (this phase).
- **Phase 2** - apply Neonimus branding (name/logo/color theme) via
  `branding/neonimus_config.h` + Bruce's runtime theme system.
- **Phase 3** - voice control (`modules/voice/`), fixed command set,
  ESP-SR, no cloud dependency.
- **Phase 4** - PC-side MCP bridge (`modules/mcp_bridge/`).
- **Phase 5** - browser-based web flasher for public distribution.
- **Phase 6** - optional modules (Sub-GHz/IR/RFID) as compile-time
  feature flags.

## License

[AGPL-3.0](LICENSE), matching upstream Bruce. This means: if you run a
modified version of this firmware's network-facing parts (e.g. the
Evil Portal web UI, the planned MCP bridge) as a service reachable by
others, you must also make that modified source available to them -
not just binaries. See `THIRD_PARTY.md` (carry over from upstream once
forked) for per-dependency attribution.
