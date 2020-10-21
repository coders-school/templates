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
    make_uniqueTest();
    make_uniqueTest(int intValue, double doubleValue, bool boolValue)
    : intValue_(intValue), doubleValue_(doubleValue), boolValue_(boolValue)
    {}

    bool operator==(const make_uniqueTest& other) const {
        return intValue_ == other.intValue_
            && doubleValue_ == other.doubleValue_
            && boolValue_ == other.boolValue_;
    }

private:
    int intValue_;
    double doubleValue_;
    bool boolValue_;
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

TEST(make_uniqueLvalueTest, testLvalueConstruct) {
    int lvalue{2020};
    auto uniqTwenty = cs::make_unique<int>(lvalue);
    ASSERT_EQ(*uniqTwenty, lvalue);
}

TEST(make_uniqueCustomObjectTest, testLvalueDoubleBoolConstruct) {
    make_uniqueTest muTest{testIntValue, testDoubleValue, testBoolValue};
    auto uniqeObject = cs::make_unique<make_uniqueTest>(testIntValue, testDoubleValue, testBoolValue);
    ASSERT_EQ(*uniqeObject, muTest);

    int lvalue{2020};
    make_uniqueTest muTest2{lvalue, testDoubleValue, testBoolValue};
    auto uniqeObject2 = cs::make_unique<make_uniqueTest>(lvalue, testDoubleValue, testBoolValue);
    ASSERT_EQ(*uniqeObject2, muTest2);
}