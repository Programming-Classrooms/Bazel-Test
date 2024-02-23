#include "../fraction/Fraction.hpp"
#include <stdexcept>
#include <gtest/gtest.h>


TEST(FractionConstructor, DefaultConstructor) {
    Fraction f;
    EXPECT_EQ(f.getNum(), 0);
    EXPECT_EQ(f.getDen(), 1);
    EXPECT_FALSE(f.isNegative());
}

TEST(FractionConstructor, ParameterizedConstructor) {
    Fraction f1(1, 2, false);
    EXPECT_EQ(f1.getNum(), 1);
    EXPECT_EQ(f1.getDen(), 2);
    EXPECT_FALSE(f1.isNegative());

    Fraction f2(2, 4, true);
    EXPECT_EQ(f2.getNum(), 1); // Проверяем сокращение дроби
    EXPECT_EQ(f2.getDen(), 2);
    EXPECT_TRUE(f2.isNegative());

    Fraction f3(0, 1, true);
    EXPECT_EQ(f3.getNum(), 0);
    EXPECT_EQ(f3.getDen(), 1);
    EXPECT_FALSE(f3.isNegative()); // Отрицательный ноль не имеет смысла

    Fraction f4(6, 3, false);
    EXPECT_EQ(f4.getNum(), 2);
    EXPECT_EQ(f4.getDen(), 1);
    EXPECT_FALSE(f4.isNegative());

    Fraction f5(10, 5, true);
    EXPECT_EQ(f5.getNum(), 2);
    EXPECT_EQ(f5.getDen(), 1);
    EXPECT_TRUE(f5.isNegative());
}

TEST(FractionConstructor, DenominatorZero) {
    EXPECT_THROW(Fraction(1, 0), std::invalid_argument);
}

TEST(FractionConversion, ToString) {
    EXPECT_EQ(static_cast<std::string>(Fraction(1, 2, false)), "1/2");
    EXPECT_EQ(static_cast<std::string>(Fraction(3, 4, true)), "-3/4");
    EXPECT_EQ(static_cast<std::string>(Fraction(2, 1, false)), "2");
    EXPECT_EQ(static_cast<std::string>(Fraction(0, 1, false)), "0");
    EXPECT_EQ(static_cast<std::string>(Fraction(100, 200, false)), "1/2");
}

TEST(FractionConversion, ToInt64) {
    EXPECT_EQ(static_cast<int64_t>(Fraction(2, 1, false)), 2);
    EXPECT_EQ(static_cast<int64_t>(Fraction(3, 2, false)), 1); // Округление вниз
    EXPECT_EQ(static_cast<int64_t>(Fraction(3, 2, true)), -1); // Округление вниз для отрицательных
    EXPECT_EQ(static_cast<int64_t>(Fraction(0, 1, false)), 0);
    EXPECT_EQ(static_cast<int64_t>(Fraction(10, 5, false)), 2);
}

TEST(FractionConversion, ToDouble) {
    EXPECT_DOUBLE_EQ(static_cast<double>(Fraction(1, 2, false)), 0.5);
    EXPECT_DOUBLE_EQ(static_cast<double>(Fraction(1, 3, false)), 1.0/3.0);
    EXPECT_DOUBLE_EQ(static_cast<double>(Fraction(1, 4, true)), -0.25);
    EXPECT_DOUBLE_EQ(static_cast<double>(Fraction(0, 1, false)), 0.0);
    EXPECT_DOUBLE_EQ(static_cast<double>(Fraction(2, 1, false)), 2.0);
}

TEST(FractionConversion, ToFloat) {
    EXPECT_FLOAT_EQ(static_cast<float>(Fraction(1, 2, false)), 0.5f);
    EXPECT_FLOAT_EQ(static_cast<float>(Fraction(1, 3, false)), 1.0f/3.0f);
    EXPECT_FLOAT_EQ(static_cast<float>(Fraction(1, 4, true)), -0.25f);
    EXPECT_FLOAT_EQ(static_cast<float>(Fraction(0, 1, false)), 0.0f);
    EXPECT_FLOAT_EQ(static_cast<float>(Fraction(2, 1, false)), 2.0f);
}

