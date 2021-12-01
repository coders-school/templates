#include <type_traits>
using namespace std;

class A {};

template <class T>
void swapo(T& a, T& b)
{
    static_assert(std::is_copy_constructible<T>::value, "Swap requires copying");
    static_assert(std::is_nothrow_move_constructible_v<T> &&
                  std::is_nothrow_move_assignable_v<T>);
    auto c = b;
    b = a;
    a = c;
}

int main() {
    A a{};
    A b{};

    swapo(a, b);
    return 0;
}