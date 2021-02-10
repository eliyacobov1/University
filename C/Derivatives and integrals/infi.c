#include "infi.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * Computes the numerical integration for the given rationale function
 * at the given numbers range, based on Riemann sums.
 * @param f The rational function
 * @param a The lower bound of the range
 * @param b The higher bound of the range
 * @param n
 * @return The differentiate.
 */

double integration(RealFunction f, double a, double b, unsigned int n)
{
    assert(n != 0 && b >= a);

    //if f is not well defined in the calculated values,
    //user entered numbers that are not part of f's domain.
    //therefore NAN will be returned
    if(f(a) == NAN || f(b) == NAN)
    {
        return NAN;
    }

    double diff_x = (b - a) / n;

    //define a partition for the numbers in the given range
    double *P = (double*)malloc((n + 1) * sizeof(double)), integral = 0;
    P[0] = a;
    P[n] = b;

    for(int i = 1; (unsigned int)i <= n; i++)
    {
        P[i] = a + (diff_x * i);

        //add the i'th epsilon value to the sum
        integral += f((P[i - 1] + P[i]) / 2);
    }
    integral *= diff_x;

    //free the partition values array memory
    double **ptr = &P;
    free(*ptr);
    *ptr = NULL;

    return integral;
}

/**
 * Computes a numerical derivative for the given rationale function
 * at the point, for a given epsilon.
 * @param f The rational function
 * @param x0 The given point.
 * @param h The given epsilon value.
 * @return The differentiate.
 */

double derivative(RealFunction f, double x0, double h)
{
    assert(h > 0);

    //if f is not well defined in the calculated values,
    //user entered numbers that are not part of f's domain
    //therefore NAN will be returned
    if(f(x0 + h) == NAN || f(x0-h) == NAN)
    {
        return NAN;
    }

    return (f(x0 + h) - f(x0 - h)) / (2 * h);
}