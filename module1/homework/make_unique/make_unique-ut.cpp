#include <gtest/gtest.h>
#include <memory>
#include "make_unique.hpp"

constexpr int testIntValue = 10;

struct make_uniqueTest : public ::testing::Test {
    make_uniqueTest();
    std::unique_ptr<int> uPtr = std::make_unique<int>(testIntValue);
};

TEST(make_uniqueTest, testMakeUniqueForIntValue) {
    std::unique_ptr<int> uPtr = cs::make_unique<int>(testIntValue);
    ASSERT_EQ(*uPtr, testIntValue);
}
