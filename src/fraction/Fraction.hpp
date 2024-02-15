#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>

class Fraction {
private:
    int numerator;
    int denominator;

public:
    // Конструктор по умолчанию
    Fraction(int num = 0, int denom = 1);

    // Конструктор копирования
    Fraction(const Fraction& other);

    // Конструктор перемещения
    Fraction(Fraction&& other) noexcept;

    // Getters
    int getNumerator() const;
    int getDenominator() const;

    // Сокращение дроби
    Fraction simplify() const;

    // Перегрузка унарных арифметических операторов
    Fraction operator-() const;

    // Перегрузка арифметических операторов
    Fraction operator+(const Fraction& other) const;
    Fraction operator-(const Fraction& other) const; 
    Fraction operator*(const Fraction& other) const;
    Fraction operator/(const Fraction& other) const;

    // Перегрузка оператора ~
    Fraction operator~() const;

    // Перегрузка оператора присваивания
    Fraction& operator=(const Fraction& other);
    Fraction& operator=(Fraction&& other) noexcept;

    // Перегрузка операторов сравнения
    bool operator==(const Fraction& other);
    bool operator<(const Fraction& other);

    // Дружественный оператор вывода
    friend std::ostream& operator<<(std::ostream& out, const Fraction& f);
};

#endif // FRACTION_H
