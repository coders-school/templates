<!-- .slide: data-background="#111111" -->

# Variable templates (C++17)

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___

## Why?

Eg. different precision
<!-- .element: class="fragment fade-in" -->

```cpp
template<class T>
constexpr T pi = T(3.1415926535897932385L);

template<class T>
T circular_area(T r) { return pi<T> * r * r; }
```
<!-- .element: class="fragment fade-in" -->

But it is really rarely used.
<!-- .element: class="fragment fade-in" -->

___
<!-- .slide: style="font-size: .8em" -->

## Specialization example #2 - field values

Remember this code?
<!-- .element: class="fragment fade-in" -->

```c++ []
#include <iostream>

template<typename T>   // primary template
struct is_int {
    static constexpr bool value = false;
};

template<>  // explicit specialization for T = int
struct is_int<int> {
    static constexpr bool value = true;
};

template<typename T>
constexpr bool is_int_v = is_int<T>::value;

int main() {
    std::cout << is_int_v<char> << '\n';  // prints 0 (false)
    std::cout << is_int_v<int> << '\n';   // prints 1 (true)
    return 0;
}
```
<!-- .element: class="fragment fade-in" -->

We mainly use template variables as a helpers to class template field values.
<!-- .element: class="fragment fade-in" -->

___

Check out [`type_traits` on cppreference.com](https://en.cppreference.com/w/cpp/header/type_traits)

Every trait has a corresponding helper variable template.

___

## Exercise

Write a variable template `is_int_key_v`. It should return a value of `is_int_key` field in a given template type.
