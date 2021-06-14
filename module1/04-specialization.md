<!-- .slide: data-background="#111111" -->

# Specialization

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___
<!-- .slide: style="font-size: .8em" -->

## Specialization examples #1

We want to have the same structures or function, but we want our code to behave in a different way for some types. This is how we can achieve it:

```c++
#include <iostream>
using namespace std;

template<typename T>   // primary template
struct is_int {
    bool get() const { return false; }
};

template<>  // explicit specialization for T = int
struct is_int<int> {
    bool get() const { return true; }
};


int main() {
    is_int<char> iic;
    is_int<int> iii;
    std::cout << iic.get() << '\n';  // prints 0 (false)
    std::cout << iii.get() << '\n';  // prints 1 (true)
    return 0;
}
```
<!-- .element: style="font-size: .65em" -->

___
<!-- .slide: style="font-size: .8em" -->

## Specialization examples #2

We have a class `is_int` with a static const boolean field `value`. It is initialized with `false` by default. However, if we provide an `int` as a parameter type, we want to have a `true` value there. This is how to achieve it:

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
    std::cout << is_int<char>::value << '\n';  // prints 0 (false)
    std::cout << is_int<int>::value << '\n';   // prints 1 (true)
    return 0;
}
```
<!-- .element: style="font-size: .65em" -->

You can play with the code [here](https://ideone.com/fork/LEIx7e)

___
<!-- .slide: style="font-size: .8em" -->

## Specialization examples #3

We have a class `is_int` with a static const boolean field `value`. It is initialized with `false` by default. However, if we provide an `int` as a parameter type, we want to have a `true` value there. This is how to achieve it:

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

template<typename T>
constexpr bool is_int_v = false;



int main() {
    std::cout << is_int_v<char> << '\n';  // prints 0 (false)
    std::cout << is_int_v<int> << '\n';   // prints 1 (true)
    return 0;
}
```
<!-- .element: style="font-size: .65em" -->

You can play with the code [here](https://ideone.com/fork/LEIx7e)

___

## Specialization in `<type_traits>` library

The concept of specialization is heavily used in [`<type_traits>` library](https://en.cppreference.com/w/cpp/header/type_traits). Please take a look there.
<!-- .element: class="fragment fade-in" -->

Generally, we can have different behaviour of the code, depending on the type that we provided.
<!-- .element: class="fragment fade-in" -->

Of course, we could write normal structures or functions above, but this solution with templates is more generic. It means that for every type that we provide to `is_int` by default value `false` will be returned.
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

The interactive version of this code is [here](https://ideone.com/fork/GaTh0B)

___

## Exercise

Write a template class `IsSmallPrime` which holds boolean value `true` or `false`, depending on the integer value passed into the template parameter.

You should use specialization for values 2, 3, 5 and 7. In the case of 0, 1, 4, 6, 8 and 9 it should hold a `false` value.

Hint: Besides typename or class parameter, templates can also have int parameters: eg. `template <typename T1, class T2, int N> class C {}`.

___

### Exercise - `Size`

Add an additional template parameter to our VectorMap - Size. It should be an integral template param. It's default value should be 0.

Write a constructor that reserve vector's memory upfront. Use vector's `reserve()` method and pass Size as an argument.

### Exercise - `is_int_key`

Write a class constant `is_int_key` that holds a boolean value. It should be `true` when the key is `int` and `false` otherwise.

Generally it should do the same job as `isIntKey()` method, but we want to have it available even without having an object.

Take a look in `<type_traits>` library for that. It should be useful :)
