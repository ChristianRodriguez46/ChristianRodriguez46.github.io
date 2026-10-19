# Breakaway primer: real-time game programming

Your orientation before the first slice. The big new thing in this project is code that runs 60
times a second instead of once per click or request. Read it through once, then use it as a
glossary. Snippets here are generic sketches; the real code arrives slice by slice.

## 1. What you'll learn

By the end you'll be able to explain:

1. Why the game updates physics in fixed steps even when the screen refreshes at 60, 120 or 144
   times a second, and what an accumulator does.
2. How velocity, acceleration, friction and a normalized direction turn key presses into smooth
   skating that feels the same on every screen.
3. How the game detects a puck touching a board, post or goalie, why that is separate from deciding
   what happens next, and why a fast puck can tunnel through a thin post.
4. How the goalie decides: a state machine, difficulty tiers that are just different numbers, and
   a seeded random function that makes tests repeatable.
5. Why the pure game logic (testable with `node --test`) is kept apart from the browser-only layer
   of drawing, input, sound, saved data and screen-reader announcements.

## 2. The mental model

```
 keyboard / mouse / touch events
          |  (1) events only record "what is held right now"
          v
     input state  <------------------------------------------+
          |                                                   |
          | (2) sampled once at the start of every step       |
          v                                                   |
 requestAnimationFrame --(3)--> loop adds elapsed time        |
                                to the accumulator            |
                                      |                       |
                                      | (4) while time >= 1 step
                                      v                       |
              +----- FIXED-STEP UPDATE (pure logic) -----+    |
              | physics -> collisions -> goalie AI ->    |    |
              | rules (score, attempt and round states)  |    |
              +------------------+-----------------------+    |
                                 | (5) new game state          |
                                 v                            |
               RENDER: canvas drawing (interpolated)          |
               + HTML score strip, overlays, aria-live text   |
                                 | (6) ask for the next frame --+
                                 v
                         (back to step 3)

 localStorage: read once at startup (settings, best scores);
 written when a setting changes or a run ends. Never inside the loop.
```

1. Browser events do not change the game; they only note which keys, buttons or touches are active.
2. Each step reads that note, so input is applied at a steady rhythm.
3. The browser calls your frame function just before each repaint and hands you a timestamp.
4. The loop turns elapsed real time into zero or more equal-sized simulation steps.
5. Each step produces the next game state; drawing only reads it and never changes it.
6. The frame function asks for another frame, and the cycle repeats.

The HTML overlays (menus, pause, game over) work like Hangman's: ordinary buttons and event
handlers outside the loop, whose results (such as "paused") the loop reads.

## 3. New vocabulary

### Time and the loop

- **Game loop**: code that repeats while the game runs: read input, update the world, draw it.
- **Frame**: one pass that ends with a new picture on screen. "60 fps" means 60 pictures a second.
- **requestAnimationFrame (rAF)**: asks the browser to call your function just before the next
  repaint, passing a timestamp in milliseconds. It pauses in hidden tabs. You must ask again each frame.

```js
function frame(nowMs) {
  // ...update and draw...
  requestAnimationFrame(frame);
}
requestAnimationFrame(frame);
```

- **Delta time (dt)**: time since the last frame or step. Multiplying speed by dt keeps speed in
  "feet per second" instead of "feet per frame".

```js
x += speedFtPerS * dtS;  // right: same speed on any screen
x += 0.5;                // wrong: twice as fast at 120 Hz as at 60 Hz
```

- **Fixed timestep**: the update always advances the world by the same amount (say 1/60 s), no
  matter how long the frame took. Same inputs then give the same results, which keeps physics
  stable and tests repeatable.
- **Accumulator**: a jar of unspent time. Each frame pours in the elapsed time; each update drinks
  one step; the leftover (less than one step) stays for next frame. See the warm-up in section 7.
- **Interpolation**: drawing a point between the previous and current state, using the leftover
  fraction `alpha` (0 to 1), so motion looks smooth even though updates are 1/60 s apart.

```js
const drawX = prevX + (currX - prevX) * alpha;
```

### Vectors and motion

- **Vector**: a pair `(x, y)` meaning a position, or a direction and amount of movement.
  These return new objects for clarity; the real module may reuse objects to avoid garbage.

