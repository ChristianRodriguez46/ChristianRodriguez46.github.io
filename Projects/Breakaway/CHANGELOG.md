# Changelog

All notable changes to Breakaway are listed here, newest first.
The format follows [Keep a Changelog](https://keepachangelog.com/en/1.1.0/), and versions follow
[Semantic Versioning](https://semver.org/).

## [Unreleased]

### Fixed
- Space and the arrow keys keep working after clicking Pause or Mute.
- Skater, goalie and puck are drawn larger on phones so they're easy to see.
- Impossibly large saved best scores are rejected.

### Changed
- Goalie levels recalibrated so the corners stay open: in scripted tests Rookie gives up about
  39% of shots, Pro about 20% and All-Star about 8%.

### Added
- Documentation and an about page: feature docs for physics, goalie AI, rules and scoring, and the
  browser layer in `docs/`, learning notes and exercises in `docs/learning/`, screenshots, a
  README, and an About page (`about.html`) linked from the Projects page.
- Game rules (`src/core/rules.js`, `game.js`): 5 attempts per round, 3 goals to advance, an
  8-second shot clock, one rebound chance per attempt, the run ends as soon as 3 goals are out of
  reach; every attempt ends as Goal, Save, Wide, No shot, Post and out, Poke check or Time.
- Goalie AI (`src/core/goalie.js`, `difficulty.js`): squares up to the puck, reacts after a delay,
  dives, poke checks, bites on or reads dekes, and gives up rebounds. Rookie, Pro and All-Star
  levels; All-Star keeps improving after round 5, up to 20%.
- Scoring and saved data (`src/core/scoring.js`, `settings.js`): 100 points a goal, +50 after a
  successful deke; a best score per control scheme and starting level; saved settings are checked
  field by field and fall back to defaults if anything is wrong.
- Browser game (`src/browser/`, `index.html`, `style.css`): fixed-step loop, rink drawn in real NHL
  measurements, keyboard and touch controls for all three schemes, synthesized sound with mute,
  start, how-to-play, settings, pause, round summary and game-over screens, and screen-reader
  announcements.
- All text the game shows lives in `src/core/ui-strings.js`.
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
- Decisions: one document, `docs/decisions.md`, covers the stack, the fixed-timestep loop, the pure
  core and browser shell, and world units in feet.
- Setup guide for Windows with WSL2 and VS Code, and learning notes on the game loop.
