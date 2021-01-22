#include <iostream>

template<typename ...Args>
void print(Args&&... args) {
    // (std::cout << ... << args);
    ((std::cout << args << ' '), ...);
    // (std::cout << (' ' << ... << args)) << '\n';
}

template<typename... Args>
auto sum(Args... args) {
    return (args + ...);
    // return (... + args);
    // return (0 + ... + args);
    // return (args + ... + 0);
}

template<typename... Numbers>
auto areEven(Numbers... nums) {
    print(nums...);
    return ((nums % 2 == 0) && ...);
}

int main() {
    auto result = sum(1, 2, 3, 4);
    std::cout << result << '\n';
    bool res = areEven(2, 4, 6, 8, 10);
    std::cout << res << '\n';
    bool res2 = areEven(2, 4, 6, 8, 9);
    std::cout << res2 << '\n';
    return 0;
}