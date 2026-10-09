# Propositional logic entailment

**CMPS 3560 Artificial Intelligence**, Lab 3

Read this lab with snapshots and notes on every file: [https://christianrodriguez46.github.io/Coursework/cmps3560/lab03/](https://christianrodriguez46.github.io/Coursework/cmps3560/lab03/)

## What it does

`lab3.py` implements the forward-chaining entailment algorithm `PL-FC-ENTAILS` for a knowledge base of Horn clauses, tracking how many premises of each rule are still unproven and which symbols have been inferred, and checks whether the goal `duck` follows.

## How to run

From this folder:

```bash
python3 lab3.py
```

Requires: Python 3 for the Python labs, `g++` for the C++ labs, and SWI-Prolog or GNU Prolog for labs 4 and 5.

## Concepts

- Propositional logic
- Horn clauses
- Forward chaining

[Back to CMPS 3560](../)
