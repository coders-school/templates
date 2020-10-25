#include "make_unique.hpp"

#include <iostream>

struct MyType {
    MyType(int&, double&&, bool) { std::cout << "lvalue, rvalue, copy\n"; }
    MyType(int&&, double&, bool) { std::cout << "rvalue, lvalue, copy\n"; }
};

int main() {
    int lvalueFirst{2020};
    std::unique_ptr<int> uniqZero = cs::make_unique<int>();
    auto uniqEleven = cs::make_unique<int>(2011);
    auto uniqTwenty = cs::make_unique<int>(lvalueFirst);
    auto uniqTypeLRC = cs::make_unique<MyType>(lvalueFirst, 3.14, true);
    double lvalueScond{3.14};
    auto uniqTypeRRC = cs::make_unique<MyType>(2020, lvalueScond, true);

    return 0;
}
