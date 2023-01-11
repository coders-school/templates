<!-- .slide: data-background="#111111" -->

# SFINAE

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___

## Prosty przykład SFINAE

```cpp
template <typename T>
void foo(T arg) {}
template <typename T>
void foo(T* arg) {}
```
<!-- .element: class="fragment fade-in" -->

Wywołanie `foo(42)` spowoduje, że kompilator poszukując funkcji o odpowiednich nazwach, spróbuje wygenerować 2 poniższe funkcje.
<!-- .element: class="fragment fade-in" -->


```cpp []
void foo(int arg) {}
void foo(int* arg) {}
```
<!-- .element: class="fragment fade-in" -->

Gdyby kompilator podstawił <code>42</code> jako argument drugiej funkcji, spowodowałoby to błąd kompilacji. Wobec tego odrzuca on to przeciążenie.
<!-- .element: class="fragment fade-in" -->

Ostatecznie nie ma żadnego błędu kompilacji, bo udało się dopasować pierwszą funkcję. Tada! Oto właśnie SFINAE w praktyce.
<!-- .element: class="fragment fade-in" -->

Gdyby nie było pierwszej funkcji, dostalibyśmy błąd kompilacji.
<!-- .element: class="fragment fade-in" -->

___
<!-- .slide: style="font-size: 0.85em" -->

## SFINAE

Substitution Failure Is Not An Error - technika meta-programowania
<!-- .element: class="fragment fade-in" -->

> This rule applies during overload resolution of function templates: When substituting the explicitly specified or deduced type for the template parameter fails, the specialization is discarded from the overload set instead of causing a compile error.
>
> -- <a href="https://en.cppreference.com/w/cpp/language/sfinae">cppreference.com</a>
<!-- .element: class="fragment fade-in" -->

### Co nam to daje?
<!-- .element: class="fragment fade-in" -->

Możemy mieć uniwersalny interfejs i to my jako twórcy kodu (biblioteki) decydujemy, która implementacja ma się wykonać. Kompilator może więc wybrać optymalną implementację w zależności od typu danych.
<!-- .element: class="fragment fade-in" -->

