#include "GField.h"
#include "GFNumber.h"
#include <cassert>

/**
 * Default constructor
*/

GField::GField()
{
p = 2;
l = 1;
}

/**
* Constructor that receives a value and sets it
* as the field's char
*/

GField::GField(const long p1)
{
    //assert the p is an integer and a prime number
    assert(p1 == floor(p1));
    assert(isPrime(abs((int)p1)));

    p = abs((int)p1);
    l = 1;
}

/**
* Constructor that receives two values and sets them
* as the field's char and degree
*/

GField::GField(const long p1, const long l1)
{
    //assert the p is an integer and a
    // prime number and that l is a natural number
    assert(p1 == floor(p1) && isPrime(abs((int)p1)) &&
    l1 > 0 && l1 == floor(l1));

    p = abs((int)p1);
    l = l1;
}

/**
* A copy constructor for a GField type object
*/

GField::GField(const GField& g)
{
    *this = g;
}

/**
* A destructor for a GField obejct
*/

GField::~GField()
= default;

/**
* Getter for the char of the field
* @return The Field's char value
*/

long GField::getChar() const
{
    return p;
}

/**
* Getter for the degree of the field
* @return The Field's degree value
*/

long GField::getDegree() const
{
    return l;
}

/**
* Getter for the order of the field
* @return The Field's degree order
* (p to the power of l)
*/

long GField::getOrder() const
{
    return (long)pow((double)p, (double)l);
}

/**
* Function gets a number and determines
* if it is a prime number.
* @return true if prime number
*/

bool GField::isPrime(const long n)
{
    int num = abs((int)n);

    if(num < 2)
    {
        return false;
    }

    int i = 2;

    while(i <= floor(sqrt(num)))
    {
        if (num % i == 0)
        {
            //if a prime factor is found,
            // then the number is not prime
            return false;
        }
        i++;
    }

    return true;
}

/**
* Gets two numbers and returns the gcd
* @return gcd of the two numbers passed on to the
* function
*/

GFNumber GField::gcd(GFNumber& num1, GFNumber& num2) const
{
    assert(num1.getField() == num2.getField());

    int x = (int)num1.getNumber(), y = (int)num2.getNumber();

    GFNumber return_value = GFNumber(gcdHelper(x, y), num2.getField());

    return return_value;
}

/**
* Create a GFNumber object with this field and the given
* number
* @return Reference to the created GFNumber object
*/

GFNumber GField::createNumber(long n)
{
    GFNumber number = GFNumber(n, *this);
    return number;
}

/**
* Overload of the '==' operator
* @return true if object are equal, false otherwise
*/

bool GField::operator==(const GField& g) const
{
    return getOrder() == g.getOrder();
}

/**
* Overload of the '!=' operator
* @return true if object are not equal, false otherwise
*/

bool GField::operator!=(const GField& g) const
{
    return getOrder() != g.getOrder();
}

/**
* Overload of the assigment '=' operator
* @return Reference to the modified GField object
*/

GField& GField::operator=(const GField& g)
{
    p = g.p;
    l = g.l;
    return *this;
}

/**
* Overload of the c out '>>' operator
* @return Reference to the modified GField object
*/

ostream& operator<<(ostream& s, const GField& g)
{
    s << "GF(" << g.p << "**" << g.l << ")";
    return s;
}

/**
* Overload of the c out '<<' operator
* @return Reference to the modified GField object
*/

istream& operator>>(istream& s, const GField& g)
{
    s >> g.p >> g.l;
    return s;
}

/**
* A helper for the gcd function. Receives two long format numbers
* as oppose to GFNumber objects in the original function
* @return gcd of the two numbers
*/

long GField::gcdHelper(long x, long y)
{
    // In case one of the numbers is zero
    if (x == 0)
    {
        return y;
    }

    if (y == 0)
    {
        return x;
    }

    // base case
    if (x == y)
    {
        return x;
    }

    // if x is greater
    if (x > y)
        return gcdHelper(x - y, y);
    return gcdHelper(x, y - x);
}