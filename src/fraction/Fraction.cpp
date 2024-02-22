#include <utility>
#include <numeric>
#include <stdexcept>
#include <sstream>

#include "Fraction.hpp"

/* ========================== Приватные методы =========================== */
/* ======================================================================= */

// Сокращение дроби (приватный метод)
void Fraction::reduce()
{
    uint64_t divisor = std::gcd(this->numerator, this->denominator); // <numeric>
    if(divisor != 1) {
        this->numerator /= divisor;
        this->denominator /= divisor;
    }
}

/* ======================================================================= */



/* ============================ Конструкторы ============================= */
/* ======================================================================= */

// Конструктор по умолчанию
Fraction::Fraction() :
    numerator(0),
    denominator(1),
    negative(false)
{}

// Конструктор c параметрами
Fraction::Fraction(const uint64_t& numeratorVal, const uint64_t& denominatorVal, const bool& negativeVal) {
    this->setNum(numeratorVal);
    this->setDen(denominatorVal);
    this->negative = negativeVal;

    this->reduce();
}

// Конструктор копирования
Fraction::Fraction(const Fraction &origin) : 
    numerator(origin.numerator),
    denominator(origin.denominator), 
    negative(origin.negative) 
{}

// Конструктор перемещения
Fraction::Fraction(Fraction &&origin) noexcept : numerator(0), denominator(1), negative(false)
{
    std::swap(this->numerator, origin.numerator);
    std::swap(this->denominator, origin.denominator);
    std::swap(this->negative, origin.negative);
}

// Конструктор преобразования int64_t
Fraction::Fraction(const int64_t& intVal) :
    numerator(std::abs(intVal)),
    denominator(1),
    negative(intVal < 0)
{}

// Деструктор
Fraction::~Fraction(){}


/* ======================================================================= */



/* ========================== Геттеры ==================================== */
/* ======================================================================= */

// Получение числителя
uint64_t Fraction::getNum() const  
{
    return this->numerator;
}

// Получение знаменателя
uint64_t Fraction::getDen() const
{
    return this->denominator;
}

// Получение знака дроби
bool Fraction::isNegative() const 
{
    return this->negative;
}

/* ======================================================================= */



/* =============================== Сеттеры =============================== */
/* ======================================================================= */

// Установка числителя
void Fraction::setNum(const uint64_t & numVal)
{
    this->numerator = numVal;
    this->reduce();
}

// Установка знаменателя
void Fraction::setDen(const uint64_t & denVal)
{
    if(denVal == 0){
        throw std::runtime_error("Denominator can not be 0 (zero divison)");
    }
    this->denominator = denVal;
    this->reduce();
}

// Установка знака дроби
void Fraction::setNegative(const bool& negativeVal) {
    this->negative = negativeVal;
}

/* ======================================================================== */



/* ============ Перегрузка унарных арифметических операторов ============== */
/* ======================================================================== */

// Префиксное инкрементирование [ дробь + 1 ]
Fraction Fraction::operator++()
{
    *this += Fraction(this->numerator, this->numerator, false);
    return *this;
}

// Постфиксное инкрементирование [ дробь + 1 ]
Fraction Fraction::operator++(int)
{
    Fraction tempFraction = *this;

    this->numerator += this->denominator;
    this->reduce();

    return tempFraction;
}

// Префиксное декрементирование [ дробь - 1 ]
Fraction Fraction::operator--()
{
    --(this->numerator);
    this->reduce();
    
    return *this;
}

// Постфиксное декрементирование [ дробь - 1 ]
Fraction Fraction::operator--(int)
{
    Fraction tempFraction = *this;

    --(this->numerator);
    this->reduce();

    return tempFraction;
}

// Нахождение дроби обратной по сложению
Fraction Fraction::operator-() const
{
    return Fraction(this->numerator, this->denominator, !(this->negative));
}

// Нахождение дроби обртаной по умножению
Fraction Fraction::operator~() const
{
    return Fraction(this->denominator, this->numerator);
}

/* ========================================================================= */



/* ============ Перегрузки бинарных арифметических операторов ============== */
/* ========================================================================= */

// Бинарное сложение   [ дробь + дробь ]
Fraction Fraction::operator+(const Fraction &rhs) const
{
    return Fraction(
        this->numerator * rhs.denominator + rhs.numerator * this->denominator * (this->negative == rhs.negative ? 1 : -1), 
        this->denominator * rhs.denominator,
        *this < rhs ? rhs.negative : this->negative );
}

// Бинарное вычитание   [ дробь + (-дробь) ]
Fraction Fraction::operator-(const Fraction &rhs) const
{
    return *this + -(rhs);
}

