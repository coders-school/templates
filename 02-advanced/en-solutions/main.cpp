#include <iostream>
#include <type_traits>

template<class T> void f(T)     { std::cout << "1\n"; }    // #1: overload for all types
template<class T> void f(T*)    { std::cout << "3\n"; }   // #3: overload for all pointer types
template<>        void f(int*)  { std::cout << "2\n"; } // #2: specialization of #1 for pointers to int

template <
    typename T,
    typename std::enable_if<std::is_integral<T>::value, T>::type* = nullptr
> void function(T& t) {}

template <typename T>
using HasVirtDtor = std::enable_if_t<std::has_virtual_destructor_v<T>>;

template<
    class T,          // the same as #3 - template parameter
    typename = void
> T* construct(T* t, int = 4)
{ return new T{}; }

int main() {
    int a = 4;
    function<int>(a);
    f(new int{1});
    return 0;
}
