#ifndef EX1_GFIELD_H
#define EX1_GFIELD_H
#include <iostream>
#include "random"
using std::ostream;
using std::istream;
//forward declaration
class GFNumber;

#ifndef EX1_GFIELD_H
#include "GFNumber.h"
#endif

class GField
{
private:
    long p, l;

public:
    /**
     * A helper for the gcd function. Receives two long format numbers
     * as oppose to GFNumber objects in the original function
     * @return gcd of the two numbers
     */

    static long gcdHelper(long, long);

    /**
     * Default constructor
     */

    GField();

    /**
     * Constructor that receives a value and sets it
     * as the field's char
     */

    GField(const long);

    /**
     * Constructor that receives two values and sets them
     * as the field's char and degree
     */

    GField(const long, const long);

    /**
     * A copy constructor for a GField type object
     */

    GField(const GField&);

    /**
     * A destructor for a GField obejct
     */

    ~GField();

    /**
     * Getter for the char of the field
     * @return The Field's char value
     */

    long getChar() const;

    /**
     * Getter for the degree of the field
     * @return The Field's degree value
     */

    long getDegree() const;

    /**
     * Getter for the order of the field
     * @return The Field's degree order
     * (p to the power of l)
     */

    long getOrder() const;

    /**
     * Function gets a number and determines
     * if it is a prime number.
     * @return true if prime number
     */

    static bool isPrime(const long);

    /**
     * Gets two numbers and returns the gcd
     * @return gcd of the two numbers passed on to the
     * function
     */

    GFNumber gcd(GFNumber&, GFNumber&) const;

    /**
     * Create a GFNumber object with this field and the given
     * number
     * @return Reference to the created GFNumber object
     */

    GFNumber createNumber(long);

    /**
     * Overload of the '==' operator
     * @return true if object are equal, false otherwise
     */

    bool operator==(const GField&) const;

    /**
     * Overload of the '!=' operator
     * @return true if object are not equal, false otherwise
     */

    bool operator!=(const GField&) const;

    /**
     * Overload of the assigment '=' operator
     * @return Reference to the modified GField object
     */

    GField& operator=(const GField&);

    /**
     * Overload of the c out '>>' operator
     * @return Reference to the modified GField object
     */

    friend ostream& operator<<(ostream&, const GField&);

    /**
     * Overload of the c out '<<' operator
     * @return Reference to the modified GField object
     */

    friend istream& operator>>(istream&, const GField&);
};

#endif //EX1_GFIELD_H