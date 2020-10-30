#include <iostream>
#include <memory>
#include "make_unique.hpp"

struct MyType {
    MyType(int&, double&&, bool) { std::cout << "lvalue, rvalue, copy\n"; }
    MyType(int&&, double&, bool) { std::cout << "rvalue, lvalue, copy\n"; }
};

int main() {
    int lvalue{2020};

    std::unique_ptr<int> uniqZero = coders::make_unique<int>();
    auto uniqEleven = coders::make_unique<int>(2011);
    auto uniqTwenty = coders::make_unique<int>(lvalue);
    /*
    auto uniqTypeLRC = coders::make_unique<MyType>(lvalue, 3.14, true);
    auto uniqTypeRRC = coders::make_unique<MyType>(2020, 3.14, true);
    */
}