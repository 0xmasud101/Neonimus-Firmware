# Web flasher - Phase 5 (not started)

Plan: an [ESP Web Tools](https://esphome.github.io/esp-web-tools/) page,
same pattern as Bruce's own flasher at https://bruce.computer/flasher.

Needs, once there's a release binary to point at:
- `manifest.json` listing the `neonimus-core` build (chip family `ESP32-S3`, improv-wifi optional)
- merged binary (bootloader + partition table + firmware) built with
  `esptool.py --chip esp32s3 merge_bin` against `partitions/neonimus_16mb_ota.csv`
- static page (can be a GitHub Pages deploy of this repo) embedding the
  `<esp-web-install-button>` custom element
