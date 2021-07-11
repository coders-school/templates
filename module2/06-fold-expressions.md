<!-- .slide: data-background="#111111" -->

# Fold expressions

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___

## Fold expressions (C++17)

Fold expressions allow to write compact code with variadic templates without using explicit recursion.

```cpp
template<typename... Args> auto sum(Args... args) {
    return (args + ...);
    // return (... + args);     // the same
    // return (0 + ... + args); // the same
    // return (args + ... + 0); // the same
    // return args + ...;       // error - missing parentheses
}

template<typename... Args> bool f(Args... args) {
    return (true && ... && args); // OK
}

template<typename... Args> bool f(Args... args) {
    return (args && ... && args); // error: both operands
}                                 // contain unexpanded
                                  // parameter packs
```

___

## Exercise

Write a `print()` function that can print anything on a screen. You should be able to pass any number of parameters to it. Use fold expressions.

Write an `areEven()` function, that

* prints all parameters on screen using above `print()` function
* check if all numbers in parameter pack are even and return a proper boolean value

___

## Solution

```cpp
template<typename ...Args>
void print(Args&&... args) {
    (std::cout << ... << args) << '\n';
}

template<typename... Numbers>
auto areEven(Numbers... nums) {
    print(nums...);
    return ((nums % 2 == 0) && ...);
}
```

Try to add a space between elements in `print()`.

___

<!-- TODO: Add logo, Animations and PDF -->

## Fold expressions

Default values when parameter pack is empty

| Operator |  Value   |
| :------: | :------: |
|   `*`    |   `1`    |
|   `+`    | `int()`  |
|   `&`    |   `-1`   |
|   `\|`    | `int()`  |
|   `&&`   |  `true`  |
|   `\|\|`   | `false`  |
|   `,`    | `void()` |