TEST(FractionUnaryOperators, PrefixIncrement) {
    Fraction f1(1, 2, false);
    auto& ref = ++f1;
    EXPECT_EQ(f1.getNum(), 3);
    EXPECT_EQ(f1.getDen(), 2);
    EXPECT_EQ(&ref, &f1); // Проверка, что возвращается ссылка на тот же объект

    Fraction f2(3, 3, false);
    ++f2;
    EXPECT_EQ(f2.getNum(), 2);
    EXPECT_EQ(f2.getDen(), 1);

    Fraction f3(0, 1, false);
    ++f3;
    EXPECT_EQ(f3.getNum(), 1);
    EXPECT_EQ(f3.getDen(), 1);

    Fraction f4(1, 2, true); // Отрицательная дробь
    ++f4;
    EXPECT_EQ(f4.getNum(), 1);
    EXPECT_EQ(f4.getDen(), 2);
    EXPECT_FALSE(f4.isNegative());

    Fraction f5(1, 1, false);
    ++f5;
    EXPECT_EQ(f5.getNum(), 2);
    EXPECT_EQ(f5.getDen(), 1);
}

TEST(FractionUnaryOperators, PostfixIncrement) {
    Fraction f1(1, 2, false);
    Fraction result1 = f1++;
    EXPECT_EQ(f1.getNum(), 3);
    EXPECT_EQ(f1.getDen(), 2);
    EXPECT_EQ(result1.getNum(), 1); 
    EXPECT_EQ(result1.getDen(), 2);

    Fraction f2(3, 3, false);
    Fraction result2 = f2++;
    EXPECT_EQ(f2.getNum(), 2);
    EXPECT_EQ(f2.getDen(), 1);
    EXPECT_EQ(result2.getNum(), 1); 
    EXPECT_EQ(result2.getDen(), 1);

    Fraction f3(0, 1, false);
    Fraction result3 = f3++;
    EXPECT_EQ(f3.getNum(), 1);
    EXPECT_EQ(f3.getDen(), 1);
    EXPECT_EQ(result3.getNum(), 0); 
    EXPECT_EQ(result3.getDen(), 1);

    Fraction f4(13, 13, false);
    Fraction result4 = f4++;
    EXPECT_EQ(f4.getNum(), 2);
    EXPECT_EQ(f4.getDen(), 1);
    EXPECT_EQ(result4.getNum(), 1); 
    EXPECT_EQ(result4.getDen(), 1);

    Fraction f5(2, 4, true);
    Fraction result5 = f5++;
    EXPECT_EQ(f5.getNum(), 1);
    EXPECT_EQ(f5.getDen(), 2);
    EXPECT_FALSE(f5.isNegative());
    EXPECT_EQ(result5.getNum(), 1); 
    EXPECT_EQ(result5.getDen(), 2);
    EXPECT_TRUE(result5.isNegative());
}

TEST(FractionUnaryOperators, PrefixDecrement) {
    Fraction f1(3, 2, false);
    --f1;
    EXPECT_EQ(f1.getNum(), 1);
    EXPECT_EQ(f1.getDen(), 2);

    Fraction f2(1, 1, false);
    --f2;
    EXPECT_EQ(f2.getNum(), 0);
    EXPECT_EQ(f2.getDen(), 1);
    EXPECT_FALSE(f2.isNegative());

    // Дополнительные случаи аналогичны
}

TEST(FractionUnaryOperators, PostfixDecrement) {
    Fraction f1(3, 2, false);
    Fraction result = f1--;
    EXPECT_EQ(f1.getNum(), 1);
    EXPECT_EQ(f1.getDen(), 2);
    EXPECT_EQ(result.getNum(), 3); 
    EXPECT_EQ(result.getDen(), 2);

    // Дополнительные случаи аналогичны префиксному декременту, но с проверкой возвращаемого значения
}

TEST(FractionUnaryOperators, UnaryMinus) {
    Fraction f1(1, 2, false);
    Fraction result = -f1;
    EXPECT_TRUE(result.isNegative());
    EXPECT_EQ(result.getNum(), 1);
    EXPECT_EQ(result.getDen(), 2);

    // Дополнительные случаи проверяют работу оператора с отрицательными и положительными дробями, а также с нулем
}

