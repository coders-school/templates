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

    MyTestType(int& intLVal, double&& doubleRVal, bool boolVal)
        : intValue_(intLVal), doubleValue_(doubleRVal), boolValue_(boolVal) {}

    MyTestType(int&& intRVal, double& doubleLVal, bool boolVal)
        : intValue_(intRVal), doubleValue_(doubleLVal), boolValue_(boolVal) {}

    bool operator==(const MyTestType& other) const {
        return intValue_ == other.intValue_ &&
               doubleValue_ == other.doubleValue_ &&
               boolValue_ == other.boolValue_;
    }

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
    ASSERT_EQ(testUniquePtr->intValue_, intValue);
    ASSERT_EQ(testUniquePtr->doubleValue_, doubleValue);
    ASSERT_EQ(testUniquePtr->boolValue_, boolValue);
}

TEST(make_unique, shouldMakeUniqueToMyTestTypeObjectWithIntLValue) {
    int intLValue{1};

    auto testUniquePtr = cs::make_unique<MyTestType>(intLValue, 1.5, true);
    ASSERT_EQ(testUniquePtr->intValue_, intLValue);
    ASSERT_EQ(testUniquePtr->doubleValue_, doubleValue);
    ASSERT_EQ(testUniquePtr->boolValue_, boolValue);
}

TEST(make_unique, shouldMakeUniqueToMyTestTypeObjectWithDoubleLValue) {
    double doubleLValue{1.5};

    auto testUniquePtr = cs::make_unique<MyTestType>(1, doubleLValue, true);
    ASSERT_EQ(testUniquePtr->intValue_, intValue);
    ASSERT_EQ(testUniquePtr->doubleValue_, doubleLValue);
    ASSERT_EQ(testUniquePtr->boolValue_, boolValue);
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
