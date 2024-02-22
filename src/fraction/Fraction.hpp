#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>

class Fraction {
private:
    uint64_t numerator; // Числитель
    uint64_t denominator; // Знаменатель
    bool negative; // Знак дроби (false = '+'  |  true = '-')

    // Сокращение дроби
    void reduce();
    
public:
    // Конструкторы
    Fraction();
    Fraction(const uint64_t& numeratorVal, const uint64_t& denominatorVal, const bool& negativeVal = false);
    Fraction(const Fraction& origin);
    Fraction(Fraction&& rhs) noexcept;
    explicit Fraction(const int64_t& intVal);
    ~Fraction();

    // Геттеры
    uint64_t getNum() const;
    uint64_t getDen() const;
    bool isNegative() const;

    // Сеттеры
    void setNum(const uint64_t& numVal);
    void setDen(const uint64_t& denVal);
    void setNegative(const bool& negativeVal);

    // Перегрузка унарных арифметических операторов
    Fraction operator++();
    Fraction operator++(int);
    Fraction operator--();
    Fraction operator--(int);
    Fraction operator-() const;
    Fraction operator~() const;

    // Перегрузка арифметических операторов
    Fraction operator+(const Fraction& rhs) const;
    Fraction operator-(const Fraction& rhs) const; 
    Fraction operator*(const Fraction& rhs) const;
    Fraction operator/(const Fraction& rhs) const;

    Fraction operator+(const int64_t& rhs) const;
    Fraction operator-(const int64_t& rhs) const;
    Fraction operator*(const int64_t& rhs) const;
    Fraction operator/(const int64_t& rhs) const;

    // double operator+(const double& rhs) const;
    // double operator-(const double& rhs) const;
    // double operator*(const double& rhs) const;
    // double operator/(const double& rhs) const;

    // friend Fraction operator+(const int64_t& lhs, const Fraction& rhs);
    // friend Fraction operator-(const int64_t& lhs, const Fraction& rhs);
    // friend Fraction operator*(const int64_t& lhs, const Fraction& rhs);
    // friend Fraction operator/(const int64_t& lhs, const Fraction& rhs);

    // Перегрузка оператора присваивания
    Fraction& operator=(const Fraction& rhs);
    Fraction& operator=(Fraction&& rhs) noexcept;

    Fraction& operator+=(const Fraction& rhs);
    Fraction& operator-=(const Fraction& rhs);
    Fraction& operator*=(const Fraction& rhs);
    Fraction& operator/=(const Fraction& rhs);

    // Fraction& operator+=(const int64_t& rhs);
    // Fraction& operator-=(const int64_t& rhs);
    // Fraction& operator*=(const int64_t& rhs);
    // Fraction& operator/=(const int64_t& rhs);

    // Перегрузки операторов сравнения
    bool operator==(const Fraction& rhs) const;
    bool operator!=(const Fraction& rhs) const;
    bool operator<(const Fraction& rhs) const;
    bool operator>(const Fraction& rhs) const;
    bool operator<=(const Fraction& rhs) const;
    bool operator>=(const Fraction& rhs) const;

    // Перегрузки операротов преобразования типов
    explicit operator std::string() const;
    explicit operator int64_t() const;
    explicit operator double() const;
    explicit operator float() const;

    // Дружественный оператор вывода
    friend std::ostream& operator<<(std::ostream& out, const Fraction& f);
};

#endif // FRACTION_H
