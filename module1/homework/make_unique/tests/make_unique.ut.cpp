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
    auto testClassPtr = cs::make_unique<TestClass>();
    ASSERT_EQ(testClassPtr->firstValue_, defaultValuesOfTestClass);
    ASSERT_EQ(testClassPtr->secondValue_, defaultValuesOfTestClass);
}

TEST(MakeUniqueTest, ShouldCreateUniquePointerFromCustomClassWithInitialValue) {
    auto testClassPtr = cs::make_unique<TestClass>(initialValuesOfTestClass);
    ASSERT_EQ(testClassPtr->firstValue_, initialValuesOfTestClass);
    ASSERT_EQ(testClassPtr->secondValue_, defaultValuesOfTestClass);
}

TEST(MakeUniqueTest, ShouldCreatedUniquePointerFromCustomClassWithTwoParameters) {
    auto testClassPtr = cs::make_unique<TestClass>(initialValuesOfTestClass,
                                                   initialValuesForSecondPrameterOfTestClass);

    ASSERT_EQ(testClassPtr->firstValue_, initialValuesOfTestClass);
    ASSERT_EQ(testClassPtr->secondValue_, initialValuesForSecondPrameterOfTestClass);
}

TEST(MakeUniqueTest, ShouldCreateUniquePointerForArrayType) {
    constexpr int arraySize = 2;
    auto arrayPtr = cs::make_unique<int[]>(arraySize);
    arrayPtr[0] = initialValue;
    arrayPtr[1] = secondValue;
    ASSERT_EQ(arrayPtr[0], initialValue);
    ASSERT_EQ(arrayPtr[1], secondValue);
}

TEST(MakeUniqueTest, ShouldCreatePointerUsingCopyConstructor) {
    LRValueTestClass classToCopy;
    auto sideTestClassPtr = cs::make_unique<LRValueTestClass>(classToCopy);
    ASSERT_EQ(sideTestClassPtr->sideTestValue_, leftValue);
    ASSERT_EQ(sideTestClassPtr->sideTestValue_, classToCopy.sideTestValue_);
}

TEST(MakeUniqueTest, ShouldCreatePointerUsingMoveConstructor) {
    LRValueTestClass classToMove;
    auto sideTestClassPtr = cs::make_unique<LRValueTestClass>(std::move(classToMove));
    ASSERT_EQ(sideTestClassPtr->sideTestValue_, rightValue);
    ASSERT_TRUE(sideTestClassPtr->sideTestValue_ != classToMove.sideTestValue_);
}