```js
const add = (a, b) => ({ x: a.x + b.x, y: a.y + b.y });
const scale = (v, k) => ({ x: v.x * k, y: v.y * k });
const length = (v) => Math.hypot(v.x, v.y);
const normalize = (v) => {            // same direction, length 1
  const len = length(v);
  return len === 0 ? { x: 0, y: 0 } : scale(v, 1 / len);
};
const dot = (a, b) => a.x * b.x + a.y * b.y;
```

- **Dot product**: for two unit vectors it is 1 when they point the same way, 0 when
  perpendicular, -1 when opposite. It answers "is the puck heading toward the net?" and powers bounces.
- **Velocity, acceleration, friction**: velocity is position change per second; acceleration is
  velocity change per second (what input does); friction shrinks velocity so the skater glides to a stop.

```js
vel = add(vel, scale(inputDir, accelFtPerS2 * dtS)); // acceleration
vel = scale(vel, Math.max(0, 1 - frictionPerS * dtS)); // friction
pos = add(pos, scale(vel, dtS));                     // velocity
```

### Collisions

- **Collision detection**: answering "are these two things touching?".
- **Collision response**: deciding what happens because they touched (bounce, stop, save).
- **Restitution**: bounciness, 0 (dead stop) to 1 (perfect bounce with no energy lost).

```js
// detection: two circles touch when their centers are closer than the radii added up
const isTouching = Math.hypot(puck.x - post.x, puck.y - post.y) <= puck.radiusFt + post.radiusFt;

// response: n is a unit vector pointing out of the surface, toward the puck
const speedIntoWall = dot(vel, n);   // negative while moving into the surface
if (speedIntoWall < 0) vel = add(vel, scale(n, -(1 + restitution) * speedIntoWall));
```

- **Tunneling and swept tests**: if a thing moves farther in one step than the thickness of what it
  should hit, a per-step overlap check never sees them touching. A swept test checks the whole
  path from the old to the new position (or splits the step into smaller ones).

### Behavior

- **State machine**: something is in exactly one named state at a time, with rules for moving
  between states. The goalie, an attempt and the screens (playing, paused, game over) all work this way.

```js
switch (goalie.state) {
  case 'squareUp': if (shotIncoming) goalie.state = 'dive'; break;
  case 'dive': if (goalie.timeInStateS > DIVE_S) goalie.state = 'recover'; break;
  case 'recover': if (goalie.timeInStateS > RECOVER_S) goalie.state = 'squareUp'; break;
}
```

- **AI tiers and parameters**: Rookie, Pro and All-Star run the same goalie code; each tier is a
  set of numbers (reaction delay, speed, chance to read a deke). These values are illustrative:

```js
const ROOKIE = { reactionDelayS: 0.30, lateralSpeedFtPerS: 9, dekeReadChance: 0.2 };
const ALL_STAR = { reactionDelayS: 0.10, lateralSpeedFtPerS: 15, dekeReadChance: 0.7 };
```

- **Seeded random number generator**: a "random" function that returns the same sequence every
  time it starts from the same seed. The goalie takes a random function as a parameter, so tests pass a seeded one.

```js
function makeRandom(seed) {
  let state = seed >>> 0;
  return () => {                       // returns [0, 1) like Math.random()
    state = (Math.imul(state, 1664525) + 1013904223) >>> 0;
    return state / 4294967296;
  };
}
```

### Drawing and the browser

- **Canvas world-to-screen transform**: the game thinks in feet; the canvas counts pixels, with y
  growing downward. One transform converts between them so drawing code can speak in feet.

```js
ctx.setTransform(pxPerFt, 0, 0, pxPerFt, offsetXPx, offsetYPx); // pixel = feet * pxPerFt + offset
```

- **devicePixelRatio**: physical screen pixels per CSS pixel (often 2 on phones and laptops). A
  canvas sized only in CSS pixels looks blurry, so the backing store is made larger.

```js
const dpr = window.devicePixelRatio || 1;
canvas.width = Math.round(cssWidthPx * dpr);
canvas.height = Math.round(cssHeightPx * dpr);
canvas.style.width = `${cssWidthPx}px`;
```

