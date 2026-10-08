# Pocket perceptron

**CMPS 3560 Artificial Intelligence**, Lab 8

## What it does

`perceptron.cpp` trains a perceptron on the normalized Iris data set, shuffling the samples each epoch and keeping the best weights seen so far (the *pocket* algorithm). It prints the weights and accuracy as training progresses.

## How to run

From this folder:

```bash
make
./perceptron iris_full_normalized.csv
```

Requires: Python 3 for the Python labs, `g++` for the C++ labs, and SWI-Prolog or GNU Prolog for labs 4 and 5.

## Concepts

- Perceptrons
- Linear classification
- Training loops

[Back to CMPS 3560](../)
