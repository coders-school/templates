<!-- .slide: data-background="#111111" -->

# Fold expressions

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___

## Fold expressions (C++17)

Fold-expressions allow writing compact code with variadic templates without using explicit recursion.

```cpp
template<typename... Args> auto sum(Args... args) {
    return (args + ...);
    // return (... + args);     // the same
    // return (0 + ... + args); // the same
    // return (args + ... + 0); // the same
    // return args + ...;       // error - missing parentheses
}

template<typename... Args> bool f(Args... args) {
    return (args && ... && args); // error: both operands
}                                 // contain unexpanded
                                  // parameter packs
```
<!-- .element: class="fragment fade-in" -->

___

## Fold-expressions

Reduces (folds) a parameter pack over a binary operator op.

### Operators
<!-- .element: class="fragment fade-in" -->

`+ - * / % ^ & | = < > << >> += -= *= /= %= ^= &= |= <<= >>= == != <= >= && || , .* ->*`
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> unary right fold
  * `(pack op ...)`
* <!-- .element: class="fragment fade-in" --> binary right fold
  * `(pack op ... op init)`
* <!-- .element: class="fragment fade-in" --> unary left fold
  * `(... op pack)`
* <!-- .element: class="fragment fade-in" --> binary left fold
  * `(init op ... op pack)`

___

## Examples

```cpp
template<typename... Args>
bool all(Args... args) {
    return (... && args);
}

bool b = all(true, true, true, false);
```
<!-- .element: class="fragment fade-in" -->

```cpp
template<typename T, typename... Args>
void push_back_vec(std::vector<T>& v, Args&&... args) {
    (v.push_back(args), ...);
}

std::vector<int> v;
push_back_vec(v, 6, 2, 45, 12);
```
<!-- .element: class="fragment fade-in" -->

___

## Task

1. Write a `print()` function that can print anything on a screen. You should be able to pass any number of parameters to it. Use fold expressions.

    ```cpp
    print(1, 40, "string", 2.0);
    ```

    Difficult version: try to add a space between elements.

2. Write an `areEven()` function, that

   * prints all parameters on screen using above `print()` function
   * check if all numbers in parameter pack are even and return a proper boolean value

    ```cpp
    bool allEven = areEven(2, 4, 6, 9);
    ```

___

## Solution

```cpp
template<typename ...Args>
void print(Args&&... args) {
    (std::cout << ... << args) << '\n';
}

template<typename ...Args>
void printSpace(Args&&... args) {
    ((std::cout << " " << args), ...) << '\n';
}

template<typename... Numbers>
auto areEven(Numbers... nums) {
    print(nums...);
    return ((nums % 2 == 0) && ...);
}
```
<!-- .element: class="fragment fade-in" -->

___

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
