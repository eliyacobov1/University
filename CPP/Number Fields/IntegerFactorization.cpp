#include "GField.h"
#include "GFNumber.h"

/**
 * main program. Gets the field of 2 GFNumers from the user and
 * prints their sum, subtraction, multiplication and prime factors
 */

int main()
{
    GFNumber a, b;

    cin >> a >> b;

    cout << a + b << "\n" << a - b << "\n" << b - a << "\n" << a * b << "\n";
    a.printFactors();
    b.printFactors();
}

