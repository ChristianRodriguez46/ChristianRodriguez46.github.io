# Multiclass neural network

**CMPS 3560 Artificial Intelligence**, Lab 9

Read this lab with snapshots and notes on every file: [https://christianrodriguez46.github.io/Coursework/cmps3560/lab09/](https://christianrodriguez46.github.io/Coursework/cmps3560/lab09/)

## What it does

`lab9_nn.cpp` builds a neural network from scratch (4 inputs, a hidden layer of 3 neurons, 3 outputs) with Xavier weight initialization, trained by stochastic gradient descent, and trains it to classify the three Iris species. It reports the mean absolute deviation error and accuracy as it trains.

## How to run

From this folder:

```bash
g++ -std=c++17 -O2 -o lab9_nn lab9_nn.cpp
./lab9_nn iris.csv
```

Requires: Python 3 for the Python labs, `g++` for the C++ labs, and SWI-Prolog or GNU Prolog for labs 4 and 5.

## Concepts

- Neural networks
- Backpropagation
- Multiclass classification

[Back to CMPS 3560](../)