- **Offscreen canvas**: a canvas that is not on the page. The rink never changes, so it is drawn
  once there and copied each frame. (`OffscreenCanvas` is a related built-in; either way works.)

```js
const rinkLayer = document.createElement('canvas'); // never added to the page
// ...draw lines and circles into rinkLayer once...
ctx.drawImage(rinkLayer, 0, 0);                     // each frame: one cheap copy
```

- **Web Audio**: a browser API that builds sound from connected nodes (oscillator, gain, speakers).
  We synthesize every sound, so there are no audio files. Browsers only start audio after a click or key press.

```js
const audio = new AudioContext();      // create or resume inside the Play click handler
const osc = audio.createOscillator();
osc.connect(audio.destination);
osc.start();
osc.stop(audio.currentTime + 0.1);     // a 0.1 s beep
```

- **aria-live**: an HTML attribute marking a region whose text changes are announced by screen
  readers. A canvas is invisible to them, so results ("Goal. Score 100.") are also written as text.

```html
<p id="announcer" aria-live="polite"></p>
```

```js
announcer.textContent = 'Goal. Score 100.';
```

## 4. From your home stack

### (a) Hangman (event-driven) vs Breakaway (frame-driven)

| | Hangman | Breakaway |
|---|---|---|
| What runs code | A click on a letter | A timer: the browser's frame callback, ~60 times a second |
| Input | The event handler uses it immediately | The handler records it; the update samples it each step |
| State changes | Inside the event handler | Only inside the update step |
| Screen changes | Browser redraws after you change the DOM | You redraw the whole canvas every frame |
| Idle | Nothing runs between clicks | The loop runs even if the player does nothing |

Hangman, from `Projects/Hangman/index.html`:

```js
lettersDiv.addEventListener('change', e => {
  wrong++;                                                   // state changes right here
  svg.querySelector(`.step${wrong}`).classList.add('visible'); // browser repaints
});
```

Breakaway-style sketch (not final code):

```js
const keysHeld = new Set();
window.addEventListener('keydown', (e) => keysHeld.add(e.code));    // only records
window.addEventListener('keyup', (e) => keysHeld.delete(e.code));

function update(dtS) {                                              // the loop reads it
  const dirX = (keysHeld.has('ArrowRight') ? 1 : 0) - (keysHeld.has('ArrowLeft') ? 1 : 0);
  skater.x += dirX * SKATE_SPEED_FT_PER_S * dtS;
}
```

### (b) PHP request lifecycle vs one frame

| | PHP request | One frame |
|---|---|---|
| Start | A request arrives | The browser calls your frame function |
| Input | `$_POST` / `$_GET`, then validate | Keys, mouse, touch state, then clamp and normalize |
| State lives in | MySQL or session; PHP forgets everything after the response | Ordinary variables that survive from frame to frame |
| Output | HTML sent to the client | Pixels on the canvas |
| End | Process done, nothing remembered | Ask for the next frame |
| Time budget | Hundreds of ms is fine | About 16.7 ms for everything |
| Persistence | A database | `localStorage`: tiny, strings only, so `JSON.parse` and validate it like `$_POST` |

```php
$guess = $_POST['letter'] ?? '';        // request in
$game = applyGuess(loadGame($pdo, $id), $guess);
saveGame($pdo, $id, $game);
echo render($game);                     // respond; PHP then forgets all of it
```

```js
function frame() {                      // simplified: no accumulator yet
  const input = sampleInput();          // sample
  state = update(state, input);         // update (state survives to the next frame)
  draw(state);                          // draw
  requestAnimationFrame(frame);         // repeat
}
```

### (c) A C++ 2D vector vs a small JS vector module

```cpp
struct Vec2 { float x, y; };
Vec2 operator+(Vec2 a, Vec2 b) { return {a.x + b.x, a.y + b.y}; }
float length(Vec2 v) { return std::sqrt(v.x * v.x + v.y * v.y); }
```

```js
export function add(a, b) { return { x: a.x + b.x, y: a.y + b.y }; }
export function length(v) { return Math.hypot(v.x, v.y); }
```

