#include <iostream>
#include <vector>
#include "src/fraction/Fraction.hpp"

int main()
{
    Fraction f1(3, 5), f2(2, 5);
    std::cout << f1 << " + " << f2 << " = " << f1 - f2 << "\n";

    return 0;
}