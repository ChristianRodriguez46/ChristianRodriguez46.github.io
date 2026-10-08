# Lab 7 – OpenMP Locks: Observation

## Execution Time Results

| Version | Threads | Time (seconds) |
|---|---|---|
| Sequential | 1 | 0.000374 |
| Parallel (Locks) | 20 | 0.014644 |

## Analysis

The parallel version was approximately **39× slower** than the sequential version.
This is expected and not a bug — it is a classic demonstration of **lock overhead dominating over parallelism gains**.

## Reasons for Slowdown

- **Trivially small work per iteration** — the histogram body is just `hist[X[i]]++`, a single integer increment. The actual computation takes almost no time, so there is very little to gain from parallelism.

- **High lock contention** — with only 10 bins and 20 threads, multiple threads constantly compete for the same locks. Threads spend most of their time waiting to acquire a lock rather than doing useful work.

- **Synchronization overhead** — `omp_set_lock()` and `omp_unset_lock()` are expensive system-level operations compared to a simple increment.

- **Thread creation and management overhead** — spawning and coordinating 20 threads adds fixed overhead that only pays off when the work per thread is substantial.

## Conclusion

Parallelism provides the greatest benefit when computation is expensive relative to synchronization cost. For a histogram over only 100,000 simple increments, the serial version is faster because there is no synchronization overhead at all. The parallel version would begin to outperform the sequential version with a significantly larger array (e.g., hundreds of millions of elements), where actual computation time dwarfs the cost of acquiring and releasing locks.