<!-- .slide: data-background="#111111" -->

# Szablony zmiennych (C++17)

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___

## Po co?

Np. inna precyzja.
<!-- .element: class="fragment fade-in" -->

```cpp []
template<class T>
constexpr T pi = T(3.1415926535897932385L);

template<class T>
T circular_area(T r) { return pi<T> * r * r; }
```
<!-- .element: class="fragment fade-in" -->

Ale to jest niesamowicie rzadko używane.
<!-- .element: class="fragment fade-in" -->

___
<!-- .slide: style="font-size: .8em" -->

## Przykład specjalizacji #2 - wartości pól

Pamiętasz ten kod?
<!-- .element: class="fragment fade-in" -->

```c++ [|13-14]
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

Szablonów zmiennych używamy głównie jako "pomocników" (helpers) dla statycznych wartości pobieranych z klas szablonowych.
<!-- .element: class="fragment fade-in" -->

___

Zobacz [`type_traits` na cppreference.com](https://en.cppreference.com/w/cpp/header/type_traits)

Każdy `type_trait` ma odpowiedni szablon zmiennej, dzięki któremu jego zapis można uprościć.

___

## Zadanie

Napisz szablon zmiennej `is_int_key_v`. Zmienna powinna mieć wartość taką samą jak pole `is_int_key` dla podanego typu szablonowego.
