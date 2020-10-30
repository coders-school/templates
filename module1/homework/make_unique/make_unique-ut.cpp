#include <array>
#include <memory>
#include "gtest/gtest.h"
#include "make_unique.hpp"

constexpr int testValInt{666};
constexpr double testValDbl{123.456};
constexpr int testValInt_L{50};
constexpr int testValInt_R{60};

struct TestStruct {
    int structValInt_{};
    double structValDbl_{};

    TestStruct() = default;
    TestStruct(int i_val, double d_val)
        : structValInt_(i_val), structValDbl_(d_val) {}
};

struct LRvalTestStruct {
    int testValue;

    LRvalTestStruct(int val = testValInt_L)
        : testValue{val} {}

    LRvalTestStruct(const LRvalTestStruct&)
        : testValue{testValInt_L} {}

    LRvalTestStruct(LRvalTestStruct&&)
        : testValue{testValInt_R} {}
};

TEST(MakeUniqueTest, ShouldMakeUniqueForInt) {
    auto uniquePtr = coders::make_unique<int>(testValInt);
    ASSERT_EQ(*uniquePtr, testValInt);
}

TEST(MakeUniqueTest, ShouldMakeUniqueForEmptyInt) {
    auto uniquePtr = coders::make_unique<int>();
    ASSERT_EQ(*uniquePtr, 0);
}

TEST(MakeUniqueTest, ShouldMakeUniqueForDbl) {
    auto uniquePtr = coders::make_unique<double>(testValDbl);
    ASSERT_EQ(*uniquePtr, testValDbl);
}

TEST(MakeUniqueTest, ShouldMakeUniqueForIntArray) {
    int arrSize{10};
    int offset = 5;
    auto uniquePtr = coders::make_unique<int[]>(arrSize);
    for (auto i = 0; i < arrSize; i++) {
        uniquePtr[i] = i + offset;
    }
    for (auto i = 0; i < arrSize; i++) {
        ASSERT_EQ(uniquePtr[i], i + offset);
    }
}

TEST(MakeUniqueTest, ShouldMakeUniqueForSTLIntArray) {
    constexpr int arrSize{4};
    std::array<int, arrSize> stlIntArray = {6, 66, 666, 6666};
    auto uniquePtr = coders::make_unique<int[]>(arrSize);
    for (auto i = 0; i < arrSize; i++) {
        uniquePtr[i] = stlIntArray[i];
    }
    for (auto i = 0; i < arrSize; i++) {
        ASSERT_EQ(uniquePtr[i], stlIntArray[i]);
    }
}

TEST(MakeUniqueTest, ShouldMakeUniqueForTestStruct) {
    auto uniquePtr = coders::make_unique<TestStruct>(testValInt, testValDbl);

    ASSERT_EQ(uniquePtr->structValInt_, testValInt);
    ASSERT_EQ(uniquePtr->structValDbl_, testValDbl);
}

TEST(MakeUniqueTest, ShouldMakeUniqueForEmptyTestStruct) {
    auto uniquePtr = coders::make_unique<TestStruct>();

    ASSERT_EQ(uniquePtr->structValInt_, 0);
    ASSERT_EQ(uniquePtr->structValDbl_, 0.0);
}

TEST(MakeUniqueTest, ShouldMakeUniqueForLvalTestStruct) {
    auto uniquePtr = coders::make_unique<LRvalTestStruct>();
    ASSERT_EQ(uniquePtr->testValue, testValInt_L);
}

TEST(MakeUniqueTest, ShouldMakeUniqueForRvalTestStruct) {
    LRvalTestStruct temp;
    auto uniquePtr = coders::make_unique<LRvalTestStruct>(std::move(temp));
    ASSERT_EQ(uniquePtr->testValue, testValInt_R);
}
