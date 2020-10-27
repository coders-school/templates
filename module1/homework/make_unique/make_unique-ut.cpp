#include <gtest/gtest.h>
#include <memory>

#include "make_unique.hpp"

constexpr int firstParam = 5;
constexpr double secondParam = 2.34;
constexpr char thirdParam = 'c';

constexpr int lValueParam = 1;
constexpr int rValueParam = 2;

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

class TestClassRLValue {
public:
    TestClassRLValue()
        : num_{lValueParam} {};

    TestClassRLValue(const TestClassRLValue&)
        : TestClassRLValue() {}

    TestClassRLValue(TestClassRLValue&&)
        : num_{rValueParam} {}

    TestClassRLValue& operator=(const TestClassRLValue&) {
        num_ = lValueParam;
        return *this;
    }

    TestClassRLValue& operator=(TestClassRLValue&&) {
        num_ = rValueParam;
        return *this;
    }

    int num_;
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

TEST(MakeUniqueLValue, shouldCreateUniquePtrUsingLvalue) {
    TestClassRLValue tc;
    auto ptr = cs::make_unique<TestClassRLValue>(tc);

    ASSERT_EQ(ptr->num_, lValueParam);
}

TEST(MakeUniqueRValue, shouldCreateUniquePtrViaMove) {
    TestClassRLValue tc;
    auto ptr = cs::make_unique<TestClassRLValue>(std::move(tc));

    ASSERT_EQ(ptr->num_, rValueParam);
}
