#include "gtest/gtest.h"

#include <iostream>

#include "make_unique.hpp"

constexpr int testingIntValue{3};
constexpr double testingDoubleValue{3.3};
constexpr bool testingBoolValue{true};

constexpr int testingLeftValue{23};
constexpr int testingRightValue{32};

class TestingClass {
public:
    TestingClass() = default;
    TestingClass(int intValue, double doubleValue, bool boolValue)
        : intValue_(intValue), doubleValue_(doubleValue), boolValue_(boolValue) {}

    int intValue_{testingIntValue};
    double doubleValue_{testingDoubleValue};
    bool boolValue_{testingBoolValue};
};

class TestingClassLRvalues {
public:
    TestingClassLRvalues(int value) : testingValue_(value){};
    TestingClassLRvalues(TestingClassLRvalues&) : testingValue_(testingLeftValue){};
    TestingClassLRvalues(TestingClassLRvalues&&) : testingValue_(testingRightValue){};

    TestingClassLRvalues& operator=(TestingClassLRvalues&) {
        testingValue_ = testingLeftValue;
        return *this;
    }

    TestingClassLRvalues& operator=(TestingClassLRvalues&&) {
        testingValue_ = testingRightValue;
        return *this;
    }

    int testingValue_;
};

TEST(MakeUniqueTest, ShouldCreateUniquePointerFromInt) {
    auto ptr = coders::make_unique<int>(testingIntValue);
    ASSERT_EQ(*ptr, testingIntValue);
}

TEST(MakeUniqueTest, ShouldCreateUniquePointerFromNotInitializedInt) {
    auto ptr = coders::make_unique<int>();
    ASSERT_EQ(*ptr, 0);
}

TEST(MakeUniqueTest, ShouldCreateUniquePointerFromTestingClass) {
    auto ptr = coders::make_unique<TestingClass>(testingIntValue, testingDoubleValue, testingBoolValue);
    ASSERT_EQ(ptr->intValue_, testingIntValue);
    ASSERT_EQ(ptr->doubleValue_, testingDoubleValue);
    ASSERT_EQ(ptr->boolValue_, testingBoolValue);
}

TEST(MakeUniqueTest, ShouldCreateArrayOfUniquePointer) {
    constexpr int arraySize = 3;

    auto testingArray = coders::make_unique<int[]>(arraySize);

    for (size_t i = 0; i < arraySize; i++) {
        testingArray[i] = testingIntValue;
    }

    for (size_t i = 0; i < arraySize; i++) {
        ASSERT_EQ(testingArray[i], testingIntValue);
    }
}

TEST(MakeUniqueTest, ShouldCreatePointerUsingLeftValue) {
    TestingClassLRvalues testingClass(testingIntValue);
    auto ptr = coders::make_unique<TestingClassLRvalues>(testingClass);

    ASSERT_EQ(ptr->testingValue_, testingLeftValue);
}

TEST(MakeUniqueTest, ShouldCreatePointerUsingRightValue) {
    TestingClassLRvalues testingClass(testingIntValue);
    auto ptr = coders::make_unique<TestingClassLRvalues>(std::move(testingClass));

    ASSERT_EQ(ptr->testingValue_, testingRightValue);
}