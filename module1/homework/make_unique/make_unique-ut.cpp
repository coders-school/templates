#include <gtest/gtest.h>
#include <memory>

#include "make_unique.hpp"

constexpr int firstParameter = 10;
constexpr int secondParameter = 20;
constexpr int thirdParameter = 30;

constexpr char LValueParameter = 'a';
constexpr char RValueParameter = 'b';

class SimpleClass {
public:
    SimpleClass() = default;
    SimpleClass(int f, int s, int t)
        : first_(f), second_(s), third_(t) {}

    bool operator==(const SimpleClass& other) const {
        return first_ == other.first_ &&
               second_ == other.second_ &&
               third_ == other.third_;
    }

private:
    int first_ = firstParameter;
    int second_ = secondParameter;
    int third_ = thirdParameter;
};

class RLValue {
public:
    RLValue()
        : char_(LValueParameter) {}

    RLValue(const RLValue&)
        : RLValue() {}

    RLValue(RLValue&&)
        : char_(RValueParameter) {}

    RLValue& operator=(const RLValue&) {
        char_ = LValueParameter;
        return *this;
    }

    RLValue operator=(RLValue&&) {
        char_ = RValueParameter;
        return *this;
    }

    char char_;
};

TEST(MakeUniqueDoubleTest, shouldCreateUniquePtrToDouble) {
    constexpr int doubleValue = 5;
    std::unique_ptr<int> ptr = MyMakeUnique::make_unique<int>(doubleValue);

    ASSERT_EQ(*ptr, doubleValue);
}

TEST(MakeUniqueSimpleClass, shouldCreateUniquePtrForSimpleClass) {
    SimpleClass compare{};

    auto ptr = MyMakeUnique::make_unique<SimpleClass>();

    ASSERT_EQ(*ptr, compare);
}

TEST(MakeUniqueForArrayTest, shouldCreateUniquePtrToArray) {
    constexpr int defaultValue = 10;
    constexpr size_t size = 10;
    auto array = MyMakeUnique::make_unique<int[]>(size);

    for (size_t i = 0; i < size; i++) {
        array[i] = defaultValue;
    }

    for (size_t i = 0; i < size; i++) {
        ASSERT_EQ(array[i], defaultValue);
    }
}

TEST(MakeUniqueToLValue, shouldCreateUniquePtrFromLValue) {
    RLValue test;

    auto ptr = MyMakeUnique::make_unique<RLValue>(test);
    ASSERT_EQ(ptr->char_, LValueParameter);
}

TEST(MakeUniqueToRValue, shouldCreateUniquePtrFromRValueUsingMove) {
    RLValue test;
    auto ptr = MyMakeUnique::make_unique<RLValue>(std::move(test));

    ASSERT_EQ(ptr->char_, RValueParameter);
}
