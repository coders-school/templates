#include <type_traits>

struct A {
    virtual ~A() {}
};

// #1 return type
template<class T>
auto construct(T* t) ->
typename std::enable_if_t<std::has_virtual_destructor_v<T>, T>* 
{
    return new T{};
}

template<class T>
T* construct2(
    T* t, 
    typename std::enable_if_t<std::has_virtual_destructor_v<T>>* = nullptr
){
    return new T{};
}

template<class T,
         typename std::enable_if_t<std::has_virtual_destructor_v<T>>* = nullptr>
T* construct3(T* t)
{ return new T{}; }

int main() {
    int* ptr = new int(4);
    A* aptr = new A{};
    auto result = construct3(aptr);
    return 0;
}