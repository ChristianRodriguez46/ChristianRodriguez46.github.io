# ADR-001: Build Breakaway with vanilla JavaScript modules and Canvas 2D

**Status:** Accepted   **Date:** 2026-10-19

## Context

Breakaway is a 2D arcade hockey game: the player skates in on an AI goalie and tries to score,
with rounds that get harder. It is a portfolio piece that has to play from a link on
`christianrodriguez46.github.io`.

Constraints:

- **Hosting is GitHub Pages.** It serves static files only: no server code, no database, and no
  way to set custom HTTP headers. Published sites can be at most 1 GB, with a soft bandwidth limit
  of 100 GB per month ([GitHub Pages limits](https://docs.github.com/en/pages/getting-started-with-github-pages/github-pages-limits)).
- **No Docker and no AWS**, by the owner's choice. Neither is needed for a static game.
- **The rest of the site has no build step.** Every page is hand-written HTML, CSS and JavaScript,
  and publishing is "edit, commit, push".
- **The developer works in WSL2 (Ubuntu) on a Windows laptop with VS Code.** Their home stack is
  HTML, CSS and JavaScript (Hangman uses ES modules), plus PHP/MySQL, C++ and C# from coursework.
- **Learning goal:** one big new thing per project. Here that is real-time game programming:
  a game loop, vector math, collision detection and simple AI.

## Options considered

| Option | Complexity | Cost | Scalability | Team familiarity | Pros | Cons |
|---|---|---|---|---|---|---|
| **Vanilla JS modules + Canvas 2D** | Low | $0 | Fine for a 2D arcade game | High (home stack) | No build step, matches the site; every line of the game is the developer's own; small download; logic testable in Node | Write the loop, physics and rendering by hand; no editor or engine tooling |
| TypeScript + Vite | Medium | $0 | Same | Close | Static types catch bugs early; high job demand | Adds a build step the rest of the site doesn't have; either commit built files or move the whole site to a GitHub Actions deploy; a second new thing next to game programming |
| C++ + raylib → WebAssembly (Emscripten) | High | $0 | Better raw performance | Medium (knows C++) | Reuses C++ coursework; teaches WebAssembly | New toolchain (emsdk) on top of new game concepts; browser text, input and accessibility are harder from WASM; harder to unit test in the same setup |
| Godot 4 (GDScript), web export | Medium | $0 | Good; can also export to desktop | Far | Full engine, editor, physics built in | New engine, language and workflow at once; Pages can't send the headers multithreaded web builds need, so it must use the single-threaded export; the engine adds a several-MB download; the engine does the physics, so less of the core is the developer's own |

## Decision

Build the game in **plain JavaScript ES modules drawn on a `<canvas>` with the Canvas 2D API**,
with no runtime dependencies and no build step. It lives at `Projects/Breakaway/` and is published
the same way as the rest of the site.

Supporting choices:

- **Game logic is kept separate from the browser.** Physics, collisions, goalie AI, scoring and
  round rules are plain modules with no DOM or canvas access, so they can be unit tested in Node.
  Rendering, input and storage are thin browser-only modules around them.
- **Tests use Node's built-in test runner** (`node --test`), Node 24 LTS. Node is a development
  tool only; players never download anything from npm.
- **Development-only tooling** (linter, formatter, type checking of JSDoc comments) may be added as
  `devDependencies` in `Projects/Breakaway/package.json`. `node_modules/` is never committed.
  Exact tools are chosen at scaffold time (Phase 4) and recorded in `SETUP.md`.
- **Saved data** (best score, settings) uses the browser's `localStorage` on the player's device
  only. Nothing is sent anywhere.
- **No third-party requests** from the game page: no Google Fonts, no CDN scripts, no analytics,
  no embeds.

## Consequences

- **Easier:** publishing (push and it's live); reading and explaining every file in an interview;
  unit testing the game rules; keeping the download small; matching the site's look and nav.
- **Harder:** everything an engine would give for free (fixed-timestep loop, collision math,
  sprite drawing, audio) is written by hand. That is the point of the project, but it takes time.
- **Ruled out on GitHub Pages:** a global leaderboard, accounts, cloud saves and online
  multiplayer. All need a server and database. Adding them later is a **high-cost** change (a new
  back end, accounts, privacy work and anti-cheat), so they stay out of scope. Two players on one
  keyboard needs no server and stays possible as a stretch feature.
- **Docker and AWS:** not needed now or later for this game. If a back end is ever added, it would
  be a separate project with its own ADR.
- **Revisit when:** the game needs online features, the code grows past what plain modules
  handle comfortably (then TypeScript is the natural next step and the logic modules port
  file by file), or the owner wants a desktop build (then Godot or a wrapper like Tauri).
