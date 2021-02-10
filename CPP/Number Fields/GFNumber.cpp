#include "GFNumber.h"
class GField;

/**
 * Class for a GFNumber object
 */

GFNumber::GFNumber()
{
    n = 0;
    GField field = GField(2, 1);
    g = field;
}

/**
     * Constructor that receives a number and sets
     * it as a number in the default field (Z2)
     */

GFNumber::GFNumber(long num)
{
    GField field = GField(2, 1);
    g = field;

    //assert that the number is whole
    assert(num == floor(num));

    //check that number is within field bounds.
    // If not, calculate the appropriate modulo value
    //adjust the number to the field (with modulo)
    _adjustNumber(num, g);
    n = num;
}

/**
* Constructor that receives a number and a field
* and sets the corresponding value of this number
* in the given field as the number field of this object
*/

GFNumber::GFNumber(long num, GField& field)
{
    g = field;

    //assert that the number is whole
    assert(num == floor(num));

    //check that number is within field bounds.
    // If not, calculate the appropriate modulo value
    _adjustNumber(num, g);
    n = num;
}

/**
* A copy constructor for a GFNumber type object
*/

GFNumber::GFNumber(const GFNumber& number)
{
    *this = number;
}

/**
 * A destructor for a GFNumber object
 */

GFNumber::~GFNumber()
= default;

/**
* Getter for the number of the object
* @return The GFNumber's numeric value
*/

long GFNumber::getNumber() const
{
    return n;
}

/**
* Getter for the GField of the object
* @return The GFNumber's GField object (pointer)
*/

GField& GFNumber::getField()
{
    return g;
}

/**
* returns an array of the prime
* factors of the object's numeric field. Also, sets
* the size of the returned array as the value of the
* pointer sent to the function
*/

GFNumber* GFNumber::getPrimeFactors(int* NumFactors)
{
    int value = (int)n, factor, index = 0;
    GFNumber* factors = new GFNumber[1];

    if(value == 1 || value == 0)
    {
        GFNumber *temp = new GFNumber[2];
        temp[0] = GFNumber(value, g);
        temp[1] = GFNumber(1, g);
        delete[] factors;
        factors = temp;
        *NumFactors = 0;

        return factors;
    }

    //in case number is prime
    if(getIsPrime())
    {
        GFNumber *temp = new GFNumber[2];
        temp[0] = GFNumber(1, g);
        temp[1] = *this;
        delete[] factors;
        factors = temp;
        *NumFactors = 0;

        return factors;
    }

    //initiate rho algorithm
    int totalValue = 1;
    while(value > 1)
    {
        factor = _rhoAlgorithm(value, g);
        if(factor == -1)
        {
            //in case rho algorithm failed, break
            break;
        }

        if (index == 0) {
            factors[index] = GFNumber(factor, g);
            index++;
            value /= floor(factor);
            totalValue *= factor;
            continue;
        }

        //resize the factors array
        GFNumber *temp = new GFNumber[index + 1];
        for (int j = 0; j < index; j++) {
            temp[j] = factors[j];
        }

        delete[] factors;
        factors = temp;
        factors[index] = GFNumber(factor, g);
        totalValue *= factor;
        index++;
        value /= floor(factor);
    }

    if(totalValue == n)
    {
        //if rho found all of the number's prime factors
        return factors;
    }

    //if rho algorithm failed, use the direct trail division algorithm
    delete[] factors;
    value = (int)n;
    int* factorsInteger = _directSearchFactorization(value);
    *NumFactors = value;
    factors = new GFNumber[*NumFactors];

    for(int i = 0; i < *NumFactors; i++)
    {
        //for each value in the returned int array,
        // create a corresponding GFNumber object
        factors[i] = GFNumber(factorsInteger[i], g);
    }

    delete[] factorsInteger;
    return factors;
}

/**
* prints the prime factors of the object's numeric field
*/

