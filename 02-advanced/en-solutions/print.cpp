#include <iostream>

template <typename... Printables>
void print(Printables... printables) {
    (std::cout << ... << printables) << std::endl;
    // ((std::cout << printables << " "), ...);
}

template<typename ... T>
bool areEven(T ... candidates) {
    print(candidates...);
    return ((candidates % 2 == 0) && ...);
}

int main() {
    print(1, 40, "string", 2.1);
    bool allEven = areEven(2, 4, 6, 9);
    std::cout << std::boolalpha << allEven;
    return 0;
}
