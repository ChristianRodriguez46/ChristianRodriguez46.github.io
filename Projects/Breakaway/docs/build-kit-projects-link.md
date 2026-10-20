# Build kit change: point the generated pages' "Projects" link at the Projects page

Why: the site now has a Projects page (`Projects/index.html`) that lists Breakaway and Hangman.
The hand-written pages already link to it. The generated pages still link straight to Hangman, so
the "Projects" link in their navigation bar and footer goes to a different place than everywhere else.

This file is instructions only. The generator (`build_lab_pages.py`) lives in your build kit, outside
this repository, so it was not changed here. No generated page in this repo was edited.

## What to change

In `build_lab_pages.py`, find the template text that writes the "Projects" link and drop
`Hangman/` from the path. The prefix before `Projects/` stays exactly as it is.

Before and after, copied from `Coursework/cmps2020/wk12/index.html` (which has
`<meta name="generator" content="build_lab_pages.py">`). The link appears twice per page, once in the
navigation bar (line 47) and once in the footer (line 152):

```html
<!-- before -->
<li><a href="../../../Projects/Hangman/">Projects</a></li>

<!-- after -->
<li><a href="../../../Projects/">Projects</a></li>
```

Nothing else on the line changes: no `aria-current`, no other attributes.

## The relative prefix depends on page depth

The generator already computes the prefix (`../` repeated once for each folder below the site root).
Keep using that value; change only the path after it.

| Generated page | Example | Before | After |
|---|---|---|---|
| Lab page, 3 folders deep (113 pages) | `Coursework/cmps2020/wk12/index.html` | `../../../Projects/Hangman/` | `../../../Projects/` |
| Course-level page, 2 folders deep (6 pages) | `Coursework/cmps3600/x11-setup.html` | `../../Projects/Hangman/` | `../../Projects/` |

If your template builds the href as `prefix + "Projects/Hangman/"`, the fix is
`prefix + "Projects/"`.

## Rerun and verify

1. Edit `build_lab_pages.py` as above.
2. Rerun it the way you normally do, writing into a checkout of this repository, for example:
   `python3 build_lab_pages.py` (use your usual arguments).
3. From the repository root, confirm no generated page still links to Hangman from the navigation or
   footer. This command should print nothing:

   ```sh
   grep -rl 'build_lab_pages.py' --include='*.html' Coursework \
     | xargs grep -l 'Projects/Hangman/'
   ```

4. Confirm the new link is there. Both counts should be the same number (two links per generated
   page, so 119 pages gives 238):

   ```sh
   grep -rl 'build_lab_pages.py' --include='*.html' Coursework | wc -l
   grep -rho 'href="[./]*Projects/">Projects' Coursework --include='*.html' | wc -l
   ```

   The second count also includes the hand-written Coursework pages that already point to
   `Projects/`, so expect it to be slightly higher than twice the first.
5. Run `git status`. Only generated pages should have changed, and each diff should be exactly those
   two lines per file. Open one lab page and click "Projects" to check it lands on the Projects page.

## One page that is not generated

`Coursework/cmps2650/index.html` (the Linux commands page) has no generator meta, so the build kit
will not touch it, and it still links to `../../Projects/Hangman/` in its navigation bar and footer.
Change it by hand to `../../Projects/` (two places).
