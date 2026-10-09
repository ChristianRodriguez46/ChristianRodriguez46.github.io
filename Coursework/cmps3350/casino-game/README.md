# Casino game (team project)

**CMPS 3350 Software Engineering**, Team project

Read this lab with snapshots and notes on every file: [https://christianrodriguez46.github.io/Coursework/cmps3350/casino-game/](https://christianrodriguez46.github.io/Coursework/cmps3350/casino-game/)

## What it does

- A casino built by a five-person team in C++ with OpenGL and X11. It has three games (slots, blackjack and dice) that share a chip balance, buttons and textures.
- **My part: the dice game** (`crodriguez4.cpp`, `include/crodriguez4.h`, `include/dice.h`).
- A cup shakes for seven seconds, then reveals two dice.
- You bet that the total will be under 7, over 7, or exactly 7; a win pays 2x.
- I built the dice and cup textures and animation, the betting interface (balance, current bet, streak), the rules overlay, and layout that adapts to the window size.
- Each team member's code is in their own file (`akoli.cpp`, `bolayvar.cpp`, `hchen.cpp`, `crodriguez4.cpp`), joined by `main.cpp`. The original team README is in `README-team.md`. The team's repository is on GitHub at [toughgun/GhettoCasino](https://github.com/toughgun/GhettoCasino).

## How to run

From this folder:

```bash
make
./main
```

Requires: Linux with `g++`. The graphics labs and the casino game also need X11 and OpenGL (`sudo apt install libx11-dev libgl1-mesa-dev libglu1-mesa-dev` on Ubuntu). Every folder has a `Makefile`, so `make` builds everything in it.

## Concepts

- Team development with Git
- OpenGL textures and sprite sheets
- Game state and UI

[Back to CMPS 3350](../)