void GFNumber::printFactors()
{
    cout << n << "=";

    int size;
    GFNumber* factors = getPrimeFactors(&size);

    //if pointer value is 0, we wold want to iterate over 2
    // numeric values (cases where number is prime, 0 or 1)
    if(size == 0)
    {
        size = 2;
    }

    for(int i = 0; i < size - 1; i++)
    {
        cout << factors[i].getNumber()<<"*";
    }

    //print last number in the array with end line
    cout << factors[size-1].getNumber() << std::endl;

    delete [] factors;
}

/**
* Method that checks if the object is a prime number
* @return
*/

bool GFNumber::getIsPrime() const {
    return GField::isPrime(n);
}

/**
* Overload of the relational operators
* @return true if operator's condition
* is fulfilled, false otherwise
*/

bool GFNumber::operator==(const GFNumber& gfn) const
{
    return (n == gfn.n && g == gfn.g);
}

/**
* Overload of the relational operator '!='
* @return true if operator's condition
* is fulfilled, false otherwise
*/

bool GFNumber::operator!=(const GFNumber& gfn) const
{
    return (n != gfn.n || g != gfn.g);
}

/**
* Overload of the relational operator '<'
* @return true if operator's condition
* is fulfilled, false otherwise
*/

bool GFNumber::operator<(const GFNumber& gfn) const
{
    //asserts that number field are equal
    assert(g == gfn.g);

    return (n < gfn.n);
}

/**
* Overload of the relational operator '<='
* @return true if operator's condition
* is fulfilled, false otherwise
*/

bool GFNumber::operator<=(const GFNumber& gfn) const
{
    //asserts that number field are equal
    assert(g == gfn.g);

    return (n <= gfn.n);
}

/**
* Overload of the relational operator '>'
* @return true if operator's condition
* is fulfilled, false otherwise
*/

bool GFNumber::operator>(const GFNumber& gfn) const
{
    //asserts that number field are equal
    assert(g == gfn.g);

    return (n > gfn.n);
}

/**
* Overload of the relational operator '>='
* @return true if operator's condition
* is fulfilled, false otherwise
*/

bool GFNumber::operator>=(const GFNumber& gfn) const
{
    //asserts that number field are equal
    assert(g == gfn.g);

    return (n >= gfn.n);
}

/**
* Overload of the arithmetic operators '+'
* used with a number of type GFNumber
* @return true if object are not equal, false otherwise
*/

GFNumber GFNumber::operator+(const GFNumber& gfn)
{
    //asserts that number field are equal
    assert(g == gfn.g);

    GFNumber temp = GFNumber(n + gfn.n, g);
    return temp;
}

/**
* Overload of the arithmetic operators '+'
* used with a number of type long
* @return true if object are not equal, false otherwise
*/

GFNumber GFNumber::operator+(long num)
{
    //assert that num is a whole number
    assert(num == floor(num));
    _adjustNumber(num, g);

    GFNumber temp = GFNumber(n + num, g);
    return temp;
}

/**
* Overload of the arithmetic operators '+='
* used with a number of type GFNumber
* @return true if object are not equal, false otherwise
*/

GFNumber& GFNumber::operator+=(const GFNumber& gfn)
{
    //asserts that number field are equal
    assert(g == gfn.g);

    //adjust the number to the field (with modulo)
    long value = n + gfn.n;
    _adjustNumber(value, g);

    n = value;

    return *this;
}

/**
* Overload of the arithmetic operators '+='
* used with a number of type long
* @return true if object are not equal, false otherwise
*/

GFNumber& GFNumber::operator+=(long num)
{
    //assert that num is a whole number
    // and adjust it to the current field
    assert(num == floor(num));
    _adjustNumber(num, g);

    //adjust the number to the field (with modulo)
    long value = n + num;
    _adjustNumber(value, g);

    n = value;

    return *this;
}

/**
* Overload of the arithmetic operators '-'
* used with a number of type GFNumber
* @return true if object are not equal, false otherwise
*/

