#include <gtest/gtest.h>
#include <memory>
#include "make_unique.hpp"

constexpr int testIntValue = 10;
constexpr double testDoubleValue = 3.14;
constexpr bool testBoolValue = true;
constexpr size_t arraySize = 5;

template<class Type> struct default_delete;
template<class Type> struct default_delete<Type[]>;

struct make_uniqueTest {
public:
    make_uniqueTest() = default;
    make_uniqueTest(int& intValue, double&& doubleValue, bool boolValue)
    : intValue_(intValue), doubleValue_(doubleValue), boolValue_(boolValue)
    {}
    make_uniqueTest(int&& intValue, double& doubleValue, bool boolValue)
        : intValue_(intValue), doubleValue_(doubleValue), boolValue_(boolValue)
    {}

    int intValue_ {testIntValue};
    double doubleValue_ {testDoubleValue};
    bool boolValue_ {testBoolValue};
};

TEST(make_uniqueIntTest, testMakeUniqueForIntValue) {
    auto uPtr = cs::make_unique<int>(testIntValue);
    ASSERT_EQ(*uPtr, testIntValue);
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
    int lvalueInt{2020};
    auto muTest = cs::make_unique<make_uniqueTest>(lvalueInt, 3.14, testBoolValue);
    ASSERT_EQ(muTest->intValue_, lvalueInt);
    ASSERT_EQ(muTest->doubleValue_, testDoubleValue);
    ASSERT_EQ(muTest->boolValue_, testBoolValue);

    double lvalueDouble{3.14};
    auto muTest2 = cs::make_unique<make_uniqueTest>(10, lvalueDouble, testBoolValue);
    ASSERT_EQ(muTest2->intValue_, testIntValue);
    ASSERT_EQ(muTest2->doubleValue_, lvalueDouble);
    ASSERT_EQ(muTest2->boolValue_, testBoolValue);
}