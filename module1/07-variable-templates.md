<!-- .slide: data-background="#111111" -->

# Variable templates

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___

<!-- .slide: style="font-size: .8em" -->

## Specialization example #3

We have a class `is_int` with a static const boolean field `value`. It is initialized with `false` by default. However, if we provide an `int` as a parameter type, we want to have a `true` value there. This is how to achieve it:

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

template<typename T>
constexpr bool is_int_v = is_int<T>;

int main() {
    std::cout << is_int_v<char> << '\n';  // prints 0 (false)
    std::cout << is_int_v<int> << '\n';   // prints 1 (true)
    return 0;
}
```
<!-- .element: style="font-size: .65em" -->

You can play with the code [here](https://ideone.com/fork/LEIx7e)

___

## Exercise

Write a variable template `is_int_key_v`. It should return a value of `is_int_key` field in a given type.
