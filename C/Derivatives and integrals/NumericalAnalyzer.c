#include "infi.h"
#include <stdio.h>
#include <stdlib.h>

static const char *invalid_msg =
        "Invalid input\n";

static const char *args_msg =
        "Usage: NumericalAnalyzer <function number> <a> <b> <N> <x0> <h>\n";

/**
 * First function that is supported
 * by the NumericalAnalyzer program
 * @param x Value received by the function
 * @return corresponding value in the function's
 * image for that value
 */

static double f1(double x)
{
    return  pow(x, 2) / 4;
}

/**
 * Second function that is supported
 * by the NumericalAnalyzer program
 * @param x Value received by the function
 * @return corresponding value in the function's
 * image for that value
 */

static double f2(double x)
{
    if(x <= 0)
    {
        return NAN;
    }

    return (-pow(x, 3) + 3 * pow(x, 2) + x - 4 * sqrt(x)) /
            (2 * x * sqrt(x));
}

/**
 * Third function that is supported
 * by the NumericalAnalyzer program
 * @param x Value received by the function
 * @return corresponding value in the function's
 * image for that value
 */

static double f3(double x)
{
    return pow(sin(x), 2) - pow(cos(x), 2);
}

/**
 * Fourth function that is supported
 * by the NumericalAnalyzer program
 * @param x Value received by the function
 * @return corresponding value in the function's
 * image for that value
 */

static double f4(double x)
{
    return (sin(x) / (1 + cos(2 * x)));
}

/**
 * Fifth function that is supported
 * by the NumericalAnalyzer program
 * @param x Value received by the function
 * @return corresponding value in the function's
 * image for that value
 */

static double f5(double x)
{
    return pow(M_E, x);
}

/**
 * Sixth function that is supported
 * by the NumericalAnalyzer program
 * @param x Value received by the function
 * @return corresponding value in the function's
 * image for that value
 */

static double f6(double x)
{
    return (sinh(2 * x) / (M_E * pow(x, 2)));
}

/**
 * checks if the given number is a natural or rational number
 * @param number The number to check
 * @return int value of the number if number is natural,
 * 0 code if number is a legal rational but not natural,
 * -1 otherwise
 */

static int isRational(const char *number)
{
    char *ptr;
    double d = strtod(number, &ptr);

    //check if conversion was successful
    if(number != ptr)
    {
        //check if number is natural
        if (d > 0)
        {
            if (ceil(d) == d)
            {
                return (int) d;
            }
        }
        //if number is rational but not natural
        return 0;
    }
    //if not a legal number
    return -1;
}

/**
 * Function that receives a serial number and returns
 * the corresponding function which is represented by it
 * @param func_num The serial number
 * @return A function of type - double (*func)(double)
 */

RealFunction chooseFunc(int func_num)
{
    switch (func_num)
    {
        case 1:
            return f1;

        case 2:
            return f2;

        case 3:
            return f3;

        case 4:
            return f4;

        case 5:
            return f5;

        case 6:
            return f6;

        default:
            return f1;
    }
}

/**
 * Function that asserts the validity of the arguments
 * sent over to the NumericalAnalyzer program.
 * @param args An array of pointers to the arguments
 * @return 1 if arguments are valid, 0 otherwise
 */

static int checkValues(char *args[])
{
    int funcNumber = isRational(args[1]);
    int a = isRational(args[2]), b = isRational(args[3]);
    int n = isRational(args[4]), x0 = isRational(args[5]);
    int h = isRational(args[6]);

    //if func number is not a natural between 1 and 6,
    //return EXIT_FAILURE
    if (funcNumber > 0)
    {
        if (funcNumber > 6)
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }

    //if one of a and b is not a valid number, or a > b, return 0
    if(a >= 0 && b >= 0)
    {
        char *a_ptr, *b_ptr ;
        if(strtod(args[2], &a_ptr) > strtod(args[2], &b_ptr))
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }

    //if n is not a natural number, or x0
    // is not a rational number return 0
    if(n <= 0 || x0 == -1)
    {
        return 0;
    }

    //if h is not a valid number, or is
    //equal or smaller than 0, return 0
    if(h >= 0)
    {
        char *h_ptr;
        if(strtod(args[6], &h_ptr) <= 0)
        {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char *argv[])
{
    //case of wrong number of arguments
    if (argc != 7)
    {
        fprintf(stderr, "%s", args_msg);
        return EXIT_FAILURE;
    }

    //check if there is non valid input
    if(!checkValues(argv))
    {
        fprintf(stderr, "%s", invalid_msg);
        return EXIT_FAILURE;
    }

    //define the variables to pass onto the functions of the infi lib
    char* ptr;
    RealFunction f = chooseFunc(argv[1][0] - '0');
    double a = (strtod(argv[2], &ptr)), b = (strtod(argv[3], &ptr));
    unsigned int n = (unsigned int)strtod(argv[4], &ptr);
    double x0 = strtod(argv[5], &ptr), h = strtod(argv[6], &ptr);

    double integral = integration(f, a, b, n),
    derivative_result = derivative(f, x0, h);

    //check that entered values are the domain of
    //the given function. If not, return ERROR_FAILURE
    //code.
    if (integral == NAN || derivative_result == NAN)
    {
        fprintf(stderr, "%s", invalid_msg);
        return EXIT_FAILURE;
    }

    printf("Integral: %0.5f\nDerivative: %0.5f",
           integral, derivative_result);

    return EXIT_SUCCESS;
}