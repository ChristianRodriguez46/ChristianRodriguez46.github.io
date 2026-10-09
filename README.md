# ChristianRodriguez46.github.io

My portfolio site, served by GitHub Pages at
[christianrodriguez46.github.io](https://christianrodriguez46.github.io/).

```
index.html          home page
style/              site styles (main.css, coursework.css)
js/                 site scripts
images/             logo and site images
Projects/           personal projects (Hangman)
Coursework/         labs and projects by course, with an index page
.nojekyll           tells GitHub Pages to serve every file as-is
```

Front-end projects open as live demos. PHP projects are posted as code for now, since GitHub Pages
does not run PHP.

## How the site is built

- Plain HTML, CSS and JavaScript, no build step. Edit a file, commit, push.
- `style/main.css` holds the design tokens (colors, type, sizes) at the top, with a dark theme
  that follows the visitor's system setting. Both stylesheets use native CSS nesting.
- `js/main.js` runs the mobile menu, the course bar highlight and the animations. Animations use
  [anime.js 3.2.2](https://animejs.com/) from cdnjs; the site works without it, and animations are
  skipped when the visitor's system has "Reduce motion" turned on.
- Each file starts with a comment block that lists its sections and common problems to check.
- The lab pages (`Coursework/<course>/<lab>/index.html`) are generated from page data by
  `build_lab_pages.py` in my build kit, which is kept outside this repository. To change a lab page,
  edit its data there and rerun the script instead of editing the HTML.
