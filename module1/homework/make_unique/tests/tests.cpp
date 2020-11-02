#include "make_unique.hpp"

#include <gtest/gtest.h>
#include <sstream>

struct MyType {
    MyType(int&, double&&, bool) { std::cout << "lvalue, rvalue, copy\n"; }
    MyType(int&&, double&, bool) { std::cout << "rvalue, lvalue, copy\n"; }
};

class makeUniqueTests : public ::testing::Test
{
   protected:
    int defaultValue{5};
    double anotherValue{10.5};
    std::array<int, 5> defaultArray{1, 2, 3, 4, 5};
};

class makeUniqueTestsWithStdOut : public makeUniqueTests
{
    std::streambuf* coutBuffer{};

   protected:
    std::stringstream testStream{};
    void SetUp() override
    {
        coutBuffer = std::cout.rdbuf();
        std::cout.rdbuf(testStream.rdbuf());
    }

    void TearDown() override
    {
        std::cout.rdbuf(coutBuffer);
        testStream.str(std::string());
    }
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

TEST_F(makeUniqueTestsWithStdOut, shouldCreateObjectWithPerfectForwarding)
{
    auto expectedLRCOutput{"lvalue, rvalue, copy\n"};
    auto uniqueLRC = cs::make_unique<MyType>(defaultValue, 5.0, true);
    auto actualLRCOutput{testStream.str()};
    EXPECT_EQ(expectedLRCOutput, actualLRCOutput);

    testStream.str(std::string());

    auto expectedRLCOutput{"rvalue, lvalue, copy\n"};
    auto uniqueRLC = cs::make_unique<MyType>(3, anotherValue, false);
    auto actualRLCOutput{testStream.str()};
    EXPECT_EQ(expectedRLCOutput, actualRLCOutput);
}
