<!-- .slide: data-background="#111111" -->

# Template template parameters
## Parametry szablonu szablonu

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___

## Przykład

<p>Chcemy użyć klasy szablonu jako argumentu szablonu.</p>
<!-- .element: class="fragment fade-in" -->

```cpp
template<typename T> class MyDeleter {};
template<typename T, typename Policy> class Handle { /* ... */ };
Handle<FILE, MyDeleter> h;
```
<!-- .element: class="fragment fade-in" style="font-size: 1.35rem" -->

<p>Powoduje to błąd kompilacji:</p>
<!-- .element: class="fragment fade-in" -->

`error: type/value mismatch at argument 2 in template parameter list for ‘template<class T, class Policy> class Handle’`
<!-- .element: class="fragment fade-in" style="font-size: 1.35rem" -->

<p>Próbowaliśmy przekazać szablon klasy zamiast określonej klasy (jak np. utworzona klasa szablonu). To powinno działać:</p>
<!-- .element: class="fragment fade-in" -->

```cpp
Handle<FILE, MyDeleter<FILE>> h;
```
<!-- .element: class="fragment fade-in" -->

___

## Szablon szablonu

<p>Aby umożliwić użycie klasy szablonu, musimy użyć tak zwanych argumentów <code>template template</code>.</p>
<!-- .element: class="fragment fade-in" -->

```cpp
template<typename T> class MyDeleter {};
template<typename T, template<typename> typename Policy> class Handle { /* ... */ };
// template<typename T, typename Policy> class Handle { /* ... */ };  // previously
Handle<FILE, MyDeleter> h;
```
<!-- .element: class="fragment fade-in" style="font-size: 1.35rem" -->

___

## Parametry szablonu szablonu

```cpp
template<template<parameter-list> typename|class name> declaration
template<template<parameter-list> typename|class> declaration

template<template<parameter-list> typename|class name = default> declaration
template<template<parameter-list> typename|class = default> declaration

template<template<parameter-list> typename|class ... name> declaration
template<template<parameter-list> typename|class ...> declaration
```

___

## Więcej przykładów

```cpp
template<typename T1, typename T2>
struct Pair {
    T1 val1;
    T2 val2;
};
```
<!-- .element: class="fragment fade-in" style="font-size: 1.3rem" -->

```cpp
template<size_t N, template<typename, typename> typename Data, typename T1, typename T2>
struct DataArray {
  std::array<Data<T1, T2>, N> data;
};
```
<!-- .element: class="fragment fade-in" style="font-size: 1.3rem" -->

```cpp
DataArray<16, Pair, int, double> a1;
a1.data[0].val1 = 4;
a1.data[0].val2 = 3.14;
DataArray<8, std::pair, std::string, std::string> a2;
a2.data[0].first = "Mickey";
a2.data[0].second = "Mouse";
```
<!-- .element: class="fragment fade-in" style="font-size: 1.3rem" -->

___

## Zadanie

1. Napisz szablon klasy `Holder`.
   1. <!-- .element: style="font-size: 0.7em" --> Klasa powinna mieć <code>vector<T></code> jako pole składowe.
   2. <!-- .element: style="font-size: 0.7em" --> Klasa powinna mieć konstruktor, który może przyjąć dowolny z 4 kolejnych kontenerów (<code>vector</code>, <code>list</code>, <code>forward_list</code>, <code>deque</code>). Ten konstruktor powinien skopiować wszystkie wartości do wektora wewnętrznego.
   3. <!-- .element: style="font-size: 0.7em" --> Parametr szablonu klasy <code>T</code> powinien zostać automatycznie wydedukowany. W razie potrzeby zadeklaruj podpowiedź dedukcyjną.

2. Dodaj funkcję print do drukowania zawartości wewnętrznego pola `vector<T>`

3. Dodaj obsługę `std::array<T, N>`. Konstruktor powinien umożliwiać kopiowanie zawartości do wektora wewnętrznego.

___

## Rozwiązanie #1 (łatwiejsze)

```cpp
template <typename T>
class Holder {
    std::vector<T> v_;
public:
    template <typename Container>
    Holder(const Container & c)
        : v_{c.begin(), c.end()}
    {}
    void print() {
        std::copy(v_.begin(), v_.end(), std::ostream_iterator<T>(std::cout, " "));
    }
};
template <typename Container>
Holder(const Container & c) -> Holder<typename Container::value_type>;
```
<!-- .element: class="fragment fade-in" style="font-size: 1.3rem" -->

* <!-- .element: class="fragment fade-in" --> Brak argumentów szablonu szablonu
* <!-- .element: class="fragment fade-in" --> Prosta podpowiedź dedukcyjna

___
<!-- .slide: style="font-size: 0.7em" -->
## Rozwiązanie #2

```cpp
template <typename T, template <typename...> typename Container>
class Holder {
    std::vector<T> v_;
public:
    Holder(const Container<T> & c)
        : v_{c.begin(), c.end()}
    {}
    template <size_t N>
    Holder(const std::array<T, N> & a)
        : v_{a.begin(), a.end()}
    {}
    void print() {
        std::copy(v_.begin(), v_.end(), std::ostream_iterator<T>(std::cout, " "));
    }
};
template <typename T, size_t N>
Holder(const std::array<T, N> & a) -> Holder<T, std::vector>;
```
<!-- .element: class="fragment fade-in" style="font-size: 1.3rem" -->

* <!-- .element: class="fragment fade-in" --> Argumenty szablonu szablonu
* <!-- .element: class="fragment fade-in" --> Dodatkowy konstruktor dla <code>std::array</code>
* <!-- .element: class="fragment fade-in" --> Dodatkowa i nieintuicyjna podpowiedź dedukcyjna dla tablicy
