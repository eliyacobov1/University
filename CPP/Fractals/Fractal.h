#ifndef EX1_FRACTAL_H
#define EX1_FRACTAL_H
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include "vector"

using std :: string;
using std :: cout;
using std :: cerr;
using std :: istringstream;
using std :: ifstream;
using std :: vector;

const string argsError = "Usage: FractalDrawer <file path>\n";
const string invalidError = "Invalid input\n";
char const WHITESPACE = ' ', HASH_TAG = '#', COMA = ',';
int const sCarpetLength = 3, sSieveLength = 2, cDustLength = 3;

/**
 * Father class of fractal object
 */

class Fractal
{
protected:
    /**
     * Represents the dimension/height of the fractal object
     */
    int _dimension;

    /**
     * Represents the length of the grid layout of the fractal object
     */
    int gridLength;

    /**
     * Function to check if the specific index on the fractal's
     * grid should be printed as a hash tag
     * @return True if character in index should be printed as a
     * hash tag, false otherwise
     */
    virtual bool isHash(int, int){return true; };

public:
    /**
     * Default Constructor
     */

    Fractal()
    {
        _dimension = 1;
        gridLength = 2;
    };

    /**
     * Constructor for a Fractal type object
     */

    Fractal(int dimension, int length)
    {
        _dimension = dimension;
        gridLength = pow(length, _dimension);
    };

    /**
     * Destructor
     */

    virtual ~Fractal() = default;

    /**
     * swaps between two SierpinskiCarpet objects
     */

    virtual void draw() = 0;

    /**
     * Reads the given CSV format file and returns a vector
     * with the corresponding Fractal type objects
     * @return vector with Fractal objects
     */

    static void readFile(string, int&, vector<Fractal*>&);
};

/**
 * SierpinskiCarpet class, Derived class of fractal class
 */

class SierpinskiCarpet : public Fractal
{
private:
    /**
     * Function to check if the specific index on the SierpinskiCarpet
     * fractal's grid should be printed as a hash tag
     * @return True if character in index should be printed as a
     * hash tag, false otherwise
     */

    bool isHash(int, int) override;

public:
    /**
     * Default Constructor
     */

    SierpinskiCarpet() :
            Fractal(){};

    /**
     * Constructor for a SierpinskiCarpet type object
     */

    explicit SierpinskiCarpet(int d) :
    Fractal(d, sCarpetLength){};

    /**
     * Destructor
     */

    virtual ~SierpinskiCarpet() = default;

    /**
     * Override for the '=' assigment operator
     */

    SierpinskiCarpet& operator=(SierpinskiCarpet &) = default;

    /**
     * Override for the '=' move operator
     */

    SierpinskiCarpet& operator=(SierpinskiCarpet && ) = default;

    /**
     * Copy Constructor
     */

    SierpinskiCarpet(const SierpinskiCarpet & other) = default;

    /**
     * Move Constructor
     */

    SierpinskiCarpet(SierpinskiCarpet && other) = default;

    /**
     * main function which is prints a SierpinskiCarpet
     * fractal using ASCII art (white spaces and hash tags)
     */

    void draw() override;
};

/**
 * SierpinskiSieve class, Derived class of fractal class
 */

class SierpinskiSieve : public Fractal
{
private:
    /**
     * Function to check if the specific index on the SierpinskiSieve
     * fractal's grid should be printed as a hash tag
     * @return True if character in index should be printed as a
     * hash tag, false otherwise
     */

    bool isHash(int, int) override;

public:
    /**
     * Default Constructor
     */

    inline SierpinskiSieve() :
            Fractal(){};

    /**
     * Constructor for a SierpinskiCarpet type object
     */

    explicit SierpinskiSieve(const int d):
            Fractal(d, sSieveLength){};

    /**
     * Destructor
     */

    ~SierpinskiSieve() = default;

    /**
     * Override for the '=' assigment operator
     */

    SierpinskiSieve& operator=(SierpinskiSieve &) = default;

    /**
     * Override for the '=' move operator
     */

    SierpinskiSieve& operator=(SierpinskiSieve && ) = default;

    /**
     * Copy Constructor
     */

    SierpinskiSieve(const SierpinskiSieve & other) = default;

    /**
     * Move Constructor
     */

    SierpinskiSieve(SierpinskiSieve && other) = default;

    /**
     * main function which is prints a SierpinskiSieve
     * fractal using ASCII art (white spaces and hash tags)
     */

    void draw() override;
};

/**
 * CantorDust class, Derived class of fractal class
 */

class CantorDust : public Fractal
{
private:
    /**
     * Function to check if the specific index on the CantorDust
     * fractal's grid should be printed as a hash tag
     * @return True if character in index should be printed as a
     * hash tag, false otherwise
     */

    bool isHash(int, int) override;

public:
    /**
     * Default Constructor
     */

    CantorDust() :
            Fractal(){};

    /**
     * Constructor for a SierpinskiCarpet type object
     */
    explicit CantorDust(const int d):
    Fractal(d, cDustLength){};

    /**
     * Destructor
     */
    ~CantorDust() = default;

    /**
     * Override for the '=' assigment operator
     */

    CantorDust& operator=(CantorDust & ) = default;

    /**
     * Override for the '=' move operator
     */

    CantorDust& operator=(CantorDust && ) = default;

    /**
     * Copy Constructor
     */

    CantorDust(const CantorDust & other) = default;

    /**
     * Move Constructor
     */

    CantorDust(CantorDust && other) = default;

    /**
     * main function which is prints a CantorDust fractal
     * using ASCII art (white spaces and hash tags)
     */

    void draw() override;
};

/**
 * factory class that yields a Fractal object
 */

class FractalFactory
{
public:

    /**
     * Factory static function which receives the arguments
     * (degree and fractal type num) and creates the corresponding fractal
     * @param fractalNum The number representing the type of fractal-
     * 1 : SierpinskiCarpet, 2 : SierpinskiSieve, 3 : CantorDust
     * @param dimension The dimension of the fractal (legal input is an integer
     * between 1 and 6)
     * @param errIndicator An int reference which is set to ErrorFailure if one
     * of the given parameters is illegal
     * @return The corresponding fractal. If illegal arguments are given, a default
     * Fractal object (of the father class) of dimension and length 1 will be returned
     */

    static Fractal* createFractal(int, int);
};

#endif //EX1_FRACTAL_H
