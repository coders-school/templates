#include <gtest/gtest.h>
#include <memory>

#include "make_unique.hpp"

constexpr int firstParam = 5;
constexpr double secondParam = 2.34;
constexpr char thirdParam = 'c';

class TestClass {
public:
    TestClass() = default;
    TestClass(int inum, double dnum, char cSign)
        : intNum_(inum),
          doubleNum_(dnum),
          charSign_(cSign) {
    }

    bool operator==(const TestClass& other) const {
        return intNum_ == other.intNum_ &&
               doubleNum_ == other.doubleNum_ &&
               charSign_ == other.charSign_;
    }

private:
    int intNum_ = firstParam;
    double doubleNum_ = secondParam;
    char charSign_ = thirdParam;
};

TEST(MakeUniqueIntTest, shouldCreateUniquePtrToInt) {
    constexpr int initValue = 5;
    std::unique_ptr<int> ptr = cs::make_unique<int>(initValue);

    ASSERT_EQ(*ptr, initValue);
}

TEST(MakeUniqueCustomClass, shouldCreateUniquePtrForCustomClassObject) {
    TestClass toCompare{firstParam, secondParam, thirdParam};

    auto ptr = cs::make_unique<TestClass>(firstParam, secondParam, thirdParam);

    ASSERT_EQ(*ptr, toCompare);
}

TEST(MakeUniqueCustomClass, shouldCreateUniquePtrForCustomClassDefaultObject) {
    TestClass toCompare{};

    auto ptr = cs::make_unique<TestClass>();

    ASSERT_EQ(*ptr, toCompare);
}

TEST(MakeUniqueArrayTest, shouldCreateArrayUniquePtr) {
    constexpr int value = 5;
    constexpr size_t arraySize = 5;
    auto arr = cs::make_unique<int[]>(arraySize);

    for (size_t i = 0; i < arraySize; ++i) {
        arr[i] = value;
    }

    for (size_t i = 0; i < arraySize; ++i) {
        ASSERT_EQ(arr[i], value);
    }
}
