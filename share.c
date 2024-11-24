#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 24

static long num_steps = 1000 * 1000 * 1000;
double step;

/*
    Summation calculation of PI using worksharing with a reduction
*/

int main()
{
    int i;
    double x, pi, sum = 0.0;
    double start, time;

    step = 1.0 / (double)num_steps;
    omp_set_num_threads(NUM_THREADS);
    omp_set_dynamic(0);
    start = omp_get_wtime();

    #pragma omp parallel for private(x) reduction(+:sum)
    for (i = 0; i < num_steps; i++)
    {
        x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }

    pi = sum * step;
    time = omp_get_wtime() - start;

    printf("Method: Worksharing with a reduction\n");
    printf("NUM_THREADS = %d\n", NUM_THREADS);
    printf("Pi = %f\n", pi);
    printf("Time = %f s\n", time);
}
