# ChristianRodriguez46.github.io

My portfolio site, served by GitHub Pages at
[christianrodriguez46.github.io](https://christianrodriguez46.github.io/).

```
index.html          home page
style/              site styles (main.css, coursework.css)
js/                 site scripts
images/             logo (logo.svg, plus PNG copies for older browsers and phones)
resume/             my CV (PDF)
Projects/           Projects page (index.html) and my personal projects
Coursework/         labs and projects by course, with an index page
.github/workflows/  GitHub Actions that run the Breakaway tests on every push
.nojekyll           tells GitHub Pages to serve every file as-is
```

Front-end projects open as live demos. PHP projects are posted as code for now, since GitHub Pages
does not run PHP.

## Projects

| Project | What it is | Built with | Links |
|---|---|---|---|
| Breakaway | A top-down hockey shootout against an AI goalie that gets better every round. Three control schemes, keyboard and touch. | JavaScript modules, Canvas 2D, Web Audio; tested with Node's test runner and Playwright | [Play](https://christianrodriguez46.github.io/Projects/Breakaway/) · [About](https://christianrodriguez46.github.io/Projects/Breakaway/about.html) · [Code and docs](Projects/Breakaway/) |
| Hangman | A word-guessing game with a coding-term word bank. | HTML, CSS, JavaScript modules | [Play](https://christianrodriguez46.github.io/Projects/Hangman/) · [Code](Projects/Hangman/) |

All of my projects run in the visitor's browser. Breakaway has a `package.json`, but Node is only
used on my machine and in GitHub Actions to run its tests; the game itself needs no build step or
server. Its README explains how to run it and test it locally.

## How the site is built

- Plain HTML, CSS and JavaScript, no build step. Edit a file, commit, push.
- `style/main.css` holds the design tokens (colors, type, sizes) at the top, with a dark theme
  that follows the visitor's system setting. Both stylesheets use native CSS nesting.
- Every page has the same navigation bar (logo, links and a CV (PDF) button). Its look is in section 4
  of `style/main.css`.
- `js/main.js` runs the mobile menu, the course bar highlight and the animations. Animations use
  [anime.js 3.2.2](https://animejs.com/) from cdnjs; the site works without it, and animations are
  skipped when the visitor's system has "Reduce motion" turned on.
- Each file starts with a comment block that lists its sections and common problems to check.
- Breakaway's tests run automatically in GitHub Actions (`.github/workflows/breakaway-tests.yml`)
  whenever a push changes the game. They don't affect how GitHub Pages publishes the site.
- The lab pages (`Coursework/<course>/<lab>/index.html`) are generated from page data by
  `build_lab_pages.py` in my build kit, which is kept outside this repository. To change a lab page,
  edit its data there and rerun the script instead of editing the HTML.
