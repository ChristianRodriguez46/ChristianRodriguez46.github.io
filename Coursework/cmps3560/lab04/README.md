# Facts and rules in Prolog

**CMPS 3560 Artificial Intelligence**, Lab 4

Read this lab with snapshots and notes on every file: [https://christianrodriguez46.github.io/Coursework/cmps3560/lab04/](https://christianrodriguez46.github.io/Coursework/cmps3560/lab04/)

## What it does

`lab4.pro` writes a small rule chain in Prolog (`x` leads to `y`, `y` leads to `z`) over a set of facts, to query which rules can be proven.

## How to run

From this folder:

```bash
swipl lab4.pro
?- rule(z).
```

Requires: Python 3 for the Python labs, `g++` for the C++ labs, and SWI-Prolog or GNU Prolog for labs 4 and 5.

## Concepts

- Prolog facts and rules
- Backward chaining

[Back to CMPS 3560](../)