TEST(FractionUnaryOperators, TildeOperator) {
    Fraction f1(1, 2, false);
    Fraction result = ~f1;
    EXPECT_EQ(result.getNum(), 2);
    EXPECT_EQ(result.getDen(), 1);

    Fraction f2(3, 4, false);
    result = ~f2;
    EXPECT_EQ(result.getNum(), 4);
    EXPECT_EQ(result.getDen(), 3);

    // Дополнительные случаи для проверки обратных дробей, включая отрицательные значения и единицу
}

// Тестирование оператора сложения
TEST(FractionArithmetic, Addition1) {
    Fraction f1(1, 2);
    Fraction f2(1, 3);

    Fraction result = f1 + f2;
    EXPECT_EQ(result.getNum(), 5);
    EXPECT_EQ(result.getDen(), 6);

    // Добавление отрицательной дроби
    Fraction f3(-1, 4);
    result = f1 + f3;
    EXPECT_EQ(result.getNum(), 1); // 1/4
    EXPECT_EQ(result.getDen(), 4);

    // Добавление целого числа
    result = f1 + (int64_t)1;
    EXPECT_EQ(result.getNum(), 3);
    EXPECT_EQ(result.getDen(), 2);

    // Сложение с нулем
    result = f1 + (int64_t)0;
    EXPECT_EQ(result.getNum(), 1);
    EXPECT_EQ(result.getDen(), 2);

    // Сложение с самим собой
    result = f1 + f1;
    EXPECT_EQ(result.getNum(), 1);
    EXPECT_EQ(result.getDen(), 1);
}

TEST(FractionArithmetic, Addition2) {
    Fraction f1(1, 2, false);
    Fraction f2(1, 2, false);
    Fraction result = f1 + f2;
    EXPECT_EQ(result.getNum(), 1);
    EXPECT_EQ(result.getDen(), 1);

    Fraction f3(1, 3, false);
    result = f1 + f3;
    EXPECT_EQ(result.getNum(), 5);
    EXPECT_EQ(result.getDen(), 6);

    Fraction f4(1, 4, true);
    result = f1 + f4;
    EXPECT_EQ(result.getNum(), 1);
    EXPECT_EQ(result.getDen(), 4);

    Fraction f5(3, 4, false);
    result = f4 + f5;
    EXPECT_EQ(result.getNum(), 1);
    EXPECT_EQ(result.getDen(), 2);

    Fraction f6(1, 4, false);
    result = f4 + f6;
    EXPECT_EQ(result.getNum(), 0);
    EXPECT_EQ(result.getDen(), 1);
}

TEST(FractionBinaryOperators, Subtraction) {
    Fraction f1(3, 4, false);
    Fraction f2(1, 4, false);
    Fraction result = f1 - f2;
    EXPECT_EQ(result.getNum(), 1);
    EXPECT_EQ(result.getDen(), 2);

    Fraction f3(1, 2, false);
    result = f2 - f3;
    EXPECT_EQ(result.getNum(), 1);
    EXPECT_EQ(result.getDen(), 4);
    EXPECT_TRUE(result.isNegative());

    Fraction f4(1, 8, true);
    result = f2 - f4;
    EXPECT_EQ(result.getNum(), 3);
    EXPECT_EQ(result.getDen(), 8);

    Fraction f5(1, 2, true);
    result = f1 - f5;
    EXPECT_EQ(result.getNum(), 5);
    EXPECT_EQ(result.getDen(), 4);

    Fraction f6(0, 1, false);
    result = f6 - f1;
    EXPECT_EQ(result.getNum(), 3);
    EXPECT_EQ(result.getDen(), 4);
    EXPECT_TRUE(result.isNegative());
}

