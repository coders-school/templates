#include <iostream>

// template <typename... Args>
// void print(Args... args) {
//     ((std::cout << args << " "), ...);
// }

// template <typename... Ts>
// void print(Ts... ts) {
//     std::string space = "";
//     (((std::cout << space << ts), space = " "), ...);
// }

//kropki w złym miejscu powodują fail:
template <typename... Types>
void print(Types&&... args) {
    (std::cout << args << ...) << '\n';
}

template <typename... V>
void print(V&&... args) {
    std::cout << (... << args);
    // std::cout << (arg1 << arg2 << arg3);
}

template <typename... Args>
bool areEven(Args&&... args) {
    print(args...);
    return ((args % 2 == 0) && ...);
    return (arg1 % 2 == 0) && (arg2 % 2 == 0) && (arg3 % 2 == 0)
}

int main() {
    print(1, 40, 4, 2);
    return 0;
}
