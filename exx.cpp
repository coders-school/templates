#include <iostream>

template<typename T>   // primary template
struct is_int : std::false_type {};

template<>  // explicit specialization for T = int
struct is_int<int> : std::true_type {};

int main() {
    std::cout << std::boolalpha << is_int<double>::value;
    std::cout << std::boolalpha << is_int<int>::value;

    is_int<double> ii;
    std::cout << ii.value;
}