#include <iostream>

template<typename ...Args>
void print(Args&&... args) {
    (std::cout << ... << args) << '\n';
}

template<typename ...Args>
void printSpace(Args&&... args) {
    ((std::cout << " " << args), ...) << '\n';
}

template<typename... Numbers>
auto areEven(Numbers... nums) {
    print(nums...);
    return ((nums % 2 == 0) && ...);
}


int main() {
    printSpace(1, 40, "string", 2.1);
    auto result = areEven(2, 4, 6, 9);
    std::cout << result << '\n';
    return 0;
}
