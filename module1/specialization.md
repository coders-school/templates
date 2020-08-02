<!-- .slide: data-background="#111111" -->

# Template specialization

___
<!-- .slide: style="font-size: .8em" -->

## Specialization examples

We have a class `is_int` with boolean field value, which is by default initialized with `false`. However, if we provide an `int` as a parameter type, we want to have a `true` value there. This is how to achieve it:

```c++
#include <iostream>
using namespace std;

template<typename T>   // primary template
struct is_int {
    static const bool value = false;
};

template<>  // explicit specialization for T = int
struct is_int<int> {
    static const bool value = true;
};


int main() {
    std::cout << is_int<char>::value << std::endl;  // prints 0 (false)
    std::cout << is_int<int>::value << std::endl;   // prints 1 (true)
    return 0;
}
```
<!-- .element: style="font-size: .65em" -->

You can play with the code [here](https://ideone.com/fork/LEIx7e)
___

## Specialization in `<type_traits>` library

The concept of specialization is heavily used in [`<type_traits>` library](https://en.cppreference.com/w/cpp/header/type_traits). Please take a look there.
<!-- .element: class="fragment fade-in" -->

Generally, we can have different behavior of the code, depending on the type that we provided.
<!-- .element: class="fragment fade-in" -->

Of course we could write normal structures or functions above, but this solution with templates is more generic. It means that for every type that we provide to `is_int` by default value `false` will be returned.
<!-- .element: class="fragment fade-in" -->

___
<!-- .slide: style="font-size: 0.85em" -->

## Specialization in `<type_traits>` library example

To achieve mentioned behavior, we can use `std::false_type` and `std::true_type`. This is equivalent code from previous slide with `std::false_type` and `std::true_type used`.

```c++
#include <iostream>
using namespace std;

template<typename T>   // primary template
struct is_int : std::false_type
{};

template<>  // explicit specialization for T = int
struct is_int<int> : std::true_type
{};

int main() {
    std::cout << is_int<char>::value << std::endl;  // prints 0 (false)
    std::cout << is_int<int>::value << std::endl;   // prints 1 (true)
    return 0;
}
```

Interactive version of this code is [here](https://ideone.com/fork/GaTh0B)

___

## Exercise

Write a template class `IsSmallPrime` which holds boolean value `true` or `false`, depending on the integer value passed into template parameter.

You should use specialization for values 2, 3, 5 and 7. In case of 0, 1, 4, 6, 8 and 9 it should hold `false` value.

Hint: Beside of typename or class parameter, templates can also have int parameters: eg. `template <typename T1, class T2, int N> class C {}`.