#include <utility>
#include <numeric>
#include <stdexcept>

#include "Fraction.hpp"

// Конструктор по умолчанию
Fraction::Fraction(int num, int denom) : numerator(num), denominator(denom) {
    if(denom == 0){
        throw std::runtime_error("Denominator can not be 0 (zero divison)");
    }
}

// Конструктор копирования
Fraction::Fraction(const Fraction &other) : numerator(other.numerator), denominator(other.denominator) {}

// Конструктор перемещения
Fraction::Fraction(Fraction &&other) noexcept : numerator(0), denominator(1)
{
    std::swap(this->numerator, other.numerator);
    std::swap(this->denominator, other.denominator);
}

// Getters
int Fraction::getNumerator() const  
{
    return this->numerator;
}

int Fraction::getDenominator() const
{
    return this->denominator;
}

// Сокращение дроби
Fraction Fraction::simplify() const
{
    int divisor = std::gcd(this->numerator, this->denominator);
    return Fraction(this->numerator / divisor, this->denominator / divisor);
}

// Перегрузка унарных арифметических операторов
Fraction Fraction::operator-() const
{
    return Fraction(-(this->numerator), this->denominator);
}

// Перегрузка бинарных арифметических операторов
Fraction Fraction::operator+(const Fraction &other) const
{
    return Fraction(
        this->numerator * other.denominator + other.numerator * this->denominator, 
        this->denominator * other.denominator
        ).simplify();
}

Fraction Fraction::operator-(const Fraction &other) const
{
    return *this + -(other);
}

Fraction Fraction::operator*(const Fraction &other) const
{
    return Fraction(
        this->numerator * other.numerator,
        this->denominator * other.denominator
        ).simplify();
}

Fraction Fraction::operator/(const Fraction &other) const
{
    if(other.numerator == 0){
        throw std::runtime_error("Divisor's numerator can't be 0 (zero divison)");
    }

    return Fraction(
        this->numerator * other.denominator,
        this->denominator * other.numerator
        ).simplify();
}

// Перегрузка оператора ~
Fraction Fraction::operator~() const
{
    return Fraction(this->denominator, this->numerator); // Обратная дробь
}

// Перегрузка оператора присваивания
Fraction &Fraction::operator=(const Fraction &other)
{
    if (this != &other)
    {
        this->numerator = other.numerator;
        this->denominator = other.denominator;
    }
    return *this;
}

Fraction &Fraction::operator=(Fraction &&other) noexcept
{
    if (this != &other)
    {
        this->numerator = 0;
        this->denominator = 1;
        std::swap(this->numerator, other.numerator);
        std::swap(this->denominator, other.denominator);
    }
    return *this;
}

// Перегрузка операторов сравнения

bool Fraction::operator==(const Fraction &other)
{
    return this->numerator == other.numerator && this->denominator == other.denominator;
}

bool Fraction::operator<(const Fraction &other)
{
    return false;
}

// Дружественный оператор вывода
std::ostream &operator<<(std::ostream &out, const Fraction &rhs)
{
    out << rhs.numerator << "/" << rhs.denominator;
    return out;
}
