#include <iostream>


template <typename... Args>
void print(Args&&... args) {
    (std::cout << ... << args) << '\n';
}

template <typename... Args>
bool areEven(Args&&... args) {
    print(args...);
    return ((args % 2 == 0) && ...);
}

int main() {
    print(1, "string", 5.5);
    auto r1 = areEven(1, 2, 4, 6, 8, 10);
    auto r2 = areEven(0, 2, 4, 6, 8, 10);
    std::cout << r1 << r2;
}