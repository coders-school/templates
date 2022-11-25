<!-- .slide: data-background="#111111" -->

# SFINAE

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___

## Prosty przykład SFINAE

<pre class="fragment"><code class="cpp" data-trim>
template <typename T>
void foo(T arg) {}

template <typename T>
void foo(T* arg) {}
</code></pre>
<!-- .element: class="fragment fade-in" -->

Wywołanie `foo(42)` spowoduje, że kompilator spróbuje wygenerować 2 funkcje.
<!-- .element: class="fragment fade-in" -->

<pre class="fragment"><code class="cpp" data-trim>
void foo(int arg) {}
void foo(int* arg) {}
</code></pre>
<!-- .element: class="fragment fade-in" -->

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

<a href="https://en.cppreference.com/w/cpp/header/type_traits">&lt;type_traits&gt; on cppreference.com</a>

___

## `std::enable_if`

<p>W C++11 znajduje się pomocnicza struktura metaprogramowania - `std::enable_if`. Jest to przełącznik czasu kompilacji do włączania lub wyłączania niektórych szablonów.</p>
<!-- .element: class="fragment fade-in" -->

<pre class="fragment"><code class="cpp" data-trim>
template <bool Condition, class T = void>;
struct enable_if {};

template <class T>
struct enable_if<true, T> { using type = T; };
</code></pre>
<!-- .element: class="fragment fade-in" -->


* <!-- .element: class="fragment fade-in" --> Jeśli <code>Condition</code> ma wartość <code>true</code>, dostęp do typu wewnętrznego przez <code>enable_if<Condition, T>::type</code> jest prawidłowy.
* <!-- .element: class="fragment fade-in" --> Jeśli <code>Condition</code> ma wartość <code>false</code>, dostęp do typu wewnętrznego przez <code>enable_if<Condition, T>::type</code> jest nieprawidłowy i podstawienie nie jest poprawne - SFINAE działa.

___

## `std::enable_if_t`

<p>C++14 definiuje typ pomocniczy:</p>
<!-- .element: class="fragment fade-in" -->

<pre class="fragment"><code class="cpp" data-trim>
template <bool B, class T = void>
using enable_if_t = typename enable_if<B, T>::type;
</code></pre>
<!-- .element: class="fragment fade-in" -->

<p>Użycie obu jest równoważne.</p>
<!-- .element: class="fragment fade-in" -->

<pre class="fragment"><code class="cpp" data-trim>
template <
    typename T,
    typename std::enable_if<std::is_integral<T>::value, T>::type* = nullptr
> void function(T& t) {}
</code></pre>
<!-- .element: class="fragment fade-in" -->

<pre class="fragment"><code class="cpp" data-trim>
template <
    typename T,
    typename std::enable_if_t<std::is_integral_v<T>, T>* = nullptr
> void function(T& t) {}
</code></pre>
<!-- .element: class="fragment fade-in" -->

Dlaczego `* = nullptr`?

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

## warianty `enable_if`

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

## variations `enable_if`

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

## Koncepcje (C++20)

```cpp
template <class T>
concept HasVirtualDtor = std::has_virtual_destructor_v<T>;

template <HasVirtualDtor T>
T* construct(T* t)
{ return new T{}; }
```

Od C++20 koncepcje powinny zastąpić użycie `std::enable_if`.

___

## Zadanie

Zajrzyj do katalogu `module2/shapes`.

Napisz funkcję `insert()` w pliku `main.cpp`. Powinna umożliwiać wstawianie do kolekcji tylko podklas Shape. Parametry inne niż `Circle`, `Square`  lub `Rectangle`  nie powinny się kompilować. Użyj SFINAE. Użyj odpowiednich type_traits.

Funkcja powinna utworzyć `shared_ptr` z obiektu przekazanego jako pierwszy parametr i umieścić go w kolekcji, która powinna zostać podana jako drugi parametr.

Podpowiedzi:

* `std::is_base_of`
* `std::remove_reference`
* `std::remove_cv`

___

## Rozwiązanie

<pre class="fragment"><code class="cpp" data-trim>
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
</code></pre>
<!-- .element: class="fragment fade-in" style="font-size: 1.4rem" -->

___

## `if constexpr`

<pre class="fragment"><code class="cpp" data-trim>
template <typename T>
using removeCvRef = std::remove_cv_t<std::remove_reference_t<T>>;

template <class T>
void insertC(T&& item, Collection& collection) {
    if constexpr (std::is_base_of_v<Shape, removeCvRef<T>>) {
        collection.emplace_back(make_shared<removeCvRef<T>>(item));
    } else {
        std::cout <<code "Sorry\n";
    }
}
</code></pre>
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> może zastąpić mechanizm SFINAE
* <!-- .element: class="fragment fade-in" --> dostępne od C++17
* <!-- .element: class="fragment fade-in" --> zazwyczaj wynikiem nie jest błąd podstawienia, ale pusty kod

___

## Podsumowanie

* <!-- .element: class="fragment fade-in" --> SFINAE to bardzo potężna i trudna technika
* <!-- .element: class="fragment fade-in" --> Właściwe użycie może nie być zbyt brzydkie 🥴
* <!-- .element: class="fragment fade-in" --> W stosownych przypadkach użyj poniższych technik zamiast SFINAE:
  * [tag dispatch](https://arne-mertz.de/2016/10/tag-dispatch/)
  * `static_assert` (C++11)
  * `if constexpr` (C++17)
  * koncepcje (C++20)
