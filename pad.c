#include <stdio.h>
#include <omp.h>

#define PAD 8 // assume 64 byte L1 cache line size (8 doubles)
#define NUM_THREADS 24

static long num_steps = 1000 * 1000 * 1000;
double step;

/*
    Summation calculation of PI using OpenMP with a SPMD pattern and padding
*/

int main()
{
    int i, nthreads;
    double pi, sum[NUM_THREADS][PAD];
    double start, time;

    step = 1.0 / (double)num_steps;
    omp_set_num_threads(NUM_THREADS);

    start = omp_get_wtime();

    #pragma omp parallel
    {   
        int j, id, nthrds;
        double x;

        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();

        if (id == 0)
        {
            nthreads = nthrds;
        } 

        for (j = id, sum[id][0] = 0.0; j < num_steps; j += nthreads)
        {
            x = (j + 0.5) * step;
            sum[id][0] += 4.0 / (1.0 + x * x);
        }
    }

    for (i = 0, pi = 0.0; i < nthreads; i++)
    {
        pi += sum[i][0] * step;
    }

    time = omp_get_wtime() - start;

    printf("Method: SPMD with padding\n");
    printf("NUM_THREADS = %d\n", NUM_THREADS);
    printf("Pi = %f\n", pi);
    printf("Time = %f s\n", time);
}
