#include <gtest/gtest.h>
#include <memory>
#include "make_unique.hpp"

constexpr int testValue{2020};

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