W taki sposób może być zaimplementowana np. funkcja [`std::advance()`](https://en.cppreference.com/w/cpp/iterator/advance).
<!-- .element: class="fragment fade-in" -->

___

## Biblioteka `type_traits`

<a href="https://en.cppreference.com/w/cpp/header/type_traits">&lt;type_traits&gt; on cppreference.com</a>

___

## Przykład SFINAE

### `std:enable_if`

```cpp
template<
    class T,
    typename = std::enable_if<std::has_virtual_destructor_v<T>>::type
>
T* construct(T* t) {
    return new T{};
}
```
<!-- .element: class="fragment fade-in" -->

Funkcja `construct` będzie widziana tylko dla typów `T`, które mają wirtualny destruktor. Dla pozostałych typów kompilator w ogóle nie widzi tej funkcji.
<!-- .element: class="fragment fade-in" -->

___
## `std::enable_if`

W C++11 znajduje się pomocnicza struktura metaprogramowania - `std::enable_if`. Jest to przełącznik czasu kompilacji do włączania lub wyłączania niektórych szablonów.
<!-- .element: class="fragment fade-in" -->

```cpp
template <bool Condition, class T = void>;
struct enable_if {};

template <class T>
struct enable_if<true, T> { using type = T; };
```
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> Jeśli <code>Condition</code> ma wartość <code>true</code>, dostęp do typu wewnętrznego przez <code>enable_if<Condition, T>::type</code> jest prawidłowy.
* <!-- .element: class="fragment fade-in" --> Jeśli <code>Condition</code> ma wartość <code>false</code>, dostęp do typu wewnętrznego przez <code>enable_if<Condition, T>::type</code> jest nieprawidłowy i podstawienie nie jest poprawne - SFINAE działa.

___

## `std::enable_if`

Wracając do przykładu

```cpp
template<
    class T,
    typename = std::enable_if<std::has_virtual_destructor_v<T>>::type
>
T* construct(T* t) {
    return new T{};
}
```

Odwołanie `std::enable_if<std::has_virtual_destructor_v<T>>::type`

* <!-- .element: class="fragment fade-in" --> jest prawidłowe, jeśli <code>std::has_virtual_destructor_v&lt;T&gt;</code> ma wartość <code>true</code>
* <!-- .element: class="fragment fade-in" --> jest nieprawidłowe, jeśli <code>std::has_virtual_destructor_v&lt;T&gt;</code> ma wartość <code>false</code>. Powoduje to wykluczenie funkcji <code>construct()</code> ze zbioru możliwych przeciążeń do wywołania. Jeśli była to jedyna pasująca funkcja to oczywiście dostaniemy błąd kompilacji.

___
<!-- .element: style="font-size: 0.9em" -->

## `std::enable_if_t`

<p>C++14 definiuje typ pomocniczy:</p>
<!-- .element: class="fragment fade-in" -->

```cpp []
template <bool B, class T = void>
using enable_if_t = typename enable_if<B, T>::type;
```
<!-- .element: class="fragment fade-in" -->

<p>Użycie obu jest równoważne.</p>
<!-- .element: class="fragment fade-in" -->

```cpp []
template <
    typename T,
    typename std::enable_if<std::is_integral<T>::value, T>::type* = nullptr
> void function(T& t) {}
```
<!-- .element: class="fragment fade-in" -->

```cpp []
template <
    typename T,
    typename std::enable_if_t<std::is_integral_v<T>, T>* = nullptr
> void function(T& t) {}
```
<!-- .element: class="fragment fade-in" -->

<p>Dlaczego <code>* = nullptr</code>?</p>
<!-- .element: class="fragment fade-in" -->

Note:

Show in IDE

```cpp
// function(4) generates this implicit instantiation
template <
    int,
    typename std::enable_if<std::is_integral<int>::value, int>::type* = nullptr
> void function(int& t) {}

template <
    int,
    int* = nullptr
> void function(int& t) {}
```

___

## Warianty `enable_if`

```cpp []
template<class T>     // #1 return type
auto construct(T* t) ->
typename std::enable_if_t<std::has_virtual_destructor_v<T>, T>*
{ return new T{}; }
```

```cpp []
template<class T>     // #2 parameter
T* construct(
    T* t,
    typename std::enable_if_t<std::has_virtual_destructor_v<T>>* = nullptr
) { return new T{}; }
```

```cpp []
template<
    class T,          // #3 template parameter - usual choice from C++11
    typename std::enable_if_t<std::has_virtual_destructor_v<T>>* = nullptr
> T* construct(T* t)
{ return new T{}; }
```

___

## Warianty `enable_if`

Najbardziej elegancka opcja

```cpp []
template <typename T>
using HasVirtDtor = std::enable_if_t<std::has_virtual_destructor_v<T>>;
```

```cpp []
template<
    class T,          // the same as #3 - template parameter
    typename = HasVirtDtor<T>
> T* construct(T* t)
{ return new T{}; }
```

___

## Koncepty (C++20)

```cpp
template <class T>
concept HasVirtualDtor = std::has_virtual_destructor_v<T>;

template <HasVirtualDtor T>
T* construct(T* t)
{ return new T{}; }
```

Od C++20 koncepty powinny zastąpić użycie `std::enable_if`.

___

## Zadanie

Zajrzyj do katalogu `02-advanced/shapes`.

Napisz funkcję `insert()` w pliku `main.cpp`. Powinna umożliwiać wstawianie do kolekcji tylko klas dziedziczących po `Shape`. Parametry inne niż `Circle`, `Square`  lub `Rectangle`  nie powinny się kompilować. Użyj SFINAE. Użyj odpowiednich type_traits.

Funkcja powinna utworzyć `shared_ptr` z obiektu przekazanego jako pierwszy parametr i umieścić go w kolekcji, która powinna zostać podana jako drugi parametr.

___

### Podpowiedzi

* `std::is_base_of`
* `std::remove_reference`
* `std::remove_cv`
* `std::decay`

___

## Rozwiązanie #1

```cpp
template <typename T>
using removeCvRef = std::remove_cv_t<std::remove_reference_t<T>>;

template <typename T>
using isBaseOfShape = std::enable_if_t<std::is_base_of_v<Shape, removeCvRef<T>>>;

template <
    class T,
    typename = isBaseOfShape<T>
>
void insert(T&& item, Collection& collection) {
    collection.emplace_back(make_shared<removeCvRef<T>>(item));
}
```
<!-- .element: class="fragment fade-in" style="font-size: 1.4rem" -->

___

## Rozwiązanie #2 (krótsze, lepsze)

```cpp
template <typename T>
using isBaseOfShape = std::enable_if_t<std::is_base_of_v<Shape, std::decay_t<T>>>;

template <
    class T,
    typename = isBaseOfShape<T>
>
void insert(T&& item, Collection& collection) {
    collection.emplace_back(make_shared<std::decay_t<T>>(item));
}
```
<!-- .element: class="fragment fade-in" style="font-size: 1.4rem" -->

___

## `if constexpr`

```cpp
template <class T>
void insertC(T&& item, Collection& collection) {
    if constexpr (std::is_base_of_v<Shape, std::decay_t<T>>) {
        collection.emplace_back(make_shared<std::decay_t<T>>(item));
    } else {
        std::cout << "Sorry\n";
    }
}
```
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> może zastąpić mechanizm SFINAE
* <!-- .element: class="fragment fade-in" --> dostępne od C++17
* <!-- .element: class="fragment fade-in" --> zazwyczaj wynikiem nie jest błąd podstawienia, ale pusty kod lub zawartość bloku <code>else</code>

___

## Podsumowanie

* <!-- .element: class="fragment fade-in" --> SFINAE to bardzo potężna i trudna technika
* <!-- .element: class="fragment fade-in" --> Właściwe użycie może nie być zbyt brzydkie 🥴
* <!-- .element: class="fragment fade-in" --> W stosownych przypadkach użyj poniższych technik zamiast SFINAE:
  * [tag dispatch](https://arne-mertz.de/2016/10/tag-dispatch/), użyte np. w [`std::advance`](https://en.cppreference.com/w/cpp/iterator/advance)
  * `static_assert` (C++11)
  * `if constexpr` (C++17)
  * koncepty (C++20)
