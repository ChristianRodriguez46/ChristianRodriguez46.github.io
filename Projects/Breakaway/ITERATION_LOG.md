# Iteration log

Problems found while building and testing Breakaway, how each was found, and how it was fixed.
Newest first.

| Date | Problem | Found by | Cause | Fix | Test |
|---|---|---|---|---|---|
| 2026-10-21 | After clicking Pause or Mute, Space toggled that button and the arrows stopped skating | Review (browser) | The clicked button kept keyboard focus, and the input code ignored keys coming from buttons | Buttons in the score strip and touch controls no longer block game keys; Space key-up is kept from clicking them | Browser check: Space with Mute focused no longer toggles it |
| 2026-10-21 | Skater, goalie and puck were 3–15 px on a phone, hard to see | Review (screenshot) | Players are drawn at their physics size, which is small at 3.8 px per foot | Draw players and puck up to 2× larger when the screen is small (drawing only); puck drawn on top of the skater | Screenshot at 375 px |
| 2026-10-21 | A hand-edited best score like `1e21` was accepted and could never be beaten | Review (code) | Saved counts had no upper limit | Reject saved counts above 10,000,000 | `settings.test.js`: impossibly large best score is dropped |
| 2026-10-20 | The goalie stopped almost every shot, even at Rookie | Stats tests | Pads plus body covered more than the 6 ft goal mouth | Recalibrated the Rookie, Pro and All-Star numbers; Rookie concedes about 39%, All-Star about 8% | `tests/stats/shot-outcomes.test.js` |
| 2026-10-20 | Score strip hidden under the site navigation bar | Browser check | The dark nav is `position: fixed` | Pad the game page by the nav height, as Hangman does | Screenshots at 375 and 1280 |
| 2026-10-20 | Dialogs opened in the top-left corner | Browser check | The site stylesheet resets every margin, including the dialog's centering | Restore centering for game dialogs | Screenshot |

## Known and accepted

- A failed round goes straight to the game-over screen (which says which round failed) instead of
  showing a separate round summary first.
- Mute comes before Play in the Tab order on the start screen; Tab rests on the page once when
  cycling through Settings and the pause dialog. Minor; left for a later polish pass.
- Browser end-to-end test files (Playwright test runner) were not written; the browser checks were
  run as scripts during review instead.
- Real touch feel, audio and screen readers can only be checked on a real device.
