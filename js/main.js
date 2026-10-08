/* =============================================================
   js/main.js
   Site behavior for christianrodriguez46.github.io

   Loaded at the end of every page, after anime.js:
       <script src="https://cdnjs.cloudflare.com/ajax/libs/animejs/3.2.2/anime.min.js" defer></script>
       <script src="js/main.js" defer></script>
   (Both use "defer", so they run in that order once the page is parsed.)

   What this file does
     1. Mobile menu       opens and closes the navigation on small screens
                          and keeps the ARIA attributes in sync.
     2. Hero intro        one short anime.js intro on each page's hero.
     3. Hangman tile      fills in the missing letters when the tile
                          scrolls into view (homepage only).
     4. Course cards      fades each course card in the first time it
                          scrolls into view (coursework page only).
     5. Course bar        highlights the course you are looking at in the
                          sticky course bar (coursework page only).

   Every part checks that its elements exist first, so the same file
   works on every page.

   Troubleshooting
   - Nothing animates:
       a) anime.js did not load. Open the browser console (F12) and look
          for a failed request to cdnjs.cloudflare.com. The site still
          works; content just appears without motion.
       b) Your computer has "Reduce motion" turned on (macOS: System
          Settings > Accessibility > Display; Windows: Settings >
          Accessibility > Visual effects). This file skips all animation
          on purpose when that setting is on.
   - The hero stays blank for 2.5 seconds, then pops in: this file
     failed before the intro ran. The console will show the error.
   - The menu button does nothing: the button needs id="nav-toggle" and
     the menu list needs id="nav-menu".
   - The course bar never highlights: every course <section> needs an id
     that matches a course bar link, for example id="cmps2680" for
     href="#cmps2680".
   - To test without animations, set DEBUG_DISABLE_ANIMATION to true.
   ============================================================= */

