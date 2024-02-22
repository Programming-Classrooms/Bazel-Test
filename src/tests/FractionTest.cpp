#include "../fraction/Fraction.hpp"
#include <stdexcept>
#include <gtest/gtest.h>


TEST(FractionTest, DefaultConstructor) {
    Fraction f;
    EXPECT_EQ(f.getNum(), 0);
    EXPECT_EQ(f.getDen(), 1);
}

TEST(FractionTest, ParameterizedConstructor) {
    Fraction f(3, 4);
    EXPECT_EQ(f.getNum(), 3);
    EXPECT_EQ(f.getDen(), 4);
}

TEST(FractionTest, CopyConstructor) {
    Fraction f1(4, 5);
    Fraction f2(f1);
    EXPECT_EQ(f1.getNum(), 4);
    EXPECT_EQ(f2.getDen(), 5);
}

TEST(FractionTest, Addition) {
    Fraction f1(1, 2);
    Fraction f2(1, 3);
    Fraction result = f1 + f2;
    EXPECT_EQ(result.getNum(), f1.getNum() * f2.getDen() + f2.getNum() * f1.getDen());
    EXPECT_EQ(result.getDen(), f1.getDen() * f2.getDen());
}

TEST(FractionTest, Simplify) {
    Fraction f(6, 18);
    Fraction reduced = f.reduce(); 
    EXPECT_EQ(reduced.getNum(), 1);
    EXPECT_EQ(reduced.getDen(), 3);
}

TEST(FractionTest, Multiplication) {
    Fraction f1(1, 2);
    Fraction f2(2, 3);
    Fraction result = f1 * f2;
    EXPECT_EQ(result.getNum(), 1);
    EXPECT_EQ(result.getDen(), 3);
}

TEST(FractionTest, Division) {
    Fraction f1(1, 2);
    Fraction f2(2, 3);
    Fraction result = f1 / f2;
    EXPECT_EQ(result.getNum(), 1 * 3);
    EXPECT_EQ(result.getDen(), 2 * 2);
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
