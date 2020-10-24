#include <iostream>
#include <memory>

#include "make_unique.hpp"

struct MyType {
    MyType(int&, double&&, bool) { std::cout << "lvalue, rvalue, copy\n"; }
    MyType(int&&, double&, bool) { std::cout << "rvalue, lvalue, copy\n"; }
};

int main() {
    auto ptr = cs::make_unique<int>(5);
    std::cout << *ptr << '\n';

    int lvalue{2020};
    std::unique_ptr<int> uniqZero = cs::make_unique<int>();
    auto uniqEleven = cs::make_unique<int>(2011);
    auto uniqTwenty = cs::make_unique<int>(lvalue);
    auto uniqTypeLRC = cs::make_unique<MyType>(lvalue, 3.14, true);
    double lvaluePi{3.14};
    auto uniqTypeRRC = cs::make_unique<MyType>(2020, lvaluePi, true);

    return 0;
}
