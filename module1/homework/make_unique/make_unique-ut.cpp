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

TEST(test, firstTest) {
    ASSERT_EQ(1, 1);
}

TEST(make_unique, shouldMakeUniqueToInt) {
    std::unique_ptr<int> uniqZero{new int{}};
    auto testUniquePtr = make_unique<int>();
    ASSERT_EQ(*uniqZero, *testUniquePtr);
}

TEST(make_unique, shouldMakeUniqueToInt2020) {
    std::unique_ptr<int> uniqEleven{new int{testValue}};
    auto testUniquePtr = make_unique<int>(testValue);

    ASSERT_EQ(*testUniquePtr, testValue);
    ASSERT_EQ(*uniqEleven, *testUniquePtr);
}

TEST(make_unique, shouldMakeUniqueToMyTestType) {
    std::unique_ptr<MyTestType> uniqMyTestType{new MyTestType{2, 2.5, 0}};
    auto testUniquePtr = make_unique<MyTestType>(2, 2.5, 0);
    ASSERT_EQ(*uniqMyTestType, *testUniquePtr);
}