// Бинарное умножение   [ дробь * дробь ]
Fraction Fraction::operator*(const Fraction &rhs) const
{
    return Fraction(
        this->numerator * rhs.numerator,
        this->denominator * rhs.denominator,
        this->negative && rhs.negative
        );
}

// Бинарное деление   [ дробь * ~(дробь) ]
Fraction Fraction::operator/(const Fraction &rhs) const
{
    if(rhs.numerator == 0){
        throw std::runtime_error("Divisor's numerator can't be 0 (zero divison)");
    }

    return (*this) * (~rhs);
}

// Сложение с int64_t  [ дробь + число ]
Fraction Fraction::operator+(const int64_t& rhs) const {
    return *this + Fraction(rhs);
}

// Вычитание с int64_t  [ дробь - число ]
Fraction Fraction::operator-(const int64_t& rhs) const {
    return *this + Fraction(-rhs);
}

// Умножение с int64_t  [ дробь * число ]
Fraction Fraction::operator*(const int64_t& rhs) const {
    return *this * Fraction(rhs);
}

// Умножение с int64_t  [ дробь / число ]
Fraction Fraction::operator/(const int64_t& rhs) const {
    return *this / Fraction(-rhs);
}

/* ======================================================================== */



/* ================== Перегрузки операторов присваивания ================== */
/* ======================================================================== */

// Дефолтный оператор присваивания
Fraction& Fraction::operator=(const Fraction &rhs)
{
    if (this != &rhs)
    {
        this->numerator = rhs.numerator;
        this->denominator = rhs.denominator;
    }
    return *this;
}

// Оператор перемещения
Fraction& Fraction::operator=(Fraction &&rhs) noexcept
{
    if (this != &rhs)
    {
        this->numerator = 0;
        this->denominator = 1;
        std::swap(this->numerator, rhs.numerator);
        std::swap(this->denominator, rhs.denominator);
    }
    return *this;
}

// Оператор присваивания сложения
Fraction& Fraction::operator+=(const Fraction &rhs)
{
    *this = *this + rhs;
    return *this;
}

// Оператор присваивания вычитания
Fraction& Fraction::operator-=(const Fraction &rhs)
{
    *this = *this - rhs;
    return *this;
}

// Оператор присваивания умножения
Fraction& Fraction::operator*=(const Fraction &rhs)
{
    *this = *this * rhs;
    return *this;
}

// Оператор присваивания деления 
Fraction& Fraction::operator/=(const Fraction &rhs)
{
    *this = *this / rhs;
    return *this;
}

/* ======================================================================== */



/* ================== Перегрузки операторов сравнения ================== */
/* ===================================================================== */

// Оператор "равно"
bool Fraction::operator==(const Fraction &rhs) const
{
    return this->numerator == rhs.numerator && this->denominator == rhs.denominator;
}

// Оператор "неравно"
bool Fraction::operator!=(const Fraction& rhs) const
{
    return !(*this == rhs);
}

// Оператор "меньше"
bool Fraction::operator<(const Fraction &rhs) const
{
    return this->numerator * rhs.denominator < rhs.numerator * this->denominator;
}

// Оператор "больше"
bool Fraction::operator>(const Fraction &rhs) const
{
    return *this < rhs || *this == rhs;
}

// Оператор "меньше или равно"
bool Fraction::operator<=(const Fraction& rhs) const
{
    return !(*this > rhs);
}

// Оператор "больше или равно"
bool Fraction::operator>=(const Fraction& rhs) const
{
    return !(*this < rhs);
}

/* ======================================================================== */



/* ================= Перегрузки операторов преобразования ================= */
/* ======================================================================== */

// Преобразование к std::string
Fraction::operator std::string() const
{
    std::stringstream ss;
    ss << (this->negative ? "-" : "") << this->numerator << "/" << this->denominator;
    return ss.str();
}

// Преобразование к double
Fraction::operator double() const
{
    return (static_cast<double>(this->numerator) / this->denominator) * (this->negative ? -1 : 1);
}

// Преобразование к float
Fraction::operator float() const
{
    return (static_cast<float>(this->numerator) / this->denominator) * (this->negative ? -1 : 1);
}

// Преобразование к int64_t
Fraction::operator int64_t() const
{
    return static_cast<int64_t>(this->numerator / this->denominator) * (this->negative ? -1 : 1);
}

/* ======================================================================== */



/* =============== Перегрузки дружественных операторов ==================== */
/* ======================================================================== */

// Оператор вывода (дружественный)
std::ostream &operator<<(std::ostream &out, const Fraction &rhs)
{
    out << std::string(rhs);
    return out;
}

/* ======================================================================= */
