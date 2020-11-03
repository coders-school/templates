
#include <gtest/gtest.h>
#include <tuple>
#include "makeUnique.hpp"

namespace TestConsts {
constexpr int intValue = 42;
constexpr double doubleValue = 4.2;
constexpr bool boolValue = false;
constexpr int lValueInt = -1;
constexpr int rValueInt = 1;
}  // namespace TestConsts

struct TestData {
    TestData(int f, double s, bool t)
        : first_(f), second_(s), third_(t) {}
    int first_ = 4;
    double second_ = 4.2;
    bool third_ = false;
};

struct LRValue {
    LRValue(int value)
        : value_(value){};
    LRValue(LRValue&)
        : value_(TestConsts::lValueInt){};
    LRValue(LRValue&&)
        : value_(TestConsts::rValueInt){};

    int value_;
};

TEST(makeUnique, shouldCreatePointerToInt) {
    auto ptr = myMakeUnique::make_unique<int>(TestConsts::intValue);

    ASSERT_EQ(*ptr, TestConsts::intValue);
}

TEST(makeUnique, shouldCreatePointerToDouble) {
    auto ptr = myMakeUnique::make_unique<double>(TestConsts::doubleValue);

    ASSERT_EQ(*ptr, TestConsts::doubleValue);
}

TEST(makeUnique, shouldCreatePointerToIntWithDefaultValue) {
    auto ptr = myMakeUnique::make_unique<int>();

    ASSERT_EQ(*ptr, int());
}

TEST(makeUnique, shouldCreatePointerToTuple) {
    auto ptr = myMakeUnique::make_unique<std::tuple<int, double>>(
        TestConsts::intValue, TestConsts::doubleValue);

    ASSERT_EQ(*ptr, std::make_tuple(TestConsts::intValue, TestConsts::doubleValue));
}

TEST(makeUnique, shouldCreatePointerToOwnStructure) {
    auto ptr = myMakeUnique::make_unique<TestData>(TestConsts::intValue,
                                                   TestConsts::doubleValue,
                                                   TestConsts::boolValue);

    ASSERT_EQ(ptr->first_, TestConsts::intValue);
    ASSERT_EQ(ptr->second_, TestConsts::doubleValue);
    ASSERT_EQ(ptr->third_, TestConsts::boolValue);
}

TEST(makeUnique, shoulCreatePointerToIntArray) {
    auto size = 11;
    auto arr = myMakeUnique::make_unique<int[]>(size);

    for (auto i = 0; i < size; i++) {
        arr[i] = TestConsts::intValue;
        ASSERT_EQ(arr[i], TestConsts::intValue);
    }
}

TEST(makeUnique, shouldCreatePointerByPassLValue) {
    LRValue data(TestConsts::intValue);
    auto ptr = myMakeUnique::make_unique<LRValue>(data);

    ASSERT_EQ(ptr->value_, TestConsts::lValueInt);
}

TEST(makeUnique, shouldCreatePointerByPassRValue) {
    LRValue data(TestConsts::intValue);
    auto ptr = myMakeUnique::make_unique<LRValue>(std::move(data));

    ASSERT_EQ(ptr->value_, TestConsts::rValueInt);
}