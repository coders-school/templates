#include <array>
#include <vector>
#include <iostream>

template<typename T, typename... Args>
void push_back_vec(std::vector<T>& v, Args&&... args) {
    (v.push_back(args), ...)
    (..., v.push_back(args));
}

int main() {
    std::vector<int> v;
    push_back_vec(v, 6, 2, 45, 12);
    for (auto & e: v) {
        std::cout << e << " ";
    }

    return 0;
}
