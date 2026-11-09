# Upstream touch points

Everything under `boards/neonimus-core/`, `branding/`, `modules/`, and
`partitions/` is **pure addition** - new files only, nothing upstream is
edited to get Phase 1 (board bring-up) working, because PlatformIO's
`extra_configs = boards/*.ini boards/*/*.ini` already auto-discovers new
board `.ini` files.

There is exactly **one** upstream file that needs a one-line addition,
because it is a hand-maintained dispatcher with no auto-discovery:

## `boards/pinouts/pins_arduino.h`

Add, before the final `#endif`:

```c
#elif NEONIMUS_CORE_BOARD
#include "../neonimus-core/pins_arduino.h"
```

`NEONIMUS_CORE_BOARD` is defined in `boards/_boards_json/neonimus-core.json`'s
`extra_flags`, so this line is all PlatformIO needs to route to our pin map.

## `platformio.ini` (repo root, comes from the fork)

Optional, not required to build: add `neonimus-core` to the
`default_envs` list so `pio run` with no `-e` flag builds it by default.
Until then, always build explicitly:

```sh
pio run -e neonimus-core
```

## Phase 3 / 4 (tracked here as they land)

Wiring the voice command set and the MCP bridge into the existing menu
system (`src/core/menu_items/OthersMenu.cpp` or similar) will need a
small, equally-isolated registration patch each. Log every such patch
in this file with the exact diff, so a `git fetch upstream && git rebase
upstream/main` only ever has to re-apply a short, known list of
one-or-two-line hunks instead of a tangle of unreviewable edits.

Keeping this list short is the whole point of the branding/modules/board
split the project brief asked for - if a change doesn't fit in a few
lines here, it probably belongs in `modules/` as a new file instead.
