# Wiring diagram - placeholder

Fill in once the board is physically wired. Suggested source of truth:
`boards/neonimus-core/pins_arduino.h` (the pin numbers there are
authoritative; keep this diagram in sync with it, not the other way
around).

TODO:
- [ ] Fritzing / KiCad sketch or hand-drawn photo of the breadboard/perfboard layout
- [ ] Power budget note (3V3 rail: display + SD + mic + amp + any optional modules - check total draw against the ESP32-S3's onboard regulator headroom, add an external 3V3 regulator if the handheld's battery/charge circuit doesn't already provide one)
