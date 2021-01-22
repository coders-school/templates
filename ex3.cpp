#include <iostream>


template <int T>
struct IsSmallPrime : std::false_type {};

template <>
struct IsSmallPrime<2> : std::true_type {};

template <>
struct IsSmallPrime<3> : std::true_type {};

template <>
struct IsSmallPrime<5> : std::true_type {};

template <>
struct IsSmallPrime<7> : std::true_type {};


template <class T1, class T2>
class X {};

template <typename T2>
struct X<int, T2> {};

template <typename T1>
struct X<T1, double> {};

template <>
struct X<int, double> {};

void variadic_foo() {}

template<class Head, class... Tail>
void variadic_foo(Head const& head, Tail const&... tail) {
    takesOneParam(head);    //action on head
    variadic_foo(tail...);
}

void variadic_foo(1, "ste", 4.5)
    takesOneParam(1);    //action on head
    variadic_foo("ste", 4.5);
}

void variadic_foo("ste", 4.5)
    takesOneParam("ste");    //action on head
    variadic_foo(4.5);
}

void variadic_foo(4.5)
    takesOneParam(4.5);    //action on head
    variadic_foo();
}

template<typename... Args> auto sum(1, 2, 3, 4, 5.0) {
    return (1 + 2 + 3 + 4 + 5.0);
}


int main() {
    int i = 4;
    decltype(i) j = 10.3;
    std::cout << std::boolalpha
              << IsSmallPrime<0>::value << '\n'
              << IsSmallPrime<1>::value << '\n'
              << IsSmallPrime<2>::value << '\n'
              << IsSmallPrime<3>::value << '\n'
              << IsSmallPrime<4>::value << '\n'
              << IsSmallPrime<5>::value << '\n'
              << IsSmallPrime<6>::value << '\n'
              << IsSmallPrime<7>::value << '\n'
              << IsSmallPrime<8>::value << '\n'
              << IsSmallPrime<9>::value;
}