| | C++ | JavaScript |
|---|---|---|
| Add two vectors | `a + b` (operator overloading) | `add(a, b)`; JS has no operator overloading |
| Passing | Struct copied by value | Object passed by reference; mutating it changes the caller's copy |
| Types | `float x, y` enforced by the compiler | Convention, described by a JSDoc `@typedef`; every number is a 64-bit double |
| Layout | Header and source file | One `export` per function, `import { add } from './vec.js'` |

## 5. The toolchain

Run every command in the WSL (Ubuntu) terminal. Paths assume your clone is in `~/projects` (see `SETUP.md`).

| Tool | What it does here | Commands |
|---|---|---|
| Node 24 + `node --test` | Runs unit tests of the pure logic with no browser. Finds `*.test.js` files and files in `test/` folders. | `node -v` (expect `v24.x`); `cd ~/projects/ChristianRodriguez46.github.io/Projects/Breakaway && node --test`. Once scaffolded: `npm test`. |
| `python3 -m http.server` | Serves the files over `http://`. | `cd ~/projects/ChristianRodriguez46.github.io && python3 -m http.server 4101`, then open `http://localhost:4101/Projects/Breakaway/` in Chrome or Edge. Stop with Ctrl+C. |
| Chrome / Edge DevTools | Debug, measure, inspect saved data. | F12 (details below). |
| VS Code + WSL extension | Editor running inside Linux. | `cd ~/projects/ChristianRodriguez46.github.io && code .`; the bottom-left corner should read **WSL: Ubuntu**. |

**Why ES modules need a server.** The browser loads each `import` as a separate request with
cross-origin rules applied. A page opened from disk (`file://`) has no valid origin, so the request
is blocked and you get a blank page with a CORS error. Serve the repo root, not the game folder,
so `../../style/main.css` resolves as on GitHub Pages.

**DevTools tabs you'll use:**

- **Sources**: Ctrl+P opens a module, clicking a line number sets a breakpoint, F10 steps over,
  F8 resumes. A breakpoint freezes the loop, so the next frame sees a huge dt; the 250 ms clamp
  in the warm-up is what prevents a jump.
- **Performance**: record a few seconds of play, then stop. In the Frames row and the main-thread
  flame chart each frame should finish in about 16.7 ms; red marks are long tasks.
- **Application**: Local Storage, then `http://localhost:4101`, lists the `breakaway.*` keys. Edit
  one to garbage and reload to see whether the game recovers.
- **Rendering drawer** (three-dot menu, More tools): an FPS meter, and "Emulate CSS media feature
  prefers-reduced-motion".
- After edits, hard refresh with Ctrl+Shift+R, or tick "Disable cache" in the Network tab.

## 6. Official resources

Read in this order. All are official documentation except the last.

