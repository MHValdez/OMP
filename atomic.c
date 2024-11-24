#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 24

static long num_steps = 1000 * 1000 * 1000;
double step;

/*
    Summation calculation of PI using OpenMP with a SPMD pattern and an atomic section
*/

int main()
{
    int nthreads;
    double pi = 0.0;
    double start, time;

    step = 1.0 / (double)num_steps;
    omp_set_num_threads(NUM_THREADS);

    start = omp_get_wtime();

    #pragma omp parallel
    {   
        int i, id, nthrds;
        double x, sum;

        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();

        if (id == 0)
        {
            nthreads = nthrds;
        }

        for (i = id, sum = 0.0; i < num_steps; i += nthreads)
        {
            x = (i + 0.5) * step;
            sum += 4.0 / (1.0 + x * x);
        }

        sum *= step;

        #pragma omp atomic
        pi += sum;
    }

    time = omp_get_wtime() - start;

    printf("Method: SPMD with an atomic section\n");
    printf("NUM_THREADS = %d\n", NUM_THREADS);
    printf("Pi = %f\n", pi);
    printf("Time = %f s\n", time);
}
