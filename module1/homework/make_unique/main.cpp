#include <iostream>
#include <memory>

#include "make_unique.hpp"

int main() {
    auto ptr = cs::make_unique<int>(5);

    std::cout << *ptr << '\n';

    return 0;
}
