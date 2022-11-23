<!-- .slide: data-background="#111111" -->

# SFINAE

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___

## Prosty przykład SFINAE

```cpp []
template <typename T>
void foo(T arg) {}

template <typename T>
void foo(T* arg) {}
```

Wywołanie `foo(42)` spowoduje, że kompilator spróbuje wygenerować 2 funkcje.
<!-- .element: class="fragment fade-in" -->

```cpp []
void foo(int arg) {}
void foo(int* arg) {}
```

Gdyby kompilator podstawił `42` jako argument drugiej funkcji, spowodowałoby to błąd kompilacji. Wobec tego odrzuca on to przeciążenie.
<!-- .element: class="fragment fade-in" -->

Ostatecznie nie ma żadnego błędu kompilacji, bo udało się dopasować pierwszą funkcję. Tada! Oto właśnie SFINAE w praktyce.
<!-- .element: class="fragment fade-in" -->

Gdyby nie było pierwszej funkcji, dostalibyśmy błąd kompilacji.
<!-- .element: class="fragment fade-in" -->

___

## SFINAE

Substitution Failure Is Not An Error - to technika meta-programowania.
<!-- .element: class="fragment fade-in" -->

> This rule applies during overload resolution of function templates: When substituting the explicitly specified or deduced type for the template parameter fails, the specialization is discarded from the overload set instead of causing a compile error.
>
> -- <a href="https://en.cppreference.com/w/cpp/language/sfinae">cppreference.com</a>
<!-- .element: class="fragment fade-in" -->

### Co nam to daje?
<!-- .element: class="fragment fade-in" -->

Możemy mieć uniwersalny interfejs i to my jako twórcy kodu (biblioteki) decydujemy, która implementacja ma się wykonać. Kompilator może więc wybrać optymalną implementację w zależności od typu danych.
<!-- .element: class="fragment fade-in" -->

___

## Biblioteka `type_traits`

<a href="https://en.cppreference.com/w/cpp/header/type_traits"><type_traits> on cppreference.com</a>

___

## `std::enable_if`

C++11 has a metaprogramming helper struct - `std::enable_if`. It is a compile-time switch for enabling or disabling some templates.

```cpp
template <bool Condition, class T = void>;
struct enable_if {};

template <class T>
struct enable_if<true, T> { using type = T; };
```
<!-- .element: class="fragment fade-in" -->


* If `Condition` is `true`, accessing internal type by `enable_if<Condition, T>::type` is valid.
* If `Condition` is `false`, accessing internal type by `enable_if<Condition, T>::type` is invalid and substitution is not correct - SFINAE works.


___

## `std::enable_if_t`

C++14 defines a helper type:

```cpp []
template <bool B, class T = void>
using enable_if_t = typename enable_if<B, T>::type;
```

Using both is equivalent.

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

Why `* = nullptr`?

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

## `enable_if` variations

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

## `enable_if` variations

The most elegant way

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

## Concepts (C++20)

```cpp
template <class T>
concept HasVirtualDtor = std::has_virtual_destructor_v<T>;

template <HasVirtualDtor T>
T* construct(T* t)
{ return new T{}; }
```

From C++20 concepts should replace the usage of `std::enable_if`.

___

## Task

Take a look into `module2/shapes` directory.

Write an `insert()` function in `main.cpp`. It should allow inserting only subclasses of Shape to the collection. Parameters other than `Circle`, `Square` or `Rectangle` should not compile. Use SFINAE. Use proper type_traits.

The function should create a `shared_ptr` from the object passed as the first parameter and put it in the collection, which should be provided as the second parameter.

Hints:

* `std::is_base_of`
* `std::remove_reference`
* `std::remove_cv`

___

## Solution

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

## `if constexpr`

```cpp
template <typename T>
using removeCvRef = std::remove_cv_t<std::remove_reference_t<T>>;

template <class T>
void insertC(T&& item, Collection& collection) {
    if constexpr (std::is_base_of_v<Shape, removeCvRef<T>>) {
        collection.emplace_back(make_shared<removeCvRef<T>>(item));
    } else {
        std::cout << "Sorry\n";
    }
}
```
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> can replace SFINAE mechanism
* <!-- .element: class="fragment fade-in" --> available from C++17
* <!-- .element: class="fragment fade-in" --> the result is not a substitution error, but usually empty code

___

## Conclusions

* <!-- .element: class="fragment fade-in" --> SFINAE is a very powerful and difficult technique
* <!-- .element: class="fragment fade-in" --> Proper usage may not be too ugly 🥴
* <!-- .element: class="fragment fade-in" --> Where applicable, use below techniques instead of SFINAE:
  * [tag dispatch](https://arne-mertz.de/2016/10/tag-dispatch/)
  * `static_assert` (C++11)
  * `if constexpr` (C++17)
  * concepts (C++20)
