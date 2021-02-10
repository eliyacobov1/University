#include "osm.h"
#include <sys/time.h>
#include <sys/unistd.h>
#include <iostream>
#include <cmath>

#define ERROR_CODE -1;
#define UNROLLING_COEFFICIENT 6

static int TRAP = 1, FUNCTION = 2, ADDITION = 3;
static double NANO_MULTIPLIER = pow(10, 9), MILLI_MULTIPLIER = pow(10, 3);

static int testNum1 = 12, testNum2 = 2, testNum3;

/**
 * An empty function call
 */
static void emptyFunc()
{
}

/**
 * Static functions which executes one of three time measurement tests
 * @param testNum The number of the corresponding test
 * @param iterations  The number of iterations that will take place in
 * order to determine the Test average time
 * @return The final result (average time)
 */
static double timeMeasurementTest(int testNum, unsigned int iterations)
{
    if (iterations == 0) // Illegal number of iterations
    {
        return ERROR_CODE
    }

    unsigned int realIterations = iterations / UNROLLING_COEFFICIENT;
    unsigned int remainder = (realIterations * UNROLLING_COEFFICIENT) < iterations  ? 1 : 0;

    // In each of the cases, the chosen operation will be executed using
    // loop unrolling. Therefore, the actual number of iterations will be
    // the calculation above and in order to narrow the gap from the actual
    // number of iterations, a remainder will also be taken under consideration

    struct timeval before, after;
    struct timezone timeZone{};
    double time_taken;
    // variables that help indicate whether or not there was an error in the system call
    int beforeErrorIndicator = 0, afterErrorIndicator = 0;

    if (testNum == TRAP)
    {
        beforeErrorIndicator = gettimeofday(&before, &timeZone);
        for(unsigned int i = 0; i < realIterations + remainder; i += 10)
        {
            OSM_NULLSYSCALL;
            OSM_NULLSYSCALL;
            OSM_NULLSYSCALL;
            OSM_NULLSYSCALL;
            OSM_NULLSYSCALL;
            OSM_NULLSYSCALL;
        }
        afterErrorIndicator = gettimeofday(&after, &timeZone);
    }

    else if (testNum == FUNCTION)
    {
        beforeErrorIndicator = gettimeofday(&before, &timeZone);
        for(unsigned int i = 0; i < realIterations + remainder; i += 10)
        {
            emptyFunc();
            emptyFunc();
            emptyFunc();
            emptyFunc();
            emptyFunc();
            emptyFunc();
        }
        afterErrorIndicator = gettimeofday(&after, &timeZone);
    }

    else if (testNum == ADDITION)
    {
        beforeErrorIndicator = gettimeofday(&before, &timeZone);
        for(unsigned int i = 0; i < realIterations + remainder; i += 10)
        {
            testNum3 = testNum1 + testNum2; // simple addition instruction
            testNum3 = testNum1 + testNum2;
            testNum3 = testNum1 + testNum2;
            testNum3 = testNum1 + testNum2;
            testNum3 = testNum1 + testNum2;
            testNum3 = testNum1 + testNum2;
        }

        afterErrorIndicator = gettimeofday(&after, &timeZone);
    }

    if ((beforeErrorIndicator != EXIT_SUCCESS) | (afterErrorIndicator != EXIT_SUCCESS))
    {
        return ERROR_CODE
    }
//    timersub(&after, &before, &total);
//    return  (double) ((total.tv_sec * NANO_MULTIPLIER) + (total.tv_usec * MILLI_MULTIPLIER))/ iterations;
//    return (double) (((after.tv_sec * NANO_MULTIPLIER) + (after.tv_usec * MILLI_MULTIPLIER)) -
//                     ((before.tv_sec * NANO_MULTIPLIER) + (before.tv_usec * MILLI_MULTIPLIER))) / iterations;
     time_taken = (after.tv_sec - before.tv_sec) * 1e6;
    return (time_taken + (after.tv_usec - before.tv_usec)) * 1e-6/ iterations;
}

/**
 * A simple addition time measurement test
 */
double osm_operation_time(unsigned int iterations)
{
    return timeMeasurementTest(ADDITION, iterations);
}

/**
 * An empty function time measurement test
 */
double osm_function_time(unsigned int iterations)
{
    return timeMeasurementTest(FUNCTION, iterations);
}

/**
 * Trap time measurement test
 */
double osm_syscall_time(unsigned int iterations)
{
    return timeMeasurementTest(TRAP, iterations);
}

//int main(int argc, char *argv[])
//{
//    int iterations;
//
//    std::cout<< "Enter the desired number of iterations: \n";
//    std::cin >> iterations;
//
//    std::cout  << "\n\nTrap time is: " << osm_syscall_time(iterations) << "\n\nEmpty function time is: "
//               << osm_function_time(iterations) << "\n\nAddition instruction time is: "
//               << osm_operation_time(iterations) << "\n";
//
//    return EXIT_SUCCESS;
//}