GFNumber GFNumber::operator-(const GFNumber& gfn)
{
    //asserts that number field are equal
    assert(g == gfn.g);

    GFNumber temp = GFNumber(n - gfn.n, g);
    return temp;
}

/**
* Overload of the arithmetic operators '-'
* used with a number of type long
* @return true if object are not equal, false otherwise
*/

GFNumber GFNumber::operator-(const long num)
{
    //assert that num is a whole number
    assert(num == floor(num));

    GFNumber temp = GFNumber(n - num, g);
    return temp;
}

/**
* Overload of the arithmetic operators '-='
* used with a number of type GFNumber
* @return true if object are not equal, false otherwise
*/

GFNumber& GFNumber::operator-=(const GFNumber& gfn)
{
    //asserts that number field are equal
    assert(g == gfn.g);

    //adjust the number to the field (with modulo)
    long value = n - gfn.n;
    _adjustNumber(value, g);

    n = value;

    return *this;
}

/**
* Overload of the arithmetic operators '-='
* used with a number of type long
* @return true if object are not equal, false otherwise
*/

GFNumber& GFNumber::operator-=(long num)
{
    //assert that num is a whole number
    // and adjust it to the current field
    assert(num == floor(num));
    _adjustNumber(num, g);

    //adjust the number to the field (with modulo)
    long value = n - num;
    _adjustNumber(value, g);

    n = value;

    return *this;
}

/**
* Overload of the arithmetic operators '*'
* used with a number of type GFNumber
* @return true if object are not equal, false otherwise
*/

GFNumber GFNumber::operator*(const GFNumber& gfn)
{
    //asserts that number field are equal
    assert(g == gfn.g);

    GFNumber temp = GFNumber(n * gfn.n, g);
    return temp;
}

/**
* Overload of the arithmetic operators '*'
* used with a number of type long
* @return true if object are not equal, false otherwise
*/

GFNumber GFNumber::operator*(const long num)
{
    //assert that num is a whole number
    assert(num == floor(num));

    GFNumber temp = GFNumber(n * num, g);
    return temp;
}

/**
* Overload of the arithmetic operators '*='
* used with a number of type GFNumber
* @return true if object are not equal, false otherwise
*/

GFNumber& GFNumber::operator*=(const GFNumber& gfn)
{
    //asserts that number field are equal
    assert(g == gfn.g);

    //adjust the number to the field (with modulo)
    long value = n * gfn.n;
    _adjustNumber(value, g);

    n = value;

    return *this;
}

/**
* Overload of the arithmetic operators '*='
* used with a number of type long
* @return true if object are not equal, false otherwise
*/

GFNumber& GFNumber::operator*=(long num)
{
    //assert that num is a whole number
    // and adjust it to the current field
    assert(num == floor(num));
    _adjustNumber(num, g);

    //adjust the number to the field (with modulo)
    long value = n * num;
    _adjustNumber(value, g);

    n = value;

    return *this;
}

/**
* Overload of the arithmetic operators '%'
* used with a number of type GFNumber
* @return true if object are not equal, false otherwise
*/

GFNumber GFNumber::operator%(const GFNumber& gfn)
{
    //asserts that number field are equal
    assert(g == gfn.g);

    GFNumber temp = GFNumber(n % gfn.n, g);
    return temp;
}

/**
* Overload of the arithmetic operators '%'
* used with a number of type long
* @return true if object are not equal, false otherwise
*/

GFNumber GFNumber::operator%(const long num)
{
    //assert that num is a whole number
    assert(num == floor(num));

    GFNumber temp = GFNumber(n % num, g);
    return temp;
}

/**
* Overload of the arithmetic operators '%='
* used with a number of type long
* @return true if object are not equal, false otherwise
*/

