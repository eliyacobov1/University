#include <stdio.h>
#include <stdlib.h> //Imported for "EXIT_FAILURE" and "EXIT_SUCCESS"
#include <string.h> //Imported for "str tok"
#include <math.h> //Imported for "pow", "ceil", "floor"

#define MAX_INPUT 1024
#define ARRAY_SIZE 100
#define M 100
#define N 100
#define INPUT_DELIMITER " \t\r\n"
#define DOT '.'
#define UNDERFLOW_BOUNDARY 0.00000001

//define multiplication macro function
#define MULTIPLY(a,  b) (a) * (b)

//manually define "isdigit" like function because the
// original one is problematic with the given code
//(following syntax is applicable and valid with C99 standard)
#define CHECK_DIGIT(a) (a >= '0' && a <= '9')

//macro function that returns the affine representation of
// a number according to array length which it is stored in
#define AFFINE(n, length) (n + (int)floor((double)length / 2.0))

/**
 * function that converts a number from string form to int type
 * @param string_value the number in string form (char array)
 * @param length length of the given array
 * @return the int type number
 */

double StringToNum(const char string_value[], int length)
{
    double numeric_value = 0;

        //calculate the whole num while ignoring a dot (if existent)
        //also, keep the index of the dot
        int dot_index  =  -1;
        for(int i  =  0, j = length-1;  i < length; i++, j--)
        {
            if (string_value[i]  ==  DOT)
            {
                dot_index = j;
                j++;
                continue;
            }

            int digit = string_value[i] - '0';
            numeric_value +=  MULTIPLY(digit, (int)pow(10, j));
        }

        //use the index of the dot to divide the number
        //by 10 in the appropriate power
        return (numeric_value / pow(10, dot_index + 1));
}

/**
 * checks if string matches the pattern of a rational
 * number. i.e: does not contain more than 9 chars,
 * contains 1/0 dots (which is not the last char of the number),
 * aside from the dot,  consists of numeric chars (between '0'-'9')
 * @param number the string (char array) which represents the number
 * @param length length of the char array
 * @return EXIT_SUCCESS code if number is rational, EXIT_FAILURE code otherwise
 */

