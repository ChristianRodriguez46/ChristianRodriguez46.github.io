# ADR-004: Model the rink in feet with real NHL geometry

**Status:** Accepted   **Date:** 2026-10-19

## Context

The game needs one coordinate system for physics, the goalie and drawing. Working in screen pixels
would tie the rules to the canvas size, so a phone and a laptop would play differently. The look
("broadcast rink") promises real markings, and a hockey fan notices a wrong crease or blue line.

## Options considered

| Option | Complexity | Cost | Scalability | Team familiarity | Pros | Cons |
|---|---|---|---|---|---|---|
| Screen pixels | Low | $0 | Poor | High | No conversion | Rules change with screen size; resizing breaks state |
| Normalized 0–1 units | Low | $0 | Good | Medium | Size-independent | Numbers mean nothing to a reader; speeds and distances hard to tune |
| **Feet and seconds, real NHL measurements** | Low | $0 | Good | High (familiar units) | Size-independent; constants read like a rulebook (goal line 11 ft, blue line 75 ft); speeds in ft/s are easy to reason about | One world→screen transform in the renderer |

## Decision

All core values are in feet and seconds, with units in the names (`GOAL_LINE_Y_FT`,
`SHOT_SPEED_MAX_FT_PER_S`). The origin is the top-left of the rink's bounding box; `y` runs from the
end boards (0) toward center ice (100). The renderer applies one scale and offset. Markings use
real NHL measurements; the puck, posts and players use larger collision and drawing sizes for
playability (puck radius 0.5 ft instead of 0.125 ft), and that exception is written down in the
constants so nobody "fixes" one into the other.

## Consequences

- Easier: the same game on every screen; tests written in rink terms; tuning by real-world feel.
- Harder: the playability radii are a deliberate deviation that must stay documented.
- Revisit when: the game adds a full-rink or side view (the units still hold; the visible box changes).
