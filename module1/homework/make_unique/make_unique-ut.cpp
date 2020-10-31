#include <gtest/gtest.h>
#include <memory>
#include "make_unique.hpp"

constexpr int testIntValueL = 10;
constexpr int testIntValueR = 5;
constexpr double testDoubleValueL = 3.14;
constexpr double testDoubleValueR = 6.28;
constexpr bool testBoolValue = true;
constexpr size_t arraySize = 5;

template<class Type> struct default_delete;
template<class Type> struct default_delete<Type[]>;

struct make_uniqueTest {
public:
    make_uniqueTest() = default;
    make_uniqueTest(int&, double&&, bool)
    : intValue_(testIntValueL), doubleValue_(testDoubleValueR), boolValue_(testBoolValue)
    {}
    make_uniqueTest(int&& intValue, double& doubleValue, bool)
        : intValue_(testIntValueR), doubleValue_(testDoubleValueL), boolValue_(testBoolValue)
    {}

    int intValue_ {testIntValueR};
    double doubleValue_ {testDoubleValueR};
    bool boolValue_ {testBoolValue};
};

TEST(make_uniqueIntTest, testMakeUniqueForIntValue) {
    auto uPtr = cs::make_unique<int>(testIntValueR);
    ASSERT_EQ(*uPtr, testIntValueR);
}

TEST(make_uniqueArrayTest, testMakeUniqueForArrayType) {
    auto uArray = cs::make_unique<int[]>(arraySize);
    for (size_t i =0; i < arraySize; i++) {
        uArray[i] = i;
    }
    for (size_t i =0; i < arraySize; i++) {
        ASSERT_EQ(uArray[i], i);
    }
}

TEST(make_uniqueEmptyTest, testIntEmptyConstruct) {
    auto uniqZero = cs::make_unique<int>();
    ASSERT_EQ(*uniqZero, 0);
}

TEST(make_uniqueCustomObjectTest, shouldUseFirstConstructor) {
    int intValue{testIntValueL};
    double doubleValue{testDoubleValueR};
    auto muTest = cs::make_unique<make_uniqueTest>(std::move(intValue), doubleValue, testBoolValue);
    ASSERT_EQ(muTest->intValue_, testIntValueR);
    ASSERT_EQ(muTest->doubleValue_, testDoubleValueL);
    ASSERT_EQ(muTest->boolValue_, testBoolValue);

    auto muTest2 = cs::make_unique<make_uniqueTest>(intValue, std::move(doubleValue), testBoolValue);
    ASSERT_EQ(muTest2->intValue_, testIntValueL);
    ASSERT_EQ(muTest2->doubleValue_, testDoubleValueR);
    ASSERT_EQ(muTest2->boolValue_, testBoolValue);
}