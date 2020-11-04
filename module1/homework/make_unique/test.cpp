#include "gtest/gtest.h"
#include "make_unique.hpp"

constexpr int structTestValue = 1;
constexpr int structDefaultValue = 2;
constexpr int structAnotherTestValue = 3;
constexpr int defaultTestValue = 4;
constexpr int anotherTestValue = 5;

constexpr int lValue = 6;
constexpr int rValue = 7;

struct TestStruct {
    TestStruct(int firstValue = structTestValue)
        : firstValue_{firstValue} {}

    TestStruct(int firstValue, int anotherTestValue)
        : firstValue_{firstValue}, anotherTestValue_{anotherTestValue} {}

    int firstValue_;
    int anotherTestValue_{structTestValue};
};

struct TestStructForLAndRValue {
    TestStructForLAndRValue()
        : testValue_{lValue} {}

    TestStructForLAndRValue(const TestStructForLAndRValue&)
        : TestStructForLAndRValue() {}

    TestStructForLAndRValue(TestStructForLAndRValue&&)
        : testValue_{rValue} {}

    int testValue_;
};

TEST(MakeUniqueTest, ShouldCreateUniquePointer) {
    auto ptr = coders_school::make_unique<int>(defaultTestValue);
    EXPECT_EQ(*ptr, defaultTestValue);
}

TEST(MakeUniqueTest, ShouldCreatePointerWithCopyConstructor) {
    TestStructForLAndRValue copyTest;
    auto testStructPtr = coders_school::make_unique<TestStructForLAndRValue>(copyTest);
    EXPECT_EQ(testStructPtr->testValue_, lValue);
    EXPECT_EQ(testStructPtr->testValue_, copyTest.testValue_);
}

TEST(MakeUniqueTest, ShouldCreatePointerWithMoveConstructor) {
    TestStructForLAndRValue moveTest;
    auto testStructPtr = coders_school::make_unique<TestStructForLAndRValue>(std::move(moveTest));
    EXPECT_EQ(testStructPtr->testValue_, rValue);
}

TEST(MakeUniqueTest, ShouldCreateUniquePointerFromStrucktWithDefaultValue) {
    auto testStructPtr = coders_school::make_unique<TestStruct>();
    EXPECT_EQ(testStructPtr->firstValue_, structTestValue);
    EXPECT_EQ(testStructPtr->anotherTestValue_, structTestValue);
}

TEST(MakeUniqueTest, ShouldCreateUniquePointerFromStrucktdefaultTestValue) {
    auto testStructPtr = coders_school::make_unique<TestStruct>(structDefaultValue);
    EXPECT_EQ(testStructPtr->firstValue_, structDefaultValue);
    EXPECT_EQ(testStructPtr->anotherTestValue_, structTestValue);
}

TEST(MakeUniqueTest, ShouldCreatedUniquePointerFromStrucktWithParameters) {
    auto testStructPtr = coders_school::make_unique<TestStruct>(structDefaultValue,
                                                                structAnotherTestValue);

    EXPECT_EQ(testStructPtr->firstValue_, structDefaultValue);
    EXPECT_EQ(testStructPtr->anotherTestValue_, structAnotherTestValue);
}

TEST(MakeUniqueTest, ShouldCreateUniquePointerForArray) {
    constexpr int arraySize = 2;
    auto arrayPtr = coders_school::make_unique<int[]>(arraySize);
    arrayPtr[0] = defaultTestValue;
    arrayPtr[1] = anotherTestValue;
    EXPECT_EQ(arrayPtr[0], defaultTestValue);
    EXPECT_EQ(arrayPtr[1], anotherTestValue);
}
