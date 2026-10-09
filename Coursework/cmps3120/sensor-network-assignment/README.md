# Sensor network clustering

**CMPS 3120 Algorithm Analysis**, Assignment

Read this lab with snapshots and notes on every file: [https://christianrodriguez46.github.io/Coursework/cmps3120/sensor-network-assignment/](https://christianrodriguez46.github.io/Coursework/cmps3120/sensor-network-assignment/)

## What it does

- Places 5 cluster heads and N low-end sensor nodes (50 by default) in a 100 by 100 area. Nodes are first assigned at random and the program measures hop counts with breadth-first search over the communication graph. Tabu search then reassigns nodes to lower the total hop count.
- It prints the total hops before and after, and saves a side-by-side plot with the Voronoi diagram to `voronoi_optimization_updated.png` (included).

## How to run

From this folder:

```bash
pip install numpy scipy matplotlib
python3 Assignment.py 50
```

Requires: A C compiler such as `gcc`. The assignment needs Python 3 with NumPy, SciPy and Matplotlib.

## Concepts

- Voronoi diagrams
- Tabu search
- Graph search
- NumPy and Matplotlib

[Back to CMPS 3120](../)
