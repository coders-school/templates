#include "make_unique.hpp"

#include <gtest/gtest.h>
#include <sstream>

struct MyType {
    const bool constructorLRC{false};
    const bool constructorRLC{false};
    MyType(int&, double&&, bool) : constructorLRC(true)  {}
    MyType(int&&, double&, bool) : constructorRLC(true) {}
};

class makeUniqueTests : public ::testing::Test
{
   protected:
    int defaultValue{5};
    double anotherValue{10.5};
    std::array<int, 5> defaultArray{1, 2, 3, 4, 5};
};

TEST_F(makeUniqueTests, noParametersShouldBeDefaultObject)
{
    auto uniqueZero = cs::make_unique<int>();
    EXPECT_EQ(*uniqueZero, 0);
}

TEST_F(makeUniqueTests, shouldCreateWithGivenValue)
{
    auto uniqueZero = cs::make_unique<int>(defaultValue);
    EXPECT_EQ(*uniqueZero, defaultValue);

    auto uniqueOne = cs::make_unique<double>(anotherValue);
    EXPECT_DOUBLE_EQ(*uniqueOne, anotherValue);
}

TEST_F(makeUniqueTests, shouldCreateWithArrays) {
    auto uniqueArray = cs::make_unique<decltype(defaultArray)>(defaultArray);
    EXPECT_EQ(*uniqueArray, defaultArray);
}

TEST_F(makeUniqueTests, uniqueArrayCanBeCreated) {
    std::unique_ptr<int[]> uniqueArray = cs::make_unique<int[]>(5);
    uniqueArray[0] = 0;
    EXPECT_EQ(uniqueArray[0], 0);
}


TEST_F(makeUniqueTests, shouldCreateObjectUsingLRC)
{
    auto expectedLRC{true};
    auto expectedRLC{false};
    auto uniqueLRC = cs::make_unique<MyType>(defaultValue, 5.0, true);
    auto actualLRC{uniqueLRC->constructorLRC};
    auto actualRLC{uniqueLRC->constructorRLC};
    EXPECT_EQ(expectedLRC, actualLRC);
    EXPECT_EQ(expectedRLC, actualRLC);
}

TEST_F(makeUniqueTests, shouldCreateObjectUsingRLC) {
    auto expectedRLC{true};
    auto expectedLRC{false};
    auto uniqueRLC = cs::make_unique<MyType>(3, anotherValue, false);
    auto actualRLC{uniqueRLC->constructorRLC};
    auto actualLRC{uniqueRLC->constructorLRC};
    EXPECT_EQ(expectedRLC, actualRLC);
    EXPECT_EQ(expectedLRC, actualLRC);
}