TEST(FractionBinaryOperators, Multiplication) {
    Fraction f1(1, 2, false);
    Fraction f2(2, 3, false);
    Fraction result = f1 * f2;
    EXPECT_EQ(result.getNum(), 1);
    EXPECT_EQ(result.getDen(), 3);

    Fraction f3(3, 4, false);
    result = f1 * f3;
    EXPECT_EQ(result.getNum(), 3);
    EXPECT_EQ(result.getDen(), 8);

    Fraction f4(1, 4, true);
    result = f1 * f4;
    EXPECT_TRUE(result.isNegative());
    EXPECT_EQ(result.getNum(), 1);
    EXPECT_EQ(result.getDen(), 8);

    Fraction f5(0, 1, false);
    result = f1 * f5;
    EXPECT_EQ(result.getNum(), 0);
    EXPECT_EQ(result.getDen(), 1);

    Fraction f6(1, 1, false);
    result = f4 * f6;
    EXPECT_TRUE(result.isNegative());
    EXPECT_EQ(result.getNum(), 1);
    EXPECT_EQ(result.getDen(), 4);
}

TEST(FractionBinaryOperators, Division) {
    Fraction f1(1, 2, false);
    Fraction f2(1, 3, false);
    Fraction result = f1 / f2;
    EXPECT_EQ(result.getNum(), 3);
    EXPECT_EQ(result.getDen(), 2);

    Fraction f3(3, 4, false);
    result = f1 / f3;
    EXPECT_EQ(result.getNum(), 2);
    EXPECT_EQ(result.getDen(), 3);

    Fraction f4(1, 4, true);
    result = f1 / f4;
    EXPECT_TRUE(result.isNegative());
    EXPECT_EQ(result.getNum(), 2);
    EXPECT_EQ(result.getDen(), 1);

    Fraction f5(1, 1, false); // Деление на единицу
    result = f1 / f5;
    EXPECT_EQ(result.getNum(), 1);
    EXPECT_EQ(result.getDen(), 2);

    Fraction f6(0, 1, false); // Деление нуля
    result = f6 / f1;
    EXPECT_EQ(result.getNum(), 0);
    EXPECT_EQ(result.getDen(), 1);

    EXPECT_THROW(f5 / f6, std::runtime_error); // Деление на 0
}

TEST(FractionInt64BinaryOperators, Addition) {
    Fraction f1(1, 2, false);
    Fraction result = f1 + (int64_t)1;
    EXPECT_EQ(result.getNum(), 3);
    EXPECT_EQ(result.getDen(), 2);

    result = f1 + (int64_t)(-1);
    EXPECT_EQ(result.getNum(), 1);
    EXPECT_EQ(result.getDen(), 2);
    EXPECT_TRUE(result.isNegative());

    Fraction f2(3, 4, false);
    result = f2 + (int64_t)2;
    EXPECT_EQ(result.getNum(), 11);
    EXPECT_EQ(result.getDen(), 4);

    Fraction f3(0, 1, false);
    result = f3 + (int64_t)5;
    EXPECT_EQ(result.getNum(), 5);
    EXPECT_EQ(result.getDen(), 1);

    Fraction f4(1, 4, true);
    result = f4 + (int64_t)1;
    EXPECT_EQ(result.getNum(), 3);
    EXPECT_EQ(result.getDen(), 4);
    EXPECT_FALSE(result.isNegative());
}


TEST(FractionInt64BinaryOperators, Subtraction) {
    Fraction f1(3, 2, false);
    Fraction result = f1 - (int64_t)1;
    EXPECT_EQ(result.getNum(), 1);
    EXPECT_EQ(result.getDen(), 2);

    result = f1 - (int64_t)(-1);
    EXPECT_EQ(result.getNum(), 5);
    EXPECT_EQ(result.getDen(), 2);

    Fraction f2(1, 2, false);
    result = f2 - (int64_t)2;
    EXPECT_EQ(result.getNum(), 3);
    EXPECT_EQ(result.getDen(), 2);
    EXPECT_TRUE(result.isNegative());

    Fraction f3(5, 1, false);
    result = f3 - (int64_t)5;
    EXPECT_EQ(result.getNum(), 0);
    EXPECT_EQ(result.getDen(), 1);

    Fraction f4(1, 4, false);
    result = f4 + (int64_t)(-1);
    EXPECT_EQ(result.getNum(), 3);
    EXPECT_EQ(result.getDen(), 4);
    EXPECT_TRUE(result.isNegative());
}


