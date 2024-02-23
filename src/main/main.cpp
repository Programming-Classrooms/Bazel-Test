#include <iostream>
#include <stdexcept>
#include "../fraction/Fraction.hpp"

int main()
{
    try{
        Fraction f1(300, 5, false), f2(2, 5, true);

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
    }
    catch(const std::runtime_error& re){
        std::cerr << "Runtime error exception caught: " << re.what() << "\n";
    }
    catch(const std::invalid_argument& re){
        std::cerr << "Invalid argument exception caught: " << re.what() << "\n";
    }

    return 0;
}