int IsRational(const char *number, int length)
{
    //check if number is longer than 9 char,  starts
    // with a dot or a zero (without a subsequent dot) or
    // ends with a dot. if so,  returns an error.
    if (length>9 || number[length-1] == DOT ||
        (number[0]-'0' == 0 && CHECK_DIGIT(number[1]))
        || number[0] == DOT)
    {
        return EXIT_FAILURE;
    }
    int dot_counter = 0;

    //check if string is made out of numbers and max of one dot only.
    for(int j = 0; j<length; j++)
    {
        if (number[j]  ==  DOT)
        {
            dot_counter +=  1;

            //if more than one dot in the number,
            // returns an error
            if (dot_counter > 1)
            {
                return EXIT_FAILURE;
            }
            continue;
        }
        if (! (CHECK_DIGIT(number[j])))
        {
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

/**
 * checks if the given number is a natural number (or 0)
 * @param number the number to check
 * @return EXIT_SUCCESS code if number is natural,
 * EXIT_FAILURE code otherwise
 */

int IsNatural(char number[], int length)
{
    //use str chr to check if there isn't a dot in the number,  also makes asserts that
    //the number is rational and not negative
    if(isrational(number,  length) == EXIT_SUCCESS && strchr(number, DOT) == NULL )
    {
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

/**
 * gets user input,  converts the char's to double's,
 * and stores the values in the given array
 * @param num_array the array to store the values in
 * @return length of input if successful,
 * EXIT_FAILURE code otherwise (if input does not consist of rational numbers only
 * or more than 100 numbers are given)
 */

int SeriesInput(double num_array[])
{
    //create array to store the input in
    char array[MAX_INPUT];

    //if input is empty,  returns a 0.
    if (fgets(array,  MAX_INPUT,  stdin)  ==  NULL)
    {
        return 0;
    }

    //check if each value separated by a whitespace is a rational number.`
    //if so, adds these to the arrays above
    char *value = NULL;
    value = strtok(array, INPUT_DELIMITER);
    int i = 0;

    while (value != NULL && i <= ARRAY_SIZE)
    {
        // Read the value and assert that it is a rational number.
        //if not,  an error is returned. else,  adds the number to the
        //new array
        int length = (int)strlen(value);

        //check if number is rational. if not,  returns a 0.
        if(isrational(value, length) == EXIT_FAILURE)
        {
            return 0;
        }
        //insert numeric value to the final array
        num_array[i] = StringToNum(value, length);
        value = strtok(NULL, INPUT_DELIMITER);
        i++;

        //if input line exceeds 100 numbers, returns 0.
        if(i>ARRAY_SIZE)
        {
            return 0;
        }
    }
    return i;
}

/**
 * gets  user input and if it is a natural number,
 * return the number.
 * @return int representing the input code if input is indeed a natural number,
 * -1 otherwise
 */

int numberInput()
{
    char array[MAX_INPUT];

    //if input is empty,  returns an error code.
    if (fgets(array,  MAX_INPUT,  stdin)  ==  NULL)
    {
        return -1;
    }
    //represents the number's length
    int length;

    if(array[strlen(array)-1] == '\n')
    {
        //subtract 1 because of the \n char
        length = (int)strlen(array) - 1;
    }
    else
    {
      length = (int)strlen(array);
    }

    //check if input is natural number
    if (isnatural(array, length) == EXIT_SUCCESS)
    {
        return (int)StringToNum(array, length);
    }
    return -1;
}

/**
 * centers the values of a double array
 * @param array the given array of values
 * @param array_copy an array of the same size as the original one
 * @param index represents the number of 'used' values
 * in the array
 * @param length the length of the array
 */

void center(double array[], double array_copy[], int index, int length)
{
    for(int i = 0; i<length; i++)
    {
        array_copy[i] = array[i];
    }
    //define start and value indexes to write values to.
    //rest of indexes will be overwritten with a 0.
    int start_index = (int)((length / 2.0) - ceil((double)(index) / 2));
    int end_index = start_index + index;

    for(int i = 0, j = 0; i<length; i++)
    {
        if(i >= start_index && i < end_index)
        {
            array[i] = array_copy[j];
            j++;
        }
        else
        {
            array[i] = 0;
        }
    }
}

/**
 * normalize the array values using L1 norm
 * @param array the array of values
 * @param length the length of the array
 */

void norm(double array[], int length)
{
    //calculate sum of values
    double sum = 0;

    for(int i = 0; i<length; i++)
    {
        sum += array[i];
    }
    //normalizing the values according to L1 norm
    for(int i = 0; i<length; i++)
    {
        if (sum < UNDERFLOW_BOUNDARY)
        {
            array[i] = 0;
        }
        else
        {
            array[i] /= sum;
        }
    }
}

/**
 * perform convolution on the array values n times and return a
 * pointer to the results array
 * @param g first series array of values
 * @param f second series array of values
 * @param n number of times to preform convolution
 * @return pointer to the normed double array with the results
 */

void convolution(double g[], const double h[], int n)
{
    double results_array[N];

    //define the range for t
    int min_t = (int)ceil(N / -2.0) - 1, max_t = (int)floor(N / 2.0) - 1;

    //define range for m
    int min_m = (int) ceil(M / -2.0), max_m = (int) floor(M / 2.0);

    //outer loop that defines iteration n times
    // (number of times convolution is calculated)
    for (int i = n; i > 0; i--)
    {
        for (int t = min_t; t <= max_t; t++)
        {
            //define the index in the results array to store the calculated
            //sum in each iteration
            int index = AFFINE(t, N) + 1;
            results_array[index] = 0.0;

            for (int m = min_m; m <= max_m; m++)
            {
                //use affine representation and check if index's are
                //in array borders. If so, add values to sum. Else, continue.
                int index1 = AFFINE(t-m, N), index2 = AFFINE(m, M);
                if (((index1) >= 0 && (index1) < N) && ((index2) >= 0 && (index2) < M))
                {
                    results_array[index] += MULTIPLY(g[index1], h[index2]);
                }
                else
                {
                    continue;
                }
            }
        }
        //norm the results array after convolution
        norm(results_array, N);

        //copy the results array to g in
        // order to calculate convolution again
        for(int j = 0; j<N; j++)
        {
            g[j] = results_array[j];
            results_array[j] = 0.0;
        }
    }
}

/**
 * round all values of double array up to 3 digits
 * subsequent to the decimal separator (dot)
 * @param array the array of values
 * @param length the length of the array
 */

void round3(double array[], int length)
{
    for(int i = 0; i < length; i++)
    {
        array[i] = (round(1000*array[i]) / 1000);
    }
}

/**
 * finds max of array with double non negative values
 * @param array the array of values
 * @param length the length of the array
 * @return the maximum value of the array
 */

double maxvalue(const double array[], int length)
{
    double max = 0.0;
    for(int i = 0; i < length; i++)
    {
        if (array[i] > max)
        {
            max = array[i];
        }
    }
    return max;
}

/**
 * prints histogram of the given array
 * @param r the double array
 * @param length the length of the array
 * @param max the max value of the array (should
 * be calculated beforehand in the main program)
 */

void histogram(double r[], int length, double max)
{
    int num_stars;
    for(int i = 0; i < length; i++)
    {
        num_stars = (int)(floor((r[i] / max)*20));
        printf("%.3lf: ", r[i]);
        for(int j = 0; j < num_stars; j++)
        {
            printf("*");
        }
        printf("\n");
    }
}

int main()
{
    //create and initialize arrays to store the numbers in
    double g[N], h[M];
    for(int i = 0; i<ARRAY_SIZE; i++)
    {
        g[i] = 0.0;
        h[i] = 0.0;
    }

    //insert input values to the arrays and room# variable and check validity.
    //if input violates a guideline,  returns an error
     int g_size = seriesinput(g);
     if (g_size == 0)
     {
         fprintf(stderr, "ERROR\n");
         return EXIT_FAILURE;
     }

    int h_size = seriesinput(h);
    if (h_size == 0 || h_size > g_size)
    {
        fprintf(stderr, "ERROR\n");
        return EXIT_FAILURE;
    }

    //represents number of nested rooms
    const int n = numinput();
    if(n == -1)
    {
        fprintf(stderr, "ERROR\n");
        return EXIT_FAILURE;
    }

    //if one of the arrays contains only 0's, return exit code
    int a = 0, b = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i)
    {
        if(g[i] != 0)
        {
            a = 1;
        }

        if(h[i] != 0)
        {
            b = 1;
        }
    }

    if(a == 0 || b == 0)
    {
        return EXIT_SUCCESS;
    }

    //center and norm the values of the arrays
    double g_copy[N];
    center(g, g_copy, g_size, N);
    norm(g, N);

    double h_copy[N];
    center(h, h_copy, h_size, M);
    norm(h, M);

    //if n = 0,  no convolution will be made and values of g
    //will be printed
    if(n > 0)
    {
        convolution(g, h, n);
    }
    //round all values of the array, and find max value
    round3(g, N);

    double max = maxvalue(g, N);

    //print histogram if max value is legal
    //(will not yield division underflow)
    if(max > UNDERFLOW_BOUNDARY)
    {
        histogram(g, N, max);
    }

    return EXIT_SUCCESS;
}