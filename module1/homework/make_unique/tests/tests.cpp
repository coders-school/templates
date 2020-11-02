#include <gtest/gtest.h>

#include "make_unique.hpp"

struct MyType {
    MyType(int&, double&&, bool) { std::cout << "lvalue, rvalue, copy\n"; }
    MyType(int&&, double&, bool) { std::cout << "rvalue, lvalue, copy\n"; }
};

class makeUniqueTests : public ::testing::Test
{
   protected:
    int defaultValue{5};
    double anotherValue{10.5};
};

TEST_F(makeUniqueTests, noParametersShouldBeDefaultObject) {
    auto uniqueZero = cs::make_unique<int>();
    EXPECT_EQ(*uniqueZero, 0);
}

TEST_F(makeUniqueTests, shouldCreateWithGivenValue) {
    auto uniqueZero = cs::make_unique<int>(defaultValue);
    EXPECT_EQ(*uniqueZero, defaultValue);
        
    auto uniqueOne = cs::make_unique<double>(anotherValue);
    EXPECT_DOUBLE_EQ(*uniqueOne, anotherValue);
}

TEST_F(makeUniqueTests, shouldCreateCustomObject) {
    auto uniqueLRC = cs::make_unique<MyType>(defaultValue, 5.0, true);
    auto uniqueRLC = cs::make_unique<MyType>(3, anotherValue, false);
}

