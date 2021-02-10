#include "Fractal.h"

/**
 * Main program. Reads the contents of a csv file that contains
 * fractal specification. If the contents are valid, prints all
 * the fractals and return EXIT_SUCCESS code. Otherwise, returns
 * EXIT_FAILURE code.
 */

int main(int argc, char *argv[])
{
    //in case of wrong argument
    //number sent to the program
    if(argc != 2)
    {
        cerr << argsError;
        return EXIT_FAILURE;
    }

    vector<Fractal*> fractalList;
    int errIndicator = EXIT_SUCCESS;

    Fractal :: readFile(argv[1], errIndicator, fractalList);

    if(errIndicator == EXIT_FAILURE)
    {
        //free all the memory of the objects
        //contained inside the vector object
        while (!fractalList.empty())
        {
            delete fractalList.back();
            fractalList.pop_back();
        }

        cerr << invalidError;
        return EXIT_FAILURE;
    }
    else
    {
        while (!fractalList.empty())
        {
            //print all of the fractals in the vector
            fractalList.back()->draw();
            cout << "\n";
            delete fractalList.back();
            fractalList.pop_back();
        }
    }

    return EXIT_SUCCESS;
}
