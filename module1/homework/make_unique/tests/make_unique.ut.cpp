#include "gtest/gtest.h"

#include <iostream>

#include "make_unique.hpp"

constexpr int defaultValuesOfTestClass = 0;
constexpr int initialValuesOfTestClass = 2;
constexpr int initialValue = 1;
constexpr int secondValue = 2;

class TestClass {
public:
    TestClass(int value = defaultValuesOfTestClass)
        : value_{value} {}

    int getValue() const {
        return value_;
    }

private:
    int value_;
};

TEST(MakeUniqueTest, ShouldCreateUniquePointerFromInt) {
    auto ptr = cs::make_unique<int>(initialValue);
    ASSERT_EQ(*ptr, initialValue);
}

TEST(MakeUniqueTest, ShouldCreateUniquePointerFromCustomClassWithDefaultValue) {
    auto testClass = cs::make_unique<TestClass>();
    ASSERT_EQ(testClass->getValue(), defaultValuesOfTestClass);
}

TEST(MakeUniqueTest, ShouldCreateUniquePointerFromCustomClassWithInitialValue) {
    auto testClass = cs::make_unique<TestClass>(initialValuesOfTestClass);
    ASSERT_EQ(testClass->getValue(), initialValuesOfTestClass);
}

TEST(MakeUniqueTest, ShouldCreateUniquePointerForArrayType) {
    constexpr int arraySize = 2;
    auto arrayPtr = cs::make_unique<int[]>(arraySize);
    arrayPtr[0] = initialValue;
    arrayPtr[1] = secondValue;
    ASSERT_EQ(arrayPtr[0], initialValue);
    ASSERT_EQ(arrayPtr[1], secondValue);
}
