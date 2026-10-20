# ADR-002: Run the game in fixed 1/120 s steps inside requestAnimationFrame

**Status:** Accepted   **Date:** 2026-10-19

## Context

Screens refresh at 60, 90, 120 or 144 Hz, and a hidden tab or a slow phone can skip frames. If the
game moved things by "however much time passed since the last frame", physics would differ by
device: friction, bounces and the goalie's reaction time would all change with the frame rate, and
a long frame could push a 105 ft/s puck straight through a post. The test plan also needs the same
inputs and seed to give the same result every time.

## Options considered

| Option | Complexity | Cost | Scalability | Team familiarity | Pros | Cons |
|---|---|---|---|---|---|---|
| Variable step (`dt` = frame time) | Low | $0 | Poor | High (most tutorials) | Simplest loop | Results depend on frame rate; tunneling on long frames; not reproducible in tests |
| **Fixed step 1/120 s with an accumulator** | Medium | $0 | Good | New (the project's learning goal) | Same physics on every device; reproducible; short swept tests | A little more code; needs render interpolation for smoothness |
| Fixed step 1/60 s | Medium | $0 | Good | New | Half the steps per second | A 105 ft/s puck moves 1.75 ft per step, longer sweeps, coarser goalie timing |
| `setInterval` timer loop | Low | $0 | Poor | Medium | Independent of rendering | Drifts, keeps running in hidden tabs, fights the display refresh |

## Decision

Use `requestAnimationFrame` for timing and drawing, and advance the game in fixed steps of
`FIXED_STEP_S = 1/120` with an accumulator. Each frame adds the elapsed time (clamped to
`MAX_FRAME_DT_S = 0.1`), runs whole steps (at most `MAX_STEPS_PER_FRAME = 12`), then draws once with
interpolation between the last two steps. The loop stops while the game is paused, hidden or on a
menu screen.

## Consequences

- Easier: identical results across devices; deterministic Node tests that advance by whole steps;
  short swept collision tests; explaining the loop in an interview.
- Harder: positions must keep a previous value for interpolation; the loop code is more than a
  one-liner.
- Revisit when: profiling shows step cost matters on low-end phones (then try 1/90), or a feature
  needs sub-step precision.