- [Canvas tutorial (MDN)](https://developer.mozilla.org/en-US/docs/Web/API/Canvas_API/Tutorial)
- [Window.requestAnimationFrame() (MDN)](https://developer.mozilla.org/en-US/docs/Web/API/Window/requestAnimationFrame)
- [JavaScript modules (MDN)](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide/Modules)
- [Node.js test runner](https://nodejs.org/api/test.html)
- [Window.devicePixelRatio (MDN)](https://developer.mozilla.org/en-US/docs/Web/API/Window/devicePixelRatio) and [OffscreenCanvas (MDN)](https://developer.mozilla.org/en-US/docs/Web/API/OffscreenCanvas)
- [Web Audio API (MDN)](https://developer.mozilla.org/en-US/docs/Web/API/Web_Audio_API)
- [Window.localStorage (MDN)](https://developer.mozilla.org/en-US/docs/Web/API/Window/localStorage)
- [ARIA live regions (MDN)](https://developer.mozilla.org/en-US/docs/Web/Accessibility/ARIA/Guides/Live_regions)
- [prefers-reduced-motion (MDN)](https://developer.mozilla.org/en-US/docs/Web/CSS/@media/prefers-reduced-motion)
- [Analyze runtime performance (Chrome DevTools)](https://developer.chrome.com/docs/devtools/performance)
- The one classic that is not official: Glenn Fiedler, [Fix Your Timestep!](https://gafferongames.com/post/fix_your_timestep/). It is the source of the accumulator and interpolation pattern used here.

## 7. How the exercises work

You said you'd rather read and explain code than write it. At each slice walkthrough:

1. You get one or two short snippets from the real code.
2. Write, in your own words, what each does and why it is written that way. Two to four sentences is enough.
3. Compare with the walkthrough's explanation.
4. Ask about any gap. A mismatch is useful information, not a failed test.

**Warm-up (generic code, not the project's names).** This is the heart of the game loop.
Assume `update(dtS)` advances the world and `draw(alpha)` paints it.

```js
const STEP_MS = 1000 / 60;
let accumulatorMs = 0;
let lastMs = null;

function frame(nowMs) {
  if (lastMs !== null) accumulatorMs += Math.min(nowMs - lastMs, 250);
  lastMs = nowMs;
  while (accumulatorMs >= STEP_MS) {
    update(STEP_MS / 1000);
    accumulatorMs -= STEP_MS;
  }
  draw(accumulatorMs / STEP_MS);
  requestAnimationFrame(frame);
}
requestAnimationFrame(frame);
```

Questions:

1. When `draw` is called, what does `accumulatorMs` hold, and why is it divided by `STEP_MS`?
2. On a 144 Hz screen a frame arrives about every 6.9 ms. How many times does `update` run per
   frame, and about how many per second?
3. What is `Math.min(..., 250)` for? What would happen without it when a player returns to a tab
   that was hidden for 5 seconds?

<details>
<summary>Model answer</summary>

1. The time that has arrived but not yet been simulated: at least 0 and under one step (16.7 ms).
   Dividing by `STEP_MS` gives `alpha`, 0 to 1, how far we are between the last update and the next.
   `draw` uses it to interpolate, so motion stays smooth between updates.
2. Usually 0, sometimes 1, never more. Each frame adds about 6.9 ms and an update fires once 16.7 ms
   has built up, so one update runs every second or third frame. Per second that is about 144 draws
   and about 60 updates, so game speed matches a 60 Hz screen.
3. It caps how much time one frame can add, so the loop can't try to catch up on a huge gap.
   rAF pauses in hidden tabs, so after 5 s the first elapsed time is about 5000 ms. Without the cap,
   `update` would run about 300 times in one frame, freezing the page and fast-forwarding the game.
   With it, at most 15 steps run. (`lastMs !== null` does a similar job on the first frame, which
   has no earlier timestamp.)

</details>

## 8. Check yourself

**Q1.** A skater's friction is written `vel = scale(vel, 0.9)` and runs once per drawn frame, with no
dt. Compared with a 60 Hz screen, a 144 Hz screen makes the skater:
(a) glide farther, (b) stop sooner, (c) behave the same.

**Q2.** A puck travels at 90 ft/s and the world steps at 60 per second. A post is about 0.17 ft
thick and the puck is about 0.25 ft across. Does checking "do the shapes overlap?" once per step
always catch a hit? Name two ways to fix it.

**Q3.** The player holds Right and Up at once, giving `{ x: 1, y: -1 }` (canvas y grows downward). How
fast is the skater moving compared with Right alone if that vector is used as is? What do you do about it?

**Q4.** Using `makeRandom` from section 3, predict the output:

```js
const a = makeRandom(42);
const b = makeRandom(42);
console.log(a() === b(), a() === a());
```

Why does that property make goalie tests useful?

<details>
<summary>Answers</summary>

**A1. (b) Stop sooner.** The 0.9 multiplication happens 144 times per second instead of 60, so
velocity decays much faster (after half a second it is about 0.0005 of its start instead of 0.04).
Fix: apply friction inside the fixed-step update, or scale it by dt, as in the friction example.

**A2. No.** The puck moves 90 / 60 = 1.5 ft per step, but post plus puck are only about 0.42 ft
thick. The puck can be just before the post on one step and just past it on the next, overlapping at
neither. Fixes: a swept test (check the segment from old to new position against the post), or split
fast steps into several sub-steps.

**A3. About 41% faster.** The length is the square root of 2, which is 1.414. Normalize the
direction first, which gives `{ x: 0.707, y: -0.707 }` with length 1, then multiply by the speed.

**A4. `true false`.** Same seed, same sequence, so the first calls match. The next two calls on `a`
are different numbers. Tests can therefore inject a seeded function and get the same goalie
decisions every run, so "the goalie bites on a deke more often at Rookie than at All-Star" passes or
fails for a reason, never by luck.

</details>
