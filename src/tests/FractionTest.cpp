#include "../fraction/Fraction.hpp"
#include <stdexcept>
#include <gtest/gtest.h>

TEST(FractionTest, DefaultConstructor) {
    Fraction f;
    EXPECT_EQ(f.getNumerator(), 0);
    EXPECT_EQ(f.getDenominator(), 1);
}

TEST(FractionTest, ParameterizedConstructor) {
    Fraction f(3, 4);
    EXPECT_EQ(f.getNumerator(), 3);
    EXPECT_EQ(f.getDenominator(), 4);
}

TEST(FractionTest, CopyConstructor) {
    Fraction f1(4, 5);
    Fraction f2(f1);
    EXPECT_EQ(f1.getNumerator(), 4);
    EXPECT_EQ(f2.getDenominator(), 5);
}

TEST(FractionTest, Addition) {
    Fraction f1(1, 2);
    Fraction f2(1, 3);
    Fraction result = f1 + f2;
    EXPECT_EQ(result.getNumerator(), f1.getNumerator() * f2.getDenominator() + f2.getNumerator() * f1.getDenominator());
    EXPECT_EQ(result.getDenominator(), f1.getDenominator() * f2.getDenominator());
}

TEST(FractionTest, Simplify) {
    Fraction f(6, 18);
    Fraction simplified = f.simplify(); 
    EXPECT_EQ(simplified.getNumerator(), 1);
    EXPECT_EQ(simplified.getDenominator(), 3);
}

TEST(FractionTest, Multiplication) {
    Fraction f1(1, 2);
    Fraction f2(2, 3);
    Fraction result = f1 * f2;
    EXPECT_EQ(result.getNumerator(), 1);
    EXPECT_EQ(result.getDenominator(), 3);
}

TEST(FractionTest, Division) {
    Fraction f1(1, 2);
    Fraction f2(2, 3);
    Fraction result = f1 / f2;
    EXPECT_EQ(result.getNumerator(), 1 * 3);
    EXPECT_EQ(result.getDenominator(), 2 * 2);
}

TEST(FractionTest, ZeroDenominator) {
    Fraction f1(1, 1);
    Fraction f2(0, 1);
    EXPECT_THROW({  
        Fraction result = f1 / f2;
    }, std::runtime_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
