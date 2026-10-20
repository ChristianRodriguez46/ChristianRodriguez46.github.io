# ADR-003: Keep the rules in a pure core and the browser code in a thin shell

**Status:** Accepted   **Date:** 2026-10-19

## Context

Breakaway has a lot of logic worth testing: puck physics, goal and post detection, goalie behavior
by tier, round rules, scoring and validation of saved data. Hangman mixed its logic into the page's
inline script, which works for a small game but can't be tested without a browser. The goalie also
makes random choices, which makes tests flaky unless randomness is controlled.

## Options considered

| Option | Complexity | Cost | Scalability | Team familiarity | Pros | Cons |
|---|---|---|---|---|---|---|
| Logic inside the page script (like Hangman) | Low | $0 | Poor | High | Fewest files | Untestable without a browser; random and time make tests flaky |
| **Pure core modules + thin browser shell, with injected random, clock and storage** | Medium | $0 | Good | Medium (ES modules already used) | Core runs in Node with `node --test`; seeded random makes every test repeatable; browser code stays small | More files; dependencies passed in explicitly |
| Class-based entities with DOM access | Medium | $0 | Medium | Medium | Familiar OOP from C++ | Classes still reach for globals; harder to test and to snapshot state |

## Decision

`src/core/` holds every rule as functions over plain objects and never touches `window`,
`document`, canvas, storage, timers, `Math.random`, `Date.now` or `performance.now`. Randomness comes
from an injected `random()` (a seeded mulberry32 generator), time from the fixed step, storage
from an injected object. `src/browser/` owns the loop, input, drawing, audio, storage and HTML, and
calls the core. A lint rule and a test helper that make those globals throw keep the core honest.
A `?seed=` URL parameter seeds the game for repeatable browser tests.

## Consequences

- Easier: fast, deterministic unit and integration tests; replaying a scripted attempt; reasoning
  about one step at a time; tuning numbers in one constants file.
- Harder: wiring dependencies by hand in `main.js`; keeping state plain (no hidden fields).
- Revisit when: the project moves to TypeScript (the core ports file by file) or adds a back end
  (the same core could run on a server to check scores).
