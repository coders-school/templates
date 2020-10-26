#include "gtest/gtest.h"
#include <memory>
#include "make_unique.hpp"

constexpr int testInt{5};
constexpr int testI {0};
constexpr double testD {0.0};
constexpr bool testB {false};
constexpr int iValueL{1};
constexpr double dValueR{2.0};
constexpr int iValueR{3};
constexpr double dValueL{4.0};
constexpr int bValue{true};


struct TestType {
    TestType() = default;
    TestType(int&, double&&, bool) : i_(iValueL), d_(dValueR), b_(bValue) { }
    TestType(int&&, double&, bool) : i_(iValueR), d_(dValueL), b_(bValue) { }

    int i_ = testI;
    int d_ = testD;
    bool b_ = testB;

};

TEST(makeUnique, shouldCreateInt) {
    auto ptr = cs::make_unique<int>(testInt);
    ASSERT_EQ(testInt, *ptr);
}

TEST(makeUnique, shouldCreateSTLStruct) {
    std::vector<int> testVector{1,2,3,4};
    auto ptr = cs::make_unique<std::vector<int>>(std::initializer_list{1,2,3,4});
    ASSERT_EQ(testVector, *ptr);
}

TEST(makeUnique, shouldCreateArray) {
    constexpr int arraySize{3};
    int arrayContent{5};
    auto ptr = cs::make_unique<int[]>(arraySize);
    for(auto i = 0; i < arraySize; i++) {
        ptr[i] = arrayContent;
    }
    for(auto i = 0; i < arraySize; i++) {
        ASSERT_EQ(ptr[i], arrayContent);
    }
}

TEST(makeUnique, shouldConstructCustomClass) {
    auto ptr = cs::make_unique<TestType>();

    ASSERT_EQ(ptr->i_, testI);
    ASSERT_EQ(ptr->d_, testD);
    ASSERT_EQ(ptr->b_, testB);
}

TEST(makeUnique, shouldUseAppropriateConstructor) {
    int valueInt{10};
    auto ptr = cs::make_unique<TestType>(valueInt, 0.0, false);

    ASSERT_EQ(ptr->i_, iValueL);
    ASSERT_EQ(ptr->d_, dValueR);
    ASSERT_EQ(ptr->b_, bValue);

    double valueDouble{10.0};
    auto ptr1 = cs::make_unique<TestType>(0.0, valueDouble, false);

    ASSERT_EQ(ptr1->i_, iValueR);
    ASSERT_EQ(ptr1->d_, dValueL);
    ASSERT_EQ(ptr1->b_, bValue);
}