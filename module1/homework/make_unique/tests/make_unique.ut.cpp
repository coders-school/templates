#include "gtest/gtest.h"

#include <iostream>

#include "make_unique.hpp"

constexpr int defaultValuesOfTestClass = 0;
constexpr int initialValuesOfTestClass = 2;
constexpr int initialValuesForSecondPrameterOfTestClass = 6;
constexpr int initialValue = 1;
constexpr int secondValue = 2;

constexpr int leftValue = 69;
constexpr int rightValue = 96;

class TestClass {
public:
    TestClass(int firstValue = defaultValuesOfTestClass)
        : firstValue_{firstValue} {}

    TestClass(int firstValue, int secondValue)
        : firstValue_{firstValue}, secondValue_{secondValue} {}

    int firstValue_;
    int secondValue_{defaultValuesOfTestClass};
};

class LRValueTestClass {
public:
    LRValueTestClass()
        : sideTestValue_{leftValue} {}

    LRValueTestClass(const LRValueTestClass&)
        : LRValueTestClass() {}

    LRValueTestClass(LRValueTestClass&&)
        : sideTestValue_{rightValue} {}

    int sideTestValue_;
};

TEST(MakeUniqueTest, ShouldCreateUniquePointerFromInt) {
    auto ptr = cs::make_unique<int>(initialValue);
    ASSERT_EQ(*ptr, initialValue);
}

TEST(MakeUniqueTest, ShouldCreateUniquePointerFromCustomClassWithDefaultValue) {
    auto testClass = cs::make_unique<TestClass>();
    ASSERT_EQ(testClass->firstValue_, defaultValuesOfTestClass);
    ASSERT_EQ(testClass->secondValue_, defaultValuesOfTestClass);
}

TEST(MakeUniqueTest, ShouldCreateUniquePointerFromCustomClassWithInitialValue) {
    auto testClass = cs::make_unique<TestClass>(initialValuesOfTestClass);
    ASSERT_EQ(testClass->firstValue_, initialValuesOfTestClass);
    ASSERT_EQ(testClass->secondValue_, defaultValuesOfTestClass);
}

TEST(MakeUniqueTest, ShouldCreatedUniquePointerFromCustomClassWithTwoParameters) {
    auto testClass = cs::make_unique<TestClass>(initialValuesOfTestClass,
                                                initialValuesForSecondPrameterOfTestClass);

    ASSERT_EQ(testClass->firstValue_, initialValuesOfTestClass);
    ASSERT_EQ(testClass->secondValue_, initialValuesForSecondPrameterOfTestClass);
}

TEST(MakeUniqueTest, ShouldCreateUniquePointerForArrayType) {
    constexpr int arraySize = 2;
    auto arrayPtr = cs::make_unique<int[]>(arraySize);
    arrayPtr[0] = initialValue;
    arrayPtr[1] = secondValue;
    ASSERT_EQ(arrayPtr[0], initialValue);
    ASSERT_EQ(arrayPtr[1], secondValue);
}

TEST(MakeUniqueTest, ShouldCreatePointerUsingLeftValue) {
    auto sideTestClass = cs::make_unique<LRValueTestClass>();
    ASSERT_EQ(sideTestClass->sideTestValue_, leftValue);
}


TEST(MakeUniqueTest, ShouldCreatePointerUsingRightValue) {
    LRValueTestClass classToMove;
    auto sideTestClass = cs::make_unique<LRValueTestClass>(std::move(classToMove));
    ASSERT_EQ(sideTestClass->sideTestValue_, rightValue);
}
