#include <iostream>
#include "make_unique.hpp"

struct MyType {
    MyType(int&, double&&, bool) { std::cout << "lvalue, rvalue, copy\n"; }
    MyType(int&&, double&, bool) { std::cout << "rvalue, lvalue, copy\n"; }
};

int main() {
    int lvalue{2020};
    std::unique_ptr<int> uniqZero = MyMakeUnique::make_unique<int>();
    auto uniqEleven = MyMakeUnique::make_unique<int>(2011);
    auto uniqTwenty = MyMakeUnique::make_unique<int>(lvalue);
    auto uniqTypeLRC = MyMakeUnique::make_unique<MyType>(lvalue, 3.14, true);
    double PI = 3.14;
    auto uniqTypeRRC = MyMakeUnique::make_unique<MyType>(2020, PI, true);
    return 0;
}
