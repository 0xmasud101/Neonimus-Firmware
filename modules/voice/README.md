# modules/voice/ - Phase 3 (not started)

Fixed-vocabulary, on-device voice control using Espressif's ESP-SR
(wake-word + keyword spotting, no cloud dependency), driven by the
INMP441 mic and MAX98357A feedback speaker wired in `boards/neonimus-core/pins_arduino.h`.

Planned command set (from the project brief - keep it fixed/closed, do
not add open-ended command parsing without re-checking authorized-use
scope):
- "scan wifi"
- "start deauth test"
- "capture handshake"
- "stop"
- "save log"
- "evil portal on/off"

Will be gated behind `NEONIMUS_HAS_VOICE` (see `branding/neonimus_config.h`)
and registered into the existing menu/command system via a tracked patch
in `../../PATCHES.md`, not by editing upstream files directly.
