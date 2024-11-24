#include <stdio.h>
#include <omp.h>


static long num_steps = 1000 * 1000 * 1000;
double step, start, time;

/*
    Summation calculation of PI using a serial method
*/

int main()
{
    int i;
    double x, pi, sum = 0.0;

    step = 1.0 / (double)num_steps;

    start = omp_get_wtime();

    for (i = 0; i < num_steps; i++)
    {
        x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }

    pi = sum * step;

    time = omp_get_wtime() - start;

    printf("Method: Serial\n");
    printf("NUM_THREADS = 1\n");
    printf("Pi = %f\n", pi);
    printf("Time = %f s\n", time);
}
