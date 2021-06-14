<!-- .slide: data-background="#111111" -->

# Specialization

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___
<!-- .slide: style="font-size: .75em" -->

## Function specialization

If we want to have the same function name, but we want our code to behave differently for some types, we can create a specialization.
<!-- .element: class="fragment fade-in" -->

```cpp
//generic function
template <typename T>
void print(T arg) {
    std::cout << arg << '\n';
}
```
<!-- .element: class="fragment fade-in" -->

```cpp
// specialization for `T = double`
template <>
void print<double>(double arg) {
    std::cout << std::setprecision(10) << arg << '\n';
}
```
<!-- .element: class="fragment fade-in" -->

```cpp
// better: overload
void print(double arg) {
    std::cout << std::setprecision(10) << arg << '\n';
}
```
<!-- .element: class="fragment fade-in" -->

Tip: do not use function specializations. Always prefer function overloads.
<!-- .element: class="fragment fade-in" -->

Template function specializations do not take part in overload resolution. Only the exact type match is considered.
<!-- .element: class="fragment fade-in" -->

Above specialization does not work for `float`. Overload does.
<!-- .element: class="fragment fade-in" -->

___

## Class specialization

Class can have not only different behavior (different methods implementations) but also different layouts. You can have completely different fields and/or their values.
<!-- .element: class="fragment fade-in" -->

___
<!-- .slide: style="font-size: .8em" -->

## Specialization example #1 - methods

```c++
#include <iostream>

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

## Specialization example #2 - field values

```c++
#include <iostream>

template<typename T>   // primary template
struct is_int {
    static constexpr bool value = false;
};

template<>  // explicit specialization for T = int
struct is_int<int> {
    static constexpr bool value = true;
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
<!-- .slide: style="font-size: 0.85em" -->

## Specialization example #3 - &lt;type_traits&gt;

To achieve the last behavior, we can use `std::false_type` and `std::true_type`. Below code is equivalent with the one from the previous example.

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

### Exercise - `is_int_key`

In `VectorMap` write a class constant `is_int_key` that holds a boolean value. It should be `true` when the key is `int` and `false` otherwise.

Generally it should do the same job as `isIntKey()` method, but we want to have it available even without having an object.

Take a look in `<type_traits>` library for that. It should be useful :)
