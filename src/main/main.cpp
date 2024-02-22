#include <iostream>
#include <stdexcept>
#include "../fraction/Fraction.hpp"

int main()
{
    try{
        Fraction f1(3, 5), f2(2, 5, true);

        // Проверка унарных арифметических операторов
        std::cout << "~(" << f1 << ") = " << ~f1 << "\n";
        std::cout << "-(" << f1 << ") = " << -f1 << "\n";
        std::cout << "\n";

        // Проверка бинарных арифметических операторов
        std::cout << f1 << " + " << f2 << " = " << f1 + f2 << "\n";
        std::cout << f1 << " - " << f2 << " = " << f1 - f2 << "\n";
        std::cout << f1 << " * " << f2 << " = " << f1 * f2 << "\n";
        std::cout << f1 << " / " << f2 << " = " << f1 / f2 << "\n";
        std::cout << "\n";

        // Проверка опрераторов сравнения
        std::cout << f1 << " < " << f2 << "   " << (f1 < f2 ? "true" : "false") << "\n";
        std::cout << f1 << " > " << f2 << "   " << (f1 > f2 ? "true" : "false") << "\n";
        std::cout << f1 << " == " << f2 << "  " << (f1 == f2 ? "true" : "false") << "\n";
        std::cout << f1 << " != " << f2 << "  " << (f1 != f2 ? "true" : "false") << "\n";
        std::cout << f1 << " <= " << f2 << "  " << (f1 <= f2 ? "true" : "false") << "\n";
        std::cout << f1 << " >= " << f2 << "  " << (f1 >= f2 ? "true" : "false") << "\n";
        std::cout << "\n";

        int64_t num = -2; 
        std::cout << f1 << " * " << num << " = " << f1 * num << "\n";


        // Fraction f0(3, 0); // throws std::runtime_error
    }
    catch(const std::runtime_error& re){
        std::cerr << "Exception caught: " << re.what() << "\n";
    }

    return 0;
}