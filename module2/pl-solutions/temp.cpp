#include <iostream>

template<class T> void f(T t)     { std::cout << "1\n" << typeid(t).name(); }    // #1: overload for all types
template<>        void f(int*)  { std::cout << "2\n"; } // #2: specialization of #1 for pointers to int
template<class T> void f(T*)    { std::cout << "3\n"; }   // #3: overload for all pointer types



template <
    typename T = int,
    typename std::enable_if<std::is_integral<T>::value, T>::type* = nullptr,
    int* = nullptr,
    size_t N = 0
> void function(T& t,
                int a = 42,
                int = 52)
{}

template <typename T>
using HasVirtDtor = std::enable_if_t<std::has_virtual_destructor_v<T>>;

template<
    class T          // the same as #3 - template parameter
> T* construct(T* t)
{
    using N = HasVirtDtor<T>;
    return new T{};
}

class A{
    virtual ~A() {}
};

int main() {
    f(new int{1});
    A* a;
    auto result = construct(a);
    // function<int>(42);

    return 0;
}
