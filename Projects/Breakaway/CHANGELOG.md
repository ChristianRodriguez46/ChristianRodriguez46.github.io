# Changelog

All notable changes to Breakaway are listed here, newest first.
The format follows [Keep a Changelog](https://keepachangelog.com/en/1.1.0/), and versions follow
[Semantic Versioning](https://semver.org/).

## [Unreleased]

### Added
- Physics (`src/core/collision.js`, `rink.js`, `skater.js`, `puck.js`): skating with acceleration,
  glide and turning; dekes; shots for all three control schemes; puck friction; bounces off the
  boards, corners and posts; swept collision tests so a fast puck can't pass through a post or the
  goalie between steps; a goal counts only when the whole puck crosses the line between the posts.
- Project setup: page shell with the site's navigation bar, design tokens, `package.json` scripts
  for tests (`node --test`), type checking (`tsc` over JSDoc types), linting and browser tests.
- `src/core/constants.js`: every tunable number in one place, with the rink in real NHL feet and
  the Rookie, Pro and All-Star goalie tiers.
- `src/core/types.js`: shared JSDoc types for the game state, input and saved data.
- `src/core/vector.js`: 2D vector math (add, scale, normalize, rotate, dot product, distance).
- `src/core/random.js`: seeded random number generator (mulberry32) and `?seed=` URL support, so
  the same seed always plays the same game.
- GitHub Actions workflow that runs the Node tests on every push that touches the game.
- Decision records: ADR-001 (stack), ADR-002 (fixed-timestep loop), ADR-003 (pure core and
  browser shell), ADR-004 (world units in feet).
- Setup guide for Windows with WSL2 and VS Code, and a learning primer on the game loop.
