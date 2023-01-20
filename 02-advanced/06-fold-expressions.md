<!-- .slide: data-background="#111111" -->

# Fold expressions

## Wyrażenia składane

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

Wyrażenia składane zawsze muszą by w nawiasach.
<!-- .element: class="fragment fade-in" -->

___

## Fold-expressions

Składa paczkę parametrów stosując podany operatorem binarnym `op` (binarny, czyli przyjmujący 2 argumenty)

### Operatory binarne
<!-- .element: class="fragment fade-in" -->

`+ - * / % ^ & | = < > << >> += -= *= /= %= ^= &= |= <<= >>= == != <= >= && || , .* ->*`
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> jednoargumentowe złożenie prawe (unary right fold)
  * `(pack op ...)`
* <!-- .element: class="fragment fade-in" --> dwuargumentowe złożenie prawe (binary right fold)
  * `(pack op ... op init)`
* <!-- .element: class="fragment fade-in" --> jednoargumentowe złożenie lewe (unary left fold)
  * `(... op pack)`
* <!-- .element: class="fragment fade-in" --> dwuargumentowe złożenie lewe (binary left fold)
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

## Zadanie 1

Napisz funkcję `print()`, która może wydrukować wszystko na ekranie. Funkcja `print()` powinna przyjmowa dowolną liczbę argumentów. Użyj fold-expressions.

```cpp
print(1, 40, "string", 2.0);
```

Trudna wersja: spróbuj dodać odstępy między elementami.

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
```
<!-- .element: class="fragment fade-in" -->

___

## Zadanie 2

Napisz funkcję `areEven()`, która

* wypisze wszystkie parametry na ekranie za pomocą funkcji `print()` z poprzedniego zadania
* sprawdzi, czy wszystkie liczby w pakiecie parametrów są parzyste i zwróci odpowiednią wartość logiczną

```cpp
bool allEven = areEven(2, 4, 6, 9);
```

___

## Rozwiązanie

```cpp
template<typename... Numbers>
auto areEven(Numbers... nums) {
    print(nums...);
    return ((nums % 2 == 0) && ...);
}
```
<!-- .element: class="fragment fade-in" -->

___
<!-- .slide: style="font-size: 0.95em" -->
## Wartości domyślne pustych wyrażeń składanych

| Operator |  wartość   |
| :------: | :------: |
|   `*`    |   `1`    |
|   `+`    | `int()`  |
|   `&`    |   `-1`   |
|   `\|`    | `int()`  |
|   `&&`   |  `true`  |
|   `\|\|`   | `false`  |
|   `,`    | `void()` |
