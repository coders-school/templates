#include <iostream>
#include <memory>
#include "make_unique.hpp"

struct MyType {
    MyType(int&, double&&, bool) { std::cout << "lvalue, rvalue, copy\n"; }
    MyType(int&&, double&, bool) { std::cout << "rvalue, lvalue, copy\n"; }
};

int main() {
    int lvalue{2020};
    std::cout << lvalue << '\n';
    // std::unique_ptr<int> uniqZero = make_unique<int>();
    // auto uniqEleven = make_unique<int>(2011);
    // auto uniqTwenty = make_unique<int>(lvalue);
    // auto uniqTypeLRC = make_unique<MyType>(lvalue, 3.14, true);
    // auto uniqTypeRRC = make_unique<MyType>(2020, 3.14, true);
}
