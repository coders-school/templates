#include <type_traits>

template <typename T>
void universal_reference(T&& arg) {
    static_assert(std::is_same_v<T, int&>);
}

int main() {
    int number = 4;
    universal_reference(number);            // int&
    universal_reference(std::move(number)); // int&&
    universal_reference(5);                 // int&&
}