TEST(FractionInt64BinaryOperators, Multiplication) {
    Fraction f1(1, 2, false);
    Fraction result = f1 * (int64_t)2;
    EXPECT_EQ(result.getNum(), 1);
    EXPECT_EQ(result.getDen(), 1);

    result = f1 * (int64_t)(-2);
    EXPECT_EQ(result.getNum(), 1);
    EXPECT_EQ(result.getDen(), 1);
    EXPECT_TRUE(result.isNegative());

    Fraction f2(3, 4, false);
    result = f2 * (int64_t)3;
    EXPECT_EQ(result.getNum(), 9);
    EXPECT_EQ(result.getDen(), 4);

    Fraction f3(0, 1, false);
    result = f3 * (int64_t)10;
    EXPECT_EQ(result.getNum(), 0);
    EXPECT_EQ(result.getDen(), 1);

    Fraction f4(2, 3, false);
    result = f4 * (int64_t)0;
    EXPECT_EQ(result.getNum(), 0);
    EXPECT_EQ(result.getDen(), 1);
}


TEST(FractionInt64BinaryOperators, Division) {
    Fraction f1(1, 2, false);
    Fraction result = f1 / (int64_t)2;
    EXPECT_EQ(result.getNum(), 1);
    EXPECT_EQ(result.getDen(), 4);

    result = f1 / (int64_t)(-2);
    EXPECT_EQ(result.getNum(), 1);
    EXPECT_EQ(result.getDen(), 4);
    EXPECT_TRUE(result.isNegative());

    Fraction f2(3, 4, false);
    result = f2 / (int64_t)3;
    EXPECT_EQ(result.getNum(), 1);
    EXPECT_EQ(result.getDen(), 4);

    Fraction f3(6, 1, false);
    result = f3 / (int64_t)2;
    EXPECT_EQ(result.getNum(), 3);
    EXPECT_EQ(result.getDen(), 1);

    Fraction f4(1, 4, true);
    result = f4 / (int64_t)(-1);
    EXPECT_EQ(result.getNum(), 1);
    EXPECT_EQ(result.getDen(), 4);
    EXPECT_FALSE(result.isNegative()); // Два отрицательных числа дают положительное
}



TEST(FractionIntBinaryOperators, Addition) {
    Fraction f1(1, 2, false);
    Fraction result = f1 + 1;
    EXPECT_EQ(result.getNum(), 3);
    EXPECT_EQ(result.getDen(), 2);

    result = f1 + (-1);
    EXPECT_EQ(result.getNum(), 1);
    EXPECT_EQ(result.getDen(), 2);
    EXPECT_TRUE(result.isNegative());

    Fraction f2(3, 4, false);
    result = f2 + 2;
    EXPECT_EQ(result.getNum(), 11);
    EXPECT_EQ(result.getDen(), 4);

    Fraction f3(0, 1, false);
    result = f3 + 5;
    EXPECT_EQ(result.getNum(), 5);
    EXPECT_EQ(result.getDen(), 1);

    Fraction f4(1, 4, true);
    result = f4 + 1;
    EXPECT_EQ(result.getNum(), 3);
    EXPECT_EQ(result.getDen(), 4);
    EXPECT_FALSE(result.isNegative());
}


TEST(FractionIntBinaryOperators, Subtraction) {
    Fraction f1(3, 2, false);
    Fraction result = f1 - 1;
    EXPECT_EQ(result.getNum(), 1);
    EXPECT_EQ(result.getDen(), 2);

    result = f1 - (-1);
    EXPECT_EQ(result.getNum(), 5);
    EXPECT_EQ(result.getDen(), 2);

    Fraction f2(1, 2, false);
    result = f2 - 2;
    EXPECT_EQ(result.getNum(), 3);
    EXPECT_EQ(result.getDen(), 2);
    EXPECT_TRUE(result.isNegative());

    Fraction f3(5, 1, false);
    result = f3 - 5;
    EXPECT_EQ(result.getNum(), 0);
    EXPECT_EQ(result.getDen(), 1);

    Fraction f4(1, 4, false);
    result = f4 + (-1);
    EXPECT_EQ(result.getNum(), 3);
    EXPECT_EQ(result.getDen(), 4);
    EXPECT_TRUE(result.isNegative());
}


