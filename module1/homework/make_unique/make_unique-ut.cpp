#include <gtest/gtest.h>
#include <memory>
#include "make_unique.hpp"

constexpr int testValue{2020};
constexpr int intValue{1};
constexpr double doubleValue{1.5};
constexpr bool boolValue{true};

class MyTestType {
public:
    MyTestType() = default;
    MyTestType(int firstValue, double secondValue, bool thirdValue)
        : intValue_(firstValue), doubleValue_(secondValue), boolValue_(thirdValue) {}

    bool operator==(const MyTestType& other) const {
        return intValue_ == other.intValue_ &&
               doubleValue_ == other.doubleValue_ &&
               boolValue_ == other.boolValue_;
    }

private:
    int intValue_{intValue};
    double doubleValue_{doubleValue};
    bool boolValue_{boolValue};
};

TEST(make_unique, shouldMakeUniqueToInt) {
    std::unique_ptr<int> uniqZero{new int{}};
    auto testUniquePtr = cs::make_unique<int>();
    ASSERT_EQ(*uniqZero, *testUniquePtr);
}

TEST(make_unique, shouldMakeUniqueToInt2020) {
    std::unique_ptr<int> uniqEleven{new int{testValue}};
    auto testUniquePtr = cs::make_unique<int>(testValue);

    ASSERT_EQ(*testUniquePtr, testValue);
    ASSERT_EQ(*uniqEleven, *testUniquePtr);
}

TEST(make_unique, shouldMakeUniqueToEmpytyMyTestTypeObject) {
    std::unique_ptr<MyTestType> uniqMyTestType{new MyTestType{}};
    auto testUniquePtr = cs::make_unique<MyTestType>();
    ASSERT_EQ(*uniqMyTestType, *testUniquePtr);
}

TEST(make_unique, shouldMakeUniqueToMyTestTypeObject) {
    std::unique_ptr<MyTestType> uniqMyTestType{new MyTestType{2, 2.5, 0}};
    auto testUniquePtr = cs::make_unique<MyTestType>(2, 2.5, 0);
    ASSERT_EQ(*uniqMyTestType, *testUniquePtr);
}

TEST(make_unique, shouldMakeUniqueToIntArray) {
    constexpr size_t arraySize = 4;
    auto testArrayUniquePtr = cs::make_unique<int[]>(arraySize);
    for (size_t counter = 0; counter < arraySize; counter++) {
        testArrayUniquePtr[counter] = testValue + counter;
    }
    for (size_t counter = 0; counter < arraySize; counter++) {
        ASSERT_EQ(testArrayUniquePtr[counter], testValue + counter);
    }
}
