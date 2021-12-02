<!-- .slide: data-background="#111111" -->

# Specjalizacje

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___
<!-- .slide: style="font-size: .65em" -->

## Specjalizacje funkcji

Jeśli chcemy mieć tę samą nazwę funkcji, ale chcemy, aby nasz kod zachowywał się inaczej dla niektórych typów, możemy stworzyć specjalizację.
<!-- .element: class="fragment fade-in" -->

```cpp
// generic function
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

Ale czemu by nie użyć przeciążenia?
<!-- .element: class="fragment fade-in" -->

```cpp
// better: overload
void print(double arg) {
    std::cout << std::setprecision(10) << arg << '\n';
}
```
<!-- .element: class="fragment fade-in" -->

Wskazówka: Nie używaj specjalizacji funkcji! Zawsze preferuj przeciążenia funkcji.
<!-- .element: class="fragment fade-in" -->

Specjalizacje funkcji szablonów nie biorą udziału w początkowych fazach procesu "overload resolution" (o nim opowiem niebawem). Kompilator rozważa tylko dokładne dopasowania typów.
<!-- .element: class="fragment fade-in" -->

Czyli: powyższa specjalizacja nie zadziała dla typu `float`. Przeciążenie zadziała.
<!-- .element: class="fragment fade-in" -->

___

## Specjalizacje klas

Klasa może mieć nie tylko inne zachowanie (różne implementacje metod), ale także różne pola lub ich domyślne wartości!
<!-- .element: class="fragment fade-in" -->

___
<!-- .slide: style="font-size: .8em" -->

## Przykład #1 - metody

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

## Przykład #2 - wartości pól

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

[Tutaj](https://ideone.com/fork/LEIx7e) możesz pobawić się tym kodem.

___
<!-- .slide: style="font-size: 0.85em" -->

## Przykład #3 - &lt;type_traits&gt;

Aby osiągnąć to samo zachowanie, możemy użyć `std::false_type` i `std::true_type`. Poniższy kod jest równoważny z przykładem #2.

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

Interaktywna wersja [tutaj](https://ideone.com/fork/GaTh0B)

___

### Zadanie - `is_int_key`

W klasie `VectorMap` dodaj stałą `is_int_key` typu `bool`. Powinna być ona ustawiona na `true` gdy klucz jest typu `int`, a na `false` w przeciwnym przypadku.

Ogólnie ta stała powinna robić to samo co metoda `isIntKey()`, z tą różnicą, że nie musimy tworzyć obieku klasy, aby ją dostać (to właśnie jest metaprogramowanie).

Poszukaj przydatnych rzeczy w bibliotece `<type_traits>` 🙂