(function () {
    'use strict';

    /* ---------- Settings ---------- */

    // Turn every animation off while debugging layout.
    var DEBUG_DISABLE_ANIMATION = false;

    // True when the visitor's system asks for less motion.
    var prefersReducedMotion = window.matchMedia('(prefers-reduced-motion: reduce)').matches;

    // anime.js is a global function when its script loaded correctly.
    var animeLoaded = typeof window.anime === 'function';

    // Animate only when all three conditions allow it.
    var canAnimate = animeLoaded && !prefersReducedMotion && !DEBUG_DISABLE_ANIMATION;

    var root = document.documentElement;

    if (!animeLoaded) {
        console.info('[main.js] anime.js is not loaded; showing content without animation.');
    }

    // The <head> of each page adds the "js" class, which hides the hero
    // until it animates (see "Entrance" in main.css). "anim-ready" tells
    // the CSS that this file has taken over. Without animation, remove
    // "js" so the hidden elements show right away.
    if (canAnimate) {
        root.classList.add('anim-ready');
    } else {
        root.classList.remove('js');
    }


    /* ---------- 1. Mobile menu ---------- */
    // The button (#nav-toggle) controls the list (#nav-menu). On screens
    // narrower than 834px the CSS turns the list into a full-screen panel
    // that is shown while it has the class "is-open".
    var toggle = document.getElementById('nav-toggle');
    var menu = document.getElementById('nav-menu');

    function setMenuOpen(open) {
        toggle.setAttribute('aria-expanded', String(open));
        toggle.setAttribute('aria-label', open ? 'Close menu' : 'Open menu');
        menu.classList.toggle('is-open', open);
        document.body.classList.toggle('menu-open', open); // stops the page behind from scrolling

        // Slide the links down one after another as the panel opens.
        if (open && canAnimate) {
            anime.remove(menu.querySelectorAll('li'));
            anime({
                targets: menu.querySelectorAll('li'),
                opacity: [0, 1],
                translateY: [-10, 0],
                delay: anime.stagger(45),
                duration: 500,
                easing: 'easeOutQuart'
            });
        }
    }

    if (toggle && menu) {
        toggle.addEventListener('click', function () {
            setMenuOpen(toggle.getAttribute('aria-expanded') !== 'true');
        });

        // Close the menu after choosing a link (needed for #section links).
        menu.addEventListener('click', function (event) {
            if (event.target.closest('a')) {
                setMenuOpen(false);
            }
        });

        // Escape closes the menu and returns focus to the button.
        document.addEventListener('keydown', function (event) {
            if (event.key === 'Escape' && toggle.getAttribute('aria-expanded') === 'true') {
                setMenuOpen(false);
                toggle.focus();
            }
        });

        // If the window grows past the mobile size, reset the menu.
        window.matchMedia('(min-width: 834px)').addEventListener('change', function (event) {
            if (event.matches) {
                setMenuOpen(false);
                // Clear the inline styles left by the slide-in animation.
                if (canAnimate) {
                    anime.set(menu.querySelectorAll('li'), { opacity: 1, translateY: 0 });
                }
            }
        });
    }


    /* ---------- 2. Hero intro ---------- */
    // Elements marked data-animate (logo, heading, intro, buttons) start
    // hidden by CSS and play in as one sequence.
    var heroItems = document.querySelectorAll('[data-animate]');

    if (canAnimate && heroItems.length) {
        var icon = document.querySelector('[data-animate="icon"]');
        var rest = Array.prototype.filter.call(heroItems, function (el) {
            return el !== icon;
        });

        var intro = anime.timeline({ easing: 'easeOutQuart' });

        if (icon) {
            intro.add({
                targets: icon,
                opacity: [0, 1],
                scale: [0.82, 1],
                rotate: [-8, 0],
                duration: 900,
                easing: 'spring(1, 90, 14, 0)'
            });
        }

        intro.add({
            targets: rest,
            opacity: [0, 1],
            translateY: [22, 0],
            duration: 900,
            delay: anime.stagger(90)
        }, icon ? '-=650' : 0); // overlap with the logo so it reads as one motion
    }


    /* ---------- 3. Hangman tile ---------- */
    // Blank slots look like <li class="is-blank" data-letter="A"></li>.
    // When the tile is half visible, each blank gets its letter, one after
    // another. Runs once.
    var slots = document.querySelector('.word-slots');

    if (canAnimate && slots && 'IntersectionObserver' in window) {
        var slotObserver = new IntersectionObserver(function (entries, observer) {
            if (!entries[0].isIntersecting) {
                return;
            }
            observer.disconnect();

            var blanks = slots.querySelectorAll('.is-blank');
            blanks.forEach(function (slot) {
                slot.innerHTML = '<span class="slot-letter">' + slot.getAttribute('data-letter') + '</span>';
            });

            anime({
                targets: slots.querySelectorAll('.slot-letter'),
                opacity: [0, 1],
                translateY: [-26, 0],
                scale: [1.3, 1],
                delay: anime.stagger(260, { start: 350 }),
                duration: 700,
                easing: 'spring(1, 80, 12, 0)',
                // When every letter has landed, the slots are no longer blank.
                complete: function () {
                    blanks.forEach(function (slot) {
                        slot.classList.remove('is-blank');
                    });
                }
            });
        }, { threshold: 0.5 });

        slotObserver.observe(slots);
    }


    /* ---------- 4. Course cards ---------- */
    // Cards that start below the screen are hidden, then fade up (with
    // their lab chips) the first time they scroll into view.
    var cards = document.querySelectorAll('.course');

    if (canAnimate && cards.length && 'IntersectionObserver' in window) {
        var below = Array.prototype.filter.call(cards, function (card) {
            return card.getBoundingClientRect().top > window.innerHeight;
        });

        anime.set(below, { opacity: 0, translateY: 28 });

        var cardObserver = new IntersectionObserver(function (entries, observer) {
            entries.forEach(function (entry) {
                if (!entry.isIntersecting) {
                    return;
                }
                observer.unobserve(entry.target);

                anime({
                    targets: entry.target,
                    opacity: [0, 1],
                    translateY: [28, 0],
                    duration: 800,
                    easing: 'easeOutQuart'
                });
                anime({
                    targets: entry.target.querySelectorAll('.lab'),
                    opacity: [0, 1],
                    translateY: [8, 0],
                    delay: anime.stagger(14, { start: 180 }),
                    duration: 450,
                    easing: 'easeOutQuad'
                });
            });
        }, { rootMargin: '0px 0px -8% 0px' });

        below.forEach(function (card) {
            cardObserver.observe(card);
        });
    }


    /* ---------- 5. Course bar ---------- */
    // Marks the course in the middle of the screen with
    // aria-current="location" (styled in coursework.css) and scrolls the
    // course bar sideways so that link stays visible on phones.
    var barLinks = document.querySelectorAll('.localnav__list a');

    if (barLinks.length && 'IntersectionObserver' in window) {
        var bar = document.querySelector('.localnav__list');
        var linkById = {};
        var current = null;

        barLinks.forEach(function (link) {
            linkById[link.hash.slice(1)] = link;
        });

        var intro = document.querySelector('.cw-hero');

        var barObserver = new IntersectionObserver(function (entries) {
            entries.forEach(function (entry) {
                // Back at the page intro: no course is current.
                if (entry.target === intro) {
                    if (entry.isIntersecting && current) {
                        current.removeAttribute('aria-current');
                        current = null;
                    }
                    return;
                }

                var link = linkById[entry.target.id];
                if (!entry.isIntersecting || !link || link === current) {
                    return;
                }
                if (current) {
                    current.removeAttribute('aria-current');
                }
                link.setAttribute('aria-current', 'location');
                current = link;

                bar.scrollTo({
                    left: link.offsetLeft - bar.clientWidth / 2 + link.clientWidth / 2,
                    behavior: prefersReducedMotion ? 'auto' : 'smooth'
                });
            });
        }, { rootMargin: '-45% 0px -50% 0px' }); // a thin line across the middle of the screen

        document.querySelectorAll('.course[id]').forEach(function (section) {
            barObserver.observe(section);
        });
        if (intro) {
            barObserver.observe(intro);
        }
    }
})();
