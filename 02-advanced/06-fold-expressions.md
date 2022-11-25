<!-- .slide: data-background="#111111" -->

# Fold expressions

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___

## Fold expressions (C++17)

Fold-expressions umożliwiają pisanie zwartego kodu przy użyciu szablonów wariadycznych bez użycia jawnej rekurencji.

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

Zmniejsza (składa) pakiet parametrów nad operatorem binarnym op.

### Operators
<!-- .element: class="fragment fade-in" -->

`+ - * / % ^ & | = < > << >> += -= *= /= %= ^= &= |= <<= >>= == != <= >= && || , .* ->*`
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> jednoargumentowe złożenie prawe
  * `(pack op ...)`
* <!-- .element: class="fragment fade-in" --> binarne złożenie prawe
  * `(pack op ... op init)`
* <!-- .element: class="fragment fade-in" --> jednoargumentowe złożenie lewe
  * `(... op pack)`
* <!-- .element: class="fragment fade-in" --> binarne złożenie lewe
  * `(init op ... op pack)`

___

## Przykłady

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

## Zadanie

1. Napisz funkcję `print()`, która może wydrukować wszystko na ekranie. Powinieneś być w stanie przekazać do niego dowolną liczbę parametrów. Użyj fold-expressions.

    ```cpp
    print(1, 40, "string", 2.0);
    ```

    Trudna wersja: spróbuj dodać odstępy między elementami.

2. Napisz funkcję `areEven()`, która

   * drukuje wszystkie parametry na ekranie za pomocą powyższej funkcji `print()`
   * sprawdzi, czy wszystkie liczby w pakiecie parametrów są parzyste i zwróci odpowiednią wartość logiczną

    ```cpp
    bool allEven = areEven(2, 4, 6, 9);
    ```

___

## Rozwiązanie

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

Wartości domyślne, gdy pakiet parametrów jest pusty

| Operator |  wartość   |
| :------: | :------: |
|   `*`    |   `1`    |
|   `+`    | `int()`  |
|   `&`    |   `-1`   |
|   `\|`    | `int()`  |
|   `&&`   |  `true`  |
|   `\|\|`   | `false`  |
|   `,`    | `void()` |
