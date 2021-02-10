#include "Fractal.h"

/**
* main function which is prints the given fractal
* using ASCII art (white spaces and hash tags)
*/

void SierpinskiCarpet :: draw()
{
    for(int i = 0; i < gridLength; i++)
    {
        for(int j = 0; j < gridLength; j++)
        {
            //check if index is in the center of the fractal or one of
            // the sub-fractals. If so, a whitespace is printed out.
            if (isHash(i, j))
            {
                cout << HASH_TAG;
            }
            else
            {
                cout << WHITESPACE;
            }
        }
        cout << "\n";
    }
}

/**
* main function which is prints a SierpinskiSieve
* fractal using ASCII art (white spaces and hash tags)
*/

void SierpinskiSieve :: draw()
{
    for(int i = 0; i < gridLength; i++)
    {
        for(int j = 0; j < gridLength; j++)
        {
            //check if index is in the bottom right quarter of the fractal
            // or of one of the sub-fractals. If so, a whitespace is printed out.
            if (isHash(i, j))
            {
                cout << HASH_TAG;
            }
            else
            {
                cout << WHITESPACE;
            }
        }
        cout << "\n";
    }
}

/**
* main function which is prints the given fractal
* using ASCII art (white spaces and hash tags)
*/

void CantorDust :: draw()
{
    for(int i = 0; i < gridLength; i++)
    {
        for(int j = 0; j < gridLength; j++)
        {
            //check if index is in either in bottom right, upper right,
            // bottom left or upper left corners of the fractal or of one
            // of the sub-fractals. If so, a hash tag is printed out.
            if (isHash(i, j))
            {
                cout << HASH_TAG;
            }
            else
            {
                cout << WHITESPACE;
            }
        }
        cout << "\n";
    }
}

/**
* Function to check if the specific index on the SierpinskiCarpet
* fractal's grid should be printed as a hash tag
* @return True if character in index should be printed as a
* hash tag, false otherwise
*/

bool SierpinskiCarpet :: isHash(int i, int j)
{
    while (1)
    {
        if(i == 0 || j == 0)
        {
            return true;
        }
        if(i % sCarpetLength == 1 && j % sCarpetLength == 1)
        {
            return false;
        }

        i /= sCarpetLength;
        j /= sCarpetLength;
    }
}

/**
* Function to check if the specific index on the SierpinskiSieve
* fractal's grid should be printed as a hash tag
* @return True if character in index should be printed as a
* hash tag, false otherwise
*/

bool SierpinskiSieve :: isHash(int i, int j)
{
    while (1)
    {
        if(i == 0 || j == 0)
        {
            return true;
        }
        if(i % sSieveLength == 1 && j % sSieveLength == 1)
        {
            return false;
        }

        i /= sSieveLength;
        j /= sSieveLength;
    }
}

/**
* Function to check if the specific index on the CantorDust
* fractal's grid should be printed as a hash tag
* @return True if character in index should be printed as a
* hash tag, false otherwise
*/

bool CantorDust ::isHash(int i, int j)
{
    while (1)
    {
        if(i == 0 && j == 0)
        {
            return true;
        }
        if(i % cDustLength == 1 || j % cDustLength == 1)
        {
            return false;
        }

        i /= cDustLength;
        j /= cDustLength;
    }
}

/**
* Reads the given CSV format file and returns a vector
* with the corresponding Fractal type objects
* @param filePath The path to the file
 * @param errorIndicator will be set to EXIT_FAILURE if
* @param list vector with Fractal objects
*/

void Fractal :: readFile(string filePath, int& errorIndicator, vector<Fractal*>& fractalList)
{
    ifstream myFile;
    myFile.open(filePath);

    //in case the program can't open the file
    if(!myFile.is_open())
    {
        errorIndicator = EXIT_FAILURE;
        return;
    }

    string csvLine;
    int elementCounter;

    //iterate through each line in the file
    while(getline(myFile, csvLine))
    {
        //if line starts or ends with a coma, file is corrupted
        if(csvLine[0] == ',' || csvLine[csvLine.length() - 1] == ',')
        {
            errorIndicator = EXIT_FAILURE;
            return;
        }

        //ignore the newline character at the end of the line
        if(csvLine[csvLine.length() - 1] == '\r' ||
           csvLine[csvLine.length() - 1] == '\n')
        {
            csvLine = csvLine.substr(0, csvLine.size()-1);
        }

        istringstream csvStream(csvLine);
        string csvElement;
        elementCounter = 0;

        int dimension = -1, fractalNumber = -1;

        //iterate through the values of the line (between the comas)
        while(getline(csvStream, csvElement, COMA))
        {
            elementCounter++;

            //if value contains more than on char, it is not
            //a single digit number and hence not a valid value.
            //also checks that there are no more than 2 elements
            //in a single line
            if(csvElement.length() > 1 || !isdigit(csvElement[0]) || elementCounter > 2)
            {
                errorIndicator = EXIT_FAILURE;
                return;
            }

            if(elementCounter == 1)
            {
                fractalNumber = csvElement[0] - '0';
            }

            if(elementCounter == 2)
            {
                dimension = csvElement[0] - '0';
            }
        }

        //in case the line holds less then two values
        if(fractalNumber == -1 || elementCounter == -1)
        {
            errorIndicator = EXIT_FAILURE;
            return;
        }

        Fractal* ptr = FractalFactory :: createFractal(fractalNumber, dimension);

        //if factory function returned a nullptr, the meaning is
        // that the arguments are invalid and the file is corrupted
        if(ptr == nullptr)
        {
            errorIndicator = EXIT_FAILURE;
            return;
        }

        //add fractal to the vector
        fractalList.push_back(ptr);
    }

    myFile.close();
}

/**
* Factory static function which receives the arguments
* (degree and fractal type num) and creates the corresponding fractal
* @param fractalNum The number representing the type of fractal-
* 1 : SierpinskiCarpet, 2 : SierpinskiSieve, 3 : CantorDust
* @param dimension The dimension of the fractal (legal input is an integer
* between 1 and 6)
* @param errIndicator An int reference which is set to ErrorFailure if one
* of the given parameters is illegal
* @return Pointer to the corresponding fractal. If illegal arguments are given,
 * a Fractal ptr with the value of nullptr will be returned
*/

Fractal* FractalFactory :: createFractal(int fractalNum, int dimension)
{
    if(dimension < 1 || dimension > 6)
    {
        Fractal* ptr = nullptr;
        return ptr;
    }

    switch (fractalNum)
    {
        case 1 :
        {
            SierpinskiCarpet *ptr1 = new SierpinskiCarpet;
            *ptr1 = SierpinskiCarpet(dimension);
            return ptr1;
        }

        case 2 :
        {
            SierpinskiSieve *ptr2 = new SierpinskiSieve;
            *ptr2 = SierpinskiSieve(dimension);
            return ptr2;
        }

        case 3 :
        {
            CantorDust *ptr3 = new CantorDust;
            *ptr3 = CantorDust(dimension);
            return ptr3;
        }

        default:
        {
            Fractal *ptr = nullptr;
            return ptr;
        }
    }
}