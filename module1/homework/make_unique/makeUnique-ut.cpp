#include <gtest/gtest.h>
#include <memory>

#include "makeUnique.hpp"

constexpr int intValueTest = 1;
constexpr double doubleValueTest = 2.2;
constexpr bool boolValueTest = true;

struct MyType {
    MyType() = default;
    MyType(int& intValue, double&& doubleValue, bool boolValue)
        : intValue_(intValue), doubleValue_(doubleValue), boolValue_(boolValue) {}
    MyType(int&& intValue, double& doubleValue, bool boolValue)
        : intValue_(intValue), doubleValue_(doubleValue), boolValue_(boolValue) {}

    int intValue_ = intValueTest;
    double doubleValue_ = doubleValueTest;
    bool boolValue_ = boolValueTest;
};

TEST(makeUnique, shouldCreateUniquePointerToInt) {
    std::unique_ptr<int> ptr = custom::make_unique<int>(intValueTest);

    ASSERT_EQ(*ptr, intValueTest);
}

TEST(makeUnique, shouldCreateEmptyUniquePointer) {
    std::unique_ptr<int> ptr = custom::make_unique<int>();

    ASSERT_EQ(*ptr, 0);
}

TEST(makeUnique, shouldUseFirstConstructor) {
    int valueInt{10};
    auto ptr = custom::make_unique<MyType>(valueInt, 2.2, true);

    ASSERT_EQ(ptr->intValue_, valueInt);
    ASSERT_EQ(ptr->doubleValue_, doubleValueTest);
    ASSERT_EQ(ptr->boolValue_, boolValueTest);
}

TEST(makeUnique, shouldUseSecondConstructor) {
    double valueDouble{10.0};
    auto ptr = custom::make_unique<MyType>(1, valueDouble, true);

    ASSERT_EQ(ptr->intValue_, intValueTest);
    ASSERT_EQ(ptr->doubleValue_, valueDouble);
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
