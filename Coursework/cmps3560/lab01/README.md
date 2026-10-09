# Rule-based classifier for iris flowers

**CMPS 3560 Artificial Intelligence**, Lab 1

Read this lab with snapshots and notes on every file: [https://christianrodriguez46.github.io/Coursework/cmps3560/lab01/](https://christianrodriguez46.github.io/Coursework/cmps3560/lab01/)

## What it does

`expsys.cpp` reads `iris.csv` into a 2-D array and classifies each flower as Versicolor or Virginica with a hand-written rule on petal length, then prints each prediction next to the true label.

## How to run

From this folder:

```bash
g++ -o expsys expsys.cpp
./expsys iris.csv
```

Requires: Python 3 for the Python labs, `g++` for the C++ labs, and SWI-Prolog or GNU Prolog for labs 4 and 5.

## Concepts

- Expert systems
- Reading CSV data

[Back to CMPS 3560](../)
