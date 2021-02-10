#ifndef EX1_GFNUMBER_H
#define EX1_GFNUMBER_H
#include "cmath"
#include <cassert>
#include "GField.h"
using std::cin;
using std::cout;

/**
 * Class for a GFNumber object
 */

class GFNumber
{
private:
    long n;
    GField g;

    /**
     * Adjust the given number it's corresponding
     * value in the given field (using modulo)
     */

    static long _adjustNumber(long&, const GField&);

    /**
     * A brute force algorithm to find the
     * prime factors of a given number
     * @param n The number
     * @return A pointer to the first index of
     * the array which hold the prime factors
     * of the given number as values
     */

    static int* _directSearchFactorization(int&);

    /**
     * A function that represents the
     * polynomial function x^2 +1
     * @param x The given value from the function domain
     * @return The corresponding value in the function's image
     */

    static long _f(long x, const GField g);

    /**
     * Implementation of the Rho algorithm
     * to find prime factors of a certain number.
     * @param n The given number.
     * @return a prime factor of the number is found, -1
     * otherwise
     */

    static long _rhoAlgorithm(const long, const GField);

public:
    /**
     * Default constructor
     */

    GFNumber();

    /**
     * Constructor that receives a number and sets
     * it as a number in the default field (Z2)
     */

    GFNumber(long);

    /**
     * Constructor that receives a number and a field
     * and sets the corresponding value of this number
     * in the given field as the number field of this object
     */

    GFNumber(long, GField&);

    /**
     * A copy constructor for a GFNumber type object
     */

    GFNumber(const GFNumber&);

    /**
     * A destructor for a GFNumber object
     */

    ~GFNumber();

    /**
     * Getter for the number of the object
     * @return The GFNumber's numeric value
     */

    long getNumber() const;

    /**
     * Getter for the GField of the object
     * @return The GFNumber's GField object (pointer)
     */

    GField& getField();

    /**
     * returns an array of the prime
     * factors of the object's numeric field. Also, sets
     * the size of the returned array as the value of the
     * pointer sent to the function
     */

    GFNumber* getPrimeFactors(int*);

    /**
     * prints the prime factors of the object's numeric field
     */

    void printFactors();

    /**
     * Method that checks if the object is a prime number
     * @return
     */

    bool getIsPrime() const;

    /**
     * Overload of the relational operator '=='
     * @return true if operator's condition
     * is fulfilled, false otherwise
     */

    bool operator==(const GFNumber&) const;

    /**
     * Overload of the relational operator '!='
     * @return true if operator's condition
     * is fulfilled, false otherwise
     */

    bool operator!=(const GFNumber&) const;

    /**
     * Overload of the relational operator '<'
     * @return true if operator's condition
     * is fulfilled, false otherwise
     */

    bool operator<(const GFNumber&) const;

    /**
     * Overload of the relational operator '<='
     * @return true if operator's condition
     * is fulfilled, false otherwise
     */

    bool operator<=(const GFNumber&) const;

    /**
     * Overload of the relational operator '>'
     * @return true if operator's condition
     * is fulfilled, false otherwise
     */

    bool operator>(const GFNumber&) const;

    /**
     * Overload of the relational operator '>='
     * @return true if operator's condition
     * is fulfilled, false otherwise
     */

    bool operator>=(const GFNumber&) const;

    /**
     * Overload of the arithmetic operators '+'
     * used with a number of type long
     * @return true if object are not equal, false otherwise
     */

    GFNumber operator+(const long);

    /**
     * Overload of the arithmetic operators '+='
     * used with a number of type long
     * @return true if object are not equal, false otherwise
     */

    GFNumber& operator+=(const long);

    /**
     * Overload of the arithmetic operators '-'
     * used with a number of type long
     * @return true if object are not equal, false otherwise
     */

    GFNumber operator-(const long);

    /**
     * Overload of the arithmetic operators '-='
     * used with a number of type long
     * @return true if object are not equal, false otherwise
     */

    GFNumber& operator-=(const long);

    /**
     * Overload of the arithmetic operators '*'
     * used with a number of type long
     * @return true if object are not equal, false otherwise
     */

    GFNumber operator*(const long);

    /**
     * Overload of the arithmetic operators '*='
     * used with a number of type long
     * @return true if object are not equal, false otherwise
     */

    GFNumber& operator*=(const long);

    /**
     * Overload of the arithmetic operators '%'
     * used with a number of type long
     * @return true if object are not equal, false otherwise
     */

    GFNumber operator%(const long);

    /**
     * Overload of the arithmetic operators '%='
     * used with a number of type long
     * @return true if object are not equal, false otherwise
     */

    GFNumber& operator%=(const long);

    /**
     * Overload of the arithmetic operators '+'
     * used with a number of type GFNumber
     * @return true if object are not equal, false otherwise
     */

    GFNumber operator+(const GFNumber&);

    /**
     * Overload of the arithmetic operators '+='
     * used with a number of type GFNumber
     * @return true if object are not equal, false otherwise
     */

    GFNumber& operator+=(const GFNumber&);

    /**
     * Overload of the arithmetic operators '-'
     * used with a number of type GFNumber
     * @return true if object are not equal, false otherwise
     */

    GFNumber operator-(const GFNumber&);

    /**
     * Overload of the arithmetic operators '-='
     * used with a number of type GFNumber
     * @return true if object are not equal, false otherwise
     */

    GFNumber& operator-=(const GFNumber&);

    /**
     * Overload of the arithmetic operators '*'
     * used with a number of type GFNumber
     * @return true if object are not equal, false otherwise
     */

    GFNumber operator*(const GFNumber&);

    /**
     * Overload of the arithmetic operators '*='
     * used with a number of type GFNumber
     * @return true if object are not equal, false otherwise
     */

    GFNumber& operator*=(const GFNumber&);

    /**
     * Overload of the arithmetic operators '%'
     * used with a number of type GFNumber
     * @return true if object are not equal, false otherwise
     */

    GFNumber operator%(const GFNumber&);

    /**
     * Overload of the arithmetic operators '%='
     * used with a number of type GFNumber
     * @return true if object are not equal, false otherwise
     */

    GFNumber& operator%=(const GFNumber&);

    /**
     * Overload of the assigment '=' operator
     * @return Reference to the modified GField object
     */

    GFNumber& operator=(const GFNumber&);

    /**
     * Overload of the c out '<<' operator
     * @return Reference to the modified GField object
     */

    friend std::ostream& operator<<(std::ostream&, const GFNumber&);

    /**
     * Overload of the c in '>>' operator
     * @return Reference to the modified GField object
     */

    friend std::istream& operator>>(std::istream&, GFNumber&);
};

#endif //EX1_GFNUMBER_H