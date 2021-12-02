<!-- .slide: data-background="#111111" -->

# Szablony klas

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___

## Przykład

Szablony klas są również używane w celu unikania duplikacji kodu lub aby utworzyć tak zwane meta-programy. Oto przykład prostej klasy szablonowej i jej użycie:
<!-- .element: class="fragment fade-in" -->

```c++
#include <iostream>

template <typename T, typename U>
class SomeClass {
public:
    T getValue() { return value; }
private:
    T value = {};
    U* ptr = nullptr;
};

int main() {
    SomeClass<int, void> sc;
    std::cout << sc.getValue() << std::endl;
    return 0;
}
```
<!-- .element: class="fragment fade-in" -->

___

## Klasy szablonowe w STLu

Klasy szablonowe są mocno używane w STLu. Na przykład `std::vector`, `std::list` i inne kontenery są klasami szablonowymi.
<!-- .element: class="fragment fade-in" -->

```c++
std::vector<int> v = {1, 2, 3};
std::list<char> l{'c', 'd', 'b'};
```
<!-- .element: class="fragment fade-in" -->

___
<!-- .slide: style="font-size: .95em" -->

## Dedukcja typów szablonowych dla klas (C++17)

Typy szablonowe również mogą być automatycznie wydedukowane przez kompilator dzięki... funkcjom szablonowym.
<!-- .element: class="fragment fade-in" -->

Kompilator w tym celu posługuje się konstruktorami klas.
<!-- .element: class="fragment fade-in" -->

Od C++17 możesz pisać kod w ten sposób:
<!-- .element: class="fragment fade-in" -->

```c++
std::vector v = {1, 2, 3};  // std::vector<int> is deduced
std::list l{'c', 'd', 'b'}; // std::list<char> is deduced
```
<!-- .element: class="fragment fade-in" -->

Ale to nie zadziała:
<!-- .element: class="fragment fade-in" -->

```cpp
// std::vector v1;          // compilation error, vector of what?
// std::vector v2(10)       // compilation error, 10 elements of what?
// clang error: no viable constructor or deduction guide for deduction of
//   template arguments of 'vector'
// g++ error: class template argument deduction failed:
//   no matching function for call to 'vector()'
```
<!-- .element: class="fragment fade-in" -->

___

## Zadanie - `VectorMap`

Napisz klasę szablonową `VectorMap`, która ma reprezentować przekombinowaną `std::map`.

Wewnątrz ma ona mieć 2 `std::vector` tego samego rozmiaru. Pierwszy vector będzie przechowywał klucze, a drugi wartości.

Elementy na tej samej pozycji w obu wektorach tworzą parę, tak jak `1` i `c` na poniższym przykładzie.

```c++
VectorMap<int, char> map;
map.insert(1, 'c');
map[1] = 'e';           // replaces value under 1
std::cout << map[1];    // prints 'e'
map.at(2);              // throw std::out_of_range
```

Zaimplementuj metody `insert()`, `operator[]`, `at()`.

Nie przejmuj się możliwymi duplikatami kluczy. To nie jest ważne w tym zadaniu.
Możesz za to zaimplementować dodatkowe metody z interfejsu `std::map` 🙂

Używaj [cppreference](http://en.cppreference.com/w/cpp/container/map).