GFNumber& GFNumber::operator%=(const GFNumber& gfn)
{
    //asserts that number field are equal
    assert(g == gfn.g);

    //adjust the number to the field (with modulo)
    long value = n % gfn.n;
    _adjustNumber(value, g);

    n = value;

    return *this;
}

/**
* Overload of the arithmetic operators '%='
* used with a number of type long
* @return true if object are not equal, false otherwise
*/

GFNumber& GFNumber::operator%=(long num)
{
    //assert that num is a whole number
    // and adjust it to the current field
    assert(num == floor(num));
    _adjustNumber(num, g);

    //adjust the number to the field (with modulo)
    long value = n % num;
    _adjustNumber(value, g);

    n = value;

    return *this;
}

/**
* Overload of the assigment '=' operator
* @return Reference to the modified GField object
*/

GFNumber& GFNumber::operator=(const GFNumber& num)
{
    n = num.n;
    g = num.g;
    return *this;
}

/**
* Overload of the c out '<<' operator
* @return Reference to the modified GField object
*/

ostream& operator<<(ostream& s, const GFNumber& num)
{
    s << num.n << " " << (num.g);
    return s;
}

/**
* Overload of the c in '>>' operator
* @return Reference to the modified GField object
*/

istream& operator>>(istream& s, GFNumber& num)
{
    long n, p, l;

    //assert that input consists of long characters
    s >> n;
    assert(!s.fail());
    s >> p;
    assert(!s.fail());
    s >> l;
    assert(!s.fail());

    //initialize a GFNumber and GField objects with
    // the given values to ensure their validity and
    // to adjust number to modulo (if necessary)
    GField g = GField(p, l);
    num = GFNumber(n, g);

    return s;
}

/**
* Implementation of the Rho algorithm
* to find prime factors of a certain number.
* @param n The given number.
* @return a prime factor of the number is found, -1
* otherwise
*/

long GFNumber::_rhoAlgorithm(const long n, const GField g)
{
    //set x's numeric value as a random value between the given
    // bounds (n-1 and 1)
    long x = ((std::rand() % (n - 1)) + 1), y = 0, p = 1;

    while(p == 1)
    {
        x = _f(x, g);
        y = _f(_f(x, g), g);
        p = GField::gcdHelper((long)abs((int)(x - y)), n);
    }

    if(p == n)
    {
        return -1;
    }

    return p;
}

/**
* A brute force algorithm to find the
* prime factors of a given number
* @param n The number
* @return A pointer to the first index of
* the array which hold the prime factors
* of the given number as values
*/

int* GFNumber::_directSearchFactorization(int& n)
{
    int value = n, i = 2, index = 0;
    int* factors = new int[1];

    while(i <= floor(sqrt(value)))
    {
        if (value % i == 0) {
            if (index == 0) {
                factors[index] = i;
                index++;
                value /= floor(i);
                continue;
            }

            //resize the factors array
            int *temp = new int[index + 1];
            for (int j = 0; j < index; j++) {
                temp[j] = factors[j];
            }

            delete[] factors;
            factors = temp;
            factors[index] = i;
            index++;
            value /= floor(i);
        }
        else
        {
            i += 1;
        }
    }

    if(value > 1)
    {
        factors[index] = value;
        index++;
    }
    //set original pointer value to the size
    //of the factors array.
    n = index;

    return factors;
}

/**
* Adjust the given number it's corresponding
* value in the given field (using modulo)
*/

long GFNumber::_adjustNumber(long& n, const GField& g)
{
    if(n >= g.getOrder())
    {
        n = n %  g.getOrder();
    }
    else if(n < 0)
    {
        n = (n % g.getOrder() + g.getOrder()) % g.getOrder();
    }

    return n;
}

/**
* A function that represents the
* polynomial function x^2 +1
* @param x The given value from the function domain
* @return The corresponding value in the function's image
*/

long GFNumber::_f(long x, const GField g)
{
    long value = (long)pow(x, 2);
    _adjustNumber(value, g);
    value += 1;

    return _adjustNumber(value, g);
}