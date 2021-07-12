#include <cstdio>
#include <iostream>
using namespace std;

template <typename T>
void printOne(T arg) {
    std::cout << "printOne: " << arg << '\n';
}

template <typename T1, typename T2>
void printTwo(T1 arg1, T2 arg2) {
    std::cout << "printTwo: " << arg1 << ' ' << arg2 << '\n';
}

template <typename... Args>
void print_all(Args&&... args) {
    printTwo(args...);
}

template <typename... Args>
void print_each(Args&&... args) {
    (printOne(args), ...);  // fold expression from C++17
}

int main() {
    print_all("Hello!", "Lukin");
    print_each("Hello!", "Lukin");
    return 0;
}
