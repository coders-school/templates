#include <array>
#include <iostream>
#include <type_traits>

template <typename T>
void f(T t) {
    std::cout << "f" << t << '\n';
}

template <typename ... Args>
constexpr std::array<std::common_type_t<Args...>, sizeof...(Args)> make_array(Args&& ... args) {
    // (f(args)...);
    return { std::forward<Args>(args)... };
    // (std::forward<Args>(args), ...);
    // auto var = f1(), f2(), f3();
}

int main() {
    std::array<int, 3> a = make_array(1, 2, 3);
    std::array<double, 4> b = make_array(1.1, 2.2, 3.3, 4.4);

    auto c = make_array('a', 'c', 'd', 'z', 'e');
    std::cout << c.size() << '\n';
    for (auto & el : c) {
        std::cout << el << " ";
    }
    std::cout << '\n';
    return 0;
}
