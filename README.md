## Exercises from OpenMP Common Core

Each file calculates the value of Pi by summation integration using different methods in the OpenMP standard to demonstrate relative time efficiency. Summation step size is defined as 1 * 10 ^ 9 as determined by trial-and-error to show a noticeable difference in performance on an Intel Core i9-12900K (3187 Mhz, 16 Cores, 24 Logical Processors).

The methods, in order of increasing performance, are as follows:
* Naive Single Process Multiple Data (SPMD) implementation (results in false sharing + overhead)
* Serial (no parallelismm)
* SPMD with a 64-byte L1 cache pad
* SPMD with an OMP atomic section
* SPMD with an OMP critical section
* OMP Worksharing (OMP parallel For Loop)

This exercise aims to illustrate that outperforming OMP's optimized toolset would generally require a much greater understanding of specific architecture than most developers, especially junior ones, would likely achieve without significant time investment.