TEST(FractionIntBinaryOperators, Multiplication) {
    Fraction f1(1, 2, false);
    Fraction result = f1 * 2;
    EXPECT_EQ(result.getNum(), 1);
    EXPECT_EQ(result.getDen(), 1);

    result = f1 * (-2);
    EXPECT_EQ(result.getNum(), 1);
    EXPECT_EQ(result.getDen(), 1);
    EXPECT_TRUE(result.isNegative());

    Fraction f2(3, 4, false);
    result = f2 * 3;
    EXPECT_EQ(result.getNum(), 9);
    EXPECT_EQ(result.getDen(), 4);

    Fraction f3(0, 1, false);
    result = f3 * 10;
    EXPECT_EQ(result.getNum(), 0);
    EXPECT_EQ(result.getDen(), 1);

    Fraction f4(2, 3, false);
    result = f4 * 0;
    EXPECT_EQ(result.getNum(), 0);
    EXPECT_EQ(result.getDen(), 1);
}


TEST(FractionIntBinaryOperators, Division) {
    Fraction f1(1, 2, false);
    Fraction result = f1 / 2;
    EXPECT_EQ(result.getNum(), 1);
    EXPECT_EQ(result.getDen(), 4);

    result = f1 / (-2);
    EXPECT_EQ(result.getNum(), 1);
    EXPECT_EQ(result.getDen(), 4);
    EXPECT_TRUE(result.isNegative());

    Fraction f2(3, 4, false);
    result = f2 / 3;
    EXPECT_EQ(result.getNum(), 1);
    EXPECT_EQ(result.getDen(), 4);

    Fraction f3(6, 1, false);
    result = f3 / 2;
    EXPECT_EQ(result.getNum(), 3);
    EXPECT_EQ(result.getDen(), 1);

    Fraction f4(1, 4, true);
    result = f4 / (-1);
    EXPECT_EQ(result.getNum(), 1);
    EXPECT_EQ(result.getDen(), 4);
    EXPECT_FALSE(result.isNegative()); // Два отрицательных числа дают положительное
}


TEST(FractionDoubleBinaryOperators, Addition) {
    double accur = 0.0001;
    EXPECT_NEAR(Fraction(1, 2, false) + 0.5, 1.0, accur);
    EXPECT_NEAR(Fraction(1, 4, false) + 0.25, 0.5, accur);
    EXPECT_NEAR(Fraction(1, 3, false) + 0.3333, 0.6666, accur);
    EXPECT_NEAR(Fraction(1, 2, true) + 0.5, 0.0, accur);
    EXPECT_NEAR(Fraction(3, 4, false) + (-0.75), 0.0, accur);
}

TEST(FractionDoubleBinaryOperators, Subtraction) {
    double accur = 0.0001;
    EXPECT_NEAR(Fraction(1, 2, false) - 0.25, 0.25, accur);
    EXPECT_NEAR(Fraction(1, 4, false) - 0.5, -0.25, accur);
    EXPECT_NEAR(Fraction(1, 3, false) - (-0.3333), 0.6666, accur);
    EXPECT_NEAR(Fraction(1, 2, true) - (-0.5), 0.0, accur);
    EXPECT_NEAR(Fraction(3, 4, false) - 0.25, 0.5, accur);
}

TEST(FractionDoubleBinaryOperators, Multiplication) {
    double accur = 0.0001;
    EXPECT_NEAR(Fraction(1, 2, false) * 2.0, 1.0, accur);
    EXPECT_NEAR(Fraction(1, 4, false) * 0.5, 0.125, accur);
    EXPECT_NEAR(Fraction(1, 3, false) * 3.0, 1.0, accur);
    EXPECT_NEAR(Fraction(1, 2, true) * (-2.0), 1.0, accur);
    EXPECT_NEAR(Fraction(3, 4, false) * (-4.0), -3.0, accur);
}

TEST(FractionDoubleBinaryOperators, Division) {
    double accur = 0.0001;
    EXPECT_NEAR(Fraction(1, 2, false) / 0.5, 1.0, accur);
    EXPECT_NEAR(Fraction(1, 4, false) / 2.0, 0.125, accur);
    EXPECT_NEAR(Fraction(1, 3, false) / 0.3333, 1.0, accur * 10);
    EXPECT_NEAR(Fraction(1, 2, true) / (-0.5), 1.0, accur);
    EXPECT_NEAR(Fraction(3, 4, false) / (-0.25), -3.0, accur);
}


TEST(FractionFriendOperators, AdditionIntLHS) {
    Fraction result = 1 + Fraction(1, 2, false);
    EXPECT_EQ(result.getNum(), 3);
    EXPECT_EQ(result.getDen(), 2);

    result = -1 + Fraction(1, 2, false);
    EXPECT_EQ(result.getNum(), 1);
    EXPECT_EQ(result.getDen(), 2);
    EXPECT_TRUE(result.isNegative());

    result = 2 + Fraction(3, 4, false);
    EXPECT_EQ(result.getNum(), 11);
    EXPECT_EQ(result.getDen(), 4);

    result = 0 + Fraction(1, 4, false);
    EXPECT_EQ(result.getNum(), 1);
    EXPECT_EQ(result.getDen(), 4);

    result = 5 + Fraction(1, 4, true);
    EXPECT_EQ(result.getNum(), 19);
    EXPECT_EQ(result.getDen(), 4);
}

TEST(FractionFriendOperators, SubtractionIntLHS) {
    Fraction result = 1 - Fraction(1, 2, false);
    EXPECT_EQ(result.getNum(), 1);
    EXPECT_EQ(result.getDen(), 2);

    result = -1 - Fraction(1, 2, false);
    EXPECT_EQ(result.getNum(), 3);
    EXPECT_EQ(result.getDen(), 2);
    EXPECT_TRUE(result.isNegative());

    result = 2 - Fraction(3, 4, false);
    EXPECT_EQ(result.getNum(), 5);
    EXPECT_EQ(result.getDen(), 4);

    result = 0 - Fraction(1, 4, false);
    EXPECT_EQ(result.getNum(), 1);
    EXPECT_EQ(result.getDen(), 4);
    EXPECT_TRUE(result.isNegative());

    result = 5 - Fraction(1, 4, true);
    EXPECT_EQ(result.getNum(), 21);
    EXPECT_EQ(result.getDen(), 4);
}

TEST(FractionFriendOperators, MultiplicationIntLHS) {
    Fraction result = 2 * Fraction(1, 2, false);
    EXPECT_EQ(result.getNum(), 1);
    EXPECT_EQ(result.getDen(), 1);

    result = -2 * Fraction(1, 2, false);
    EXPECT_EQ(result.getNum(), 1);
    EXPECT_EQ(result.getDen(), 1);
    EXPECT_TRUE(result.isNegative());

    result = 3 * Fraction(3, 4, false);
    EXPECT_EQ(result.getNum(), 9);
    EXPECT_EQ(result.getDen(), 4);

    result = 0 * Fraction(1, 4, false);
    EXPECT_EQ(result.getNum(), 0);
    EXPECT_EQ(result.getDen(), 1);

    result = -1 * Fraction(2, 3, false);
    EXPECT_EQ(result.getNum(), 2);
    EXPECT_EQ(result.getDen(), 3);
    EXPECT_TRUE(result.isNegative());
}

TEST(FractionFriendOperators, DivisionIntLHS) {
    Fraction result = 1 / Fraction(1, 2, false);
    EXPECT_EQ(result.getNum(), 2);
    EXPECT_EQ(result.getDen(), 1);

    result = -1 / Fraction(1, 2, false);
    EXPECT_EQ(result.getNum(), 2);
    EXPECT_EQ(result.getDen(), 1);
    EXPECT_TRUE(result.isNegative());

    result = 2 / Fraction(3, 4, false);
    EXPECT_EQ(result.getNum(), 8);
    EXPECT_EQ(result.getDen(), 3);

    result = 0 / Fraction(1, 4, false);
    EXPECT_EQ(result.getNum(), 0);
    EXPECT_EQ(result.getDen(), 1);

    // Тест на деление на дробь, дающую отрицательный результат
    result = -3 / Fraction(3, 4, true);
    EXPECT_EQ(result.getNum(), 4);
    EXPECT_EQ(result.getDen(), 1);
}


TEST(FractionFriendOperators, AdditionInt64LHS) {
    Fraction result = (int64_t)1 + Fraction(1, 2, false);
    EXPECT_EQ(result.getNum(), 3);
    EXPECT_EQ(result.getDen(), 2);

    result = (int64_t)(-1) + Fraction(1, 2, false);
    EXPECT_EQ(result.getNum(), 1);
    EXPECT_EQ(result.getDen(), 2);
    EXPECT_TRUE(result.isNegative());

    result = (int64_t)2 + Fraction(3, 4, false);
    EXPECT_EQ(result.getNum(), 11);
    EXPECT_EQ(result.getDen(), 4);

    result = (int64_t)0 + Fraction(1, 4, false);
    EXPECT_EQ(result.getNum(), 1);
    EXPECT_EQ(result.getDen(), 4);

    result = (int64_t)5 + Fraction(1, 4, true);
    EXPECT_EQ(result.getNum(), 19);
    EXPECT_EQ(result.getDen(), 4);
}

TEST(FractionFriendOperators, SubtractionInt64LHS) {
    Fraction result = (int64_t)1 - Fraction(1, 2, false);
    EXPECT_EQ(result.getNum(), 1);
    EXPECT_EQ(result.getDen(), 2);

    result = (int64_t)(-1) - Fraction(1, 2, false);
    EXPECT_EQ(result.getNum(), 3);
    EXPECT_EQ(result.getDen(), 2);
    EXPECT_TRUE(result.isNegative());

    result = (int64_t)2 - Fraction(3, 4, false);
    EXPECT_EQ(result.getNum(), 5);
    EXPECT_EQ(result.getDen(), 4);

    result = (int64_t)0 - Fraction(1, 4, false);
    EXPECT_EQ(result.getNum(), 1);
    EXPECT_EQ(result.getDen(), 4);
    EXPECT_TRUE(result.isNegative());

    result = (int64_t)5 - Fraction(1, 4, true);
    EXPECT_EQ(result.getNum(), 21);
    EXPECT_EQ(result.getDen(), 4);
}

TEST(FractionFriendOperators, MultiplicationInt64LHS) {
    Fraction result = (int64_t)2 * Fraction(1, 2, false);
    EXPECT_EQ(result.getNum(), 1);
    EXPECT_EQ(result.getDen(), 1);

    result = (int64_t)(-2) * Fraction(1, 2, false);
    EXPECT_EQ(result.getNum(), 1);
    EXPECT_EQ(result.getDen(), 1);
    EXPECT_TRUE(result.isNegative());

    result = (int64_t)3 * Fraction(3, 4, false);
    EXPECT_EQ(result.getNum(), 9);
    EXPECT_EQ(result.getDen(), 4);

    result = (int64_t)0 * Fraction(1, 4, false);
    EXPECT_EQ(result.getNum(), 0);
    EXPECT_EQ(result.getDen(), 1);

    result = (int64_t)(-1) * Fraction(2, 3, false);
    EXPECT_EQ(result.getNum(), 2);
    EXPECT_EQ(result.getDen(), 3);
    EXPECT_TRUE(result.isNegative());
}

TEST(FractionFriendOperators, DivisionInt64LHS) {
    Fraction result = 1 / Fraction(1, 2, false);
    EXPECT_EQ(result.getNum(), 2);
    EXPECT_EQ(result.getDen(), 1);

    result = (int64_t)(-1) / Fraction(1, 2, false);
    EXPECT_EQ(result.getNum(), 2);
    EXPECT_EQ(result.getDen(), 1);
    EXPECT_TRUE(result.isNegative());

    result = (int64_t)2 / Fraction(3, 4, false);
    EXPECT_EQ(result.getNum(), 8);
    EXPECT_EQ(result.getDen(), 3);

    result = (int64_t)0 / Fraction(1, 4, false);
    EXPECT_EQ(result.getNum(), 0);
    EXPECT_EQ(result.getDen(), 1);

    // Тест на деление на дробь, дающую отрицательный результат
    result = (int64_t)(-3) / Fraction(3, 4, true);
    EXPECT_EQ(result.getNum(), 4);
    EXPECT_EQ(result.getDen(), 1);
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
