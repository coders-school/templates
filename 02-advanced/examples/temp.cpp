#include <iostream>
#include <type_traits>
#include <cmath>
template <typename T, typename = std::enable_if_t<!std::is_floating_point_v<T> || sizeof(T) == 8>>
void f(T t) {

}

void h(std::string s, int i) {

}

template <typename... Args>
void g(Args... args) {
    g(args...); // -> h("asda", 1);
    // j(args)...; // -> j("asda"), j(1);  // ale to mozna tylko wewnatrz innej funkcji zrobic, np ponizej
    g(const_cast<const Args*>(&args)...);

}

template <typename X, typename... Args>
void g(X first, Args... args) {
    auto a = first;
    g(args...);
}


// void f(double) = delete;

// template <>
// void f<double>(double t) {
//     std::cout << "nie\n";
// }

class A{};

int main() {
    f(3.14);
    g();
    g("asda", 1);
    // A a;
    // f(a);
}