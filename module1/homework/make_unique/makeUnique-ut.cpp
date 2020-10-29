#include <gtest/gtest.h>
#include <memory>

#include "makeUnique.hpp"

constexpr int intValueTest{1};
constexpr double doubleValueTest{2.2};
constexpr bool boolValueTest{true};
constexpr int rValueUsed{10};
constexpr int lValueUsed{20};

struct MyType {
    MyType() = default;
    MyType(int intValue, double doubleValue, bool boolValue)
        : intValue_(intValue), doubleValue_(doubleValue), boolValue_(boolValue) {}

    int intValue_ = intValueTest;
    double doubleValue_ = doubleValueTest;
    bool boolValue_ = boolValueTest;
};

struct TestStruct {
    TestStruct(int value) : testValue_(value){};
    TestStruct(TestStruct&) : testValue_(lValueUsed){};
    TestStruct(TestStruct&&) : testValue_(rValueUsed){};

    TestStruct& operator=(TestStruct&) {
        testValue_ = lValueUsed;
        return *this;
    }

    TestStruct& operator=(TestStruct&&) {
        testValue_ = rValueUsed;
        return *this;
    }

    int testValue_;
};

TEST(makeUnique, shouldCreateUniquePointerToInt) {
    std::unique_ptr<int> ptr = custom::make_unique<int>(intValueTest);

    ASSERT_EQ(*ptr, intValueTest);
}

TEST(makeUnique, shouldCreateUniquePointerToNotDefinedInt) {
    std::unique_ptr<int> ptr = custom::make_unique<int>();

    ASSERT_EQ(*ptr, 0);
}

TEST(makeUnique, shouldCreateUniquePointerToStruct) {
    int intValue{10};
    auto ptr = custom::make_unique<MyType>(intValue, doubleValueTest, boolValueTest);

    ASSERT_EQ(ptr->intValue_, intValue);
    ASSERT_EQ(ptr->doubleValue_, doubleValueTest);
    ASSERT_EQ(ptr->boolValue_, boolValueTest);
}

TEST(makeUnique, shouldCreateArrayUniquePointer) {
    size_t size = 5;
    auto testArray = custom::make_unique<double[]>(size);

    for (size_t i = 0; i < size; i++) {
        testArray[i] = doubleValueTest;
    }

    for (size_t i = 0; i < size; i++) {
        ASSERT_EQ(testArray[i], doubleValueTest);
    }
}

TEST(makeUnique, shouldCreateUniquePointerUsingLvalue) {
    TestStruct testStruct(intValueTest);
    auto ptr = custom::make_unique<TestStruct>(testStruct);

    ASSERT_EQ(ptr->testValue_, lValueUsed);
}

TEST(makeUnique, shouldCreateUniquePointerUsingMove) {
    TestStruct testStruct(intValueTest);
    auto ptr = custom::make_unique<TestStruct>(std::move(testStruct));

    ASSERT_EQ(ptr->testValue_, rValueUsed);
}
