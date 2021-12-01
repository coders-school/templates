<!-- .slide: data-background="#111111" -->

# Szablony funkcji

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___
<!-- .slide: style="font-size: 0.9em" -->

## Przykłady

Załóżmy, że mamy poniższą funkcję:

```c++
int add(int first, int second) {
    return first + second;
}
```

Jeśli chcemy mieć funkcję, która robi to samo dla typu `double`, musimy napisać jej przeciążenie.
<!-- .element: class="fragment fade-in" -->

```c++
double add(double first, double second) {
    return first + second;
}
```
<!-- .element: class="fragment fade-in" -->

I jeśli chcemy mieć funkcję, która robi to samo dla liczb zespolonych, musimy napisać kolejne przeciążenie.
<!-- .element: class="fragment fade-in" -->

```c++
std::complex<int> add(std::complex<int> first, std::complex<int> second) {
    return first + second;
}
```
<!-- .element: class="fragment fade-in" -->

"Łatwo" widać, że mamy tutaj duplikację kodu.
<!-- .element: class="fragment fade-in" -->

___

## Unikanie duplikacji

Zamiast pisać wiele wersji funkcji możemy napisać jedną - funkcję szablonową.

```c++
template <typename Type>
Type add(Type first, Type second) {
    return first + second;
}
```
<!-- .element: class="fragment fade-in" -->

Zamiast `Type`, możesz nadać dowolną nazwę typu. Zazwyczaj zobaczysz `T`, ale lepiej mieć dłuższą nazwę niż tylko jeden znak, zwłaszcza, gdy jest więcej niż tylko jeden parametr szablonu. Funkcji szablonowej możesz teraz używać w następujący sposób.
<!-- .element: class="fragment fade-in" -->

```c++
auto resultI = add<int>(4, 5);  // resultI type is int
auto resultD = add<double>(4.0, 5.0);  // resultD type is double
auto resultC = add<std::complex<int>>({1, 2}, {2, 3});  // resultC type is std::complex<int>
```
<!-- .element: class="fragment fade-in" -->

[Tutaj](https://ideone.com/fork/NU0L8k) możesz się pobawić tym kodem.
<!-- .element: class="fragment fade-in" -->

___

## Dedukcja typów funkcji szablonowej

W C++ mamy mechanizm automatycznej dedukcji typów szablonowych na podstawie parametrów funkcji. To oznacza, że można pominąć część z nawiasami trójkątnymi `<>`.

```c++
auto resultI = add(4, 5);  // resultI type is int
auto resultD = add(4.0, 5.0);  // resultD type is double
auto resultC = add({1, 2}, {2, 3});  // error, does not compile
```

`resultC` nie skompiluje się jednak w tym przypadku, ponieważ kompilator przyjmie, że typ `{1, 2}` oraz `{2, 3}` to `std::initializer_list`. Ten typ nigdy nie może być wynikiem dedukcji typu szablonowego.
W tym przypadku musimy jawnie zapisać typ:
<!-- .element: class="fragment fade-in" -->

```c++
auto resultC = add(std::complex<int>{1, 2}, std::complex<int>{2, 3});
```
<!-- .element: class="fragment fade-in" -->

lub
<!-- .element: class="fragment fade-in" -->

```c++
auto resultC = add<std::complex<int>>({1, 2}, {2, 3});
```
<!-- .element: class="fragment fade-in" -->

___

## Zadanie

Napisz funkcję `makeComplex()`, która tworzy liczbę zespoloną `std::complex` z dwóch dostarczonych liczb. Jeśli typy tych liczb są różne, powinna utworzyć się liczba zespolona z typem pierwszego parametru.

```c++
std::complex<int> a = makeComplex(4, 5);        // both ints
std::complex<double> b = makeComplex(3.0, 2.0); // both doubles
std::complex<int> c = makeComplex(1, 5.0); // int, double -> takes int
```

___
<!-- .slide: style="font-size: 0.8em" -->

## Wiele parametrów szablonowych

Kompilator sam z siebie dedukuje parametry szablonowe. Ale... jeśli napiszesz taki kod jak poniżej, będzie błąd kompilacji.

```c++
auto resultC = add(4, 5.0);  // error: int + double
```
<!-- .element: class="fragment fade-in" -->

Kompilator nie potrafi wydedukować parametru, ponieważ funkcja `add()` przyjmuje tylko jeden parametr szablonowy i oba jej argumenty muszą być tego samego typu. Możemy to zmienić dodając nową wersję funkcji szablonowej `add()`
<!-- .element: class="fragment fade-in" -->

```c++
template <typename TypeA, typename TypeB>
TypeA add(TypeA first, TypeB second) {
    return first + second;
}
```
<!-- .element: class="fragment fade-in" -->

Teraz ten kod się skompiluje
<!-- .element: class="fragment fade-in" -->

```c++
auto resultC = add(4, 5.0);  // resultC type is int
```
<!-- .element: class="fragment fade-in" -->

Typ zwracany przez tę funkcję jest taki sam, jak typ pierwszego argumentu, bo tak zapisaliśmy w szablonie. Jest to typ `TypeA`.
<!-- .element: class="fragment fade-in" -->

___
<!-- .slide: style="font-size: 0.8em" -->
## `typeid`

Ogólnie rzecz biorąc, można dowolnie używać typów szablonowych wewnątrz funkcji. Na przykład można utworzyć nowe zmienne typów szablonowych:

```cpp
#include <typeinfo>

template <class T>
void showType() {
    T value;
    std::cout << "Type: " << typeid(value).name() << std::endl;
}
```
<!-- .element: class="fragment fade-in" -->

Możesz użyć `typeid().name()` aby wypisać typ zmiennej. Trzeba dołączyć nagłówek `typeinfo`. Jednak to co pojawi się na ekranie jest zależne od implementacji kompilatora. Nie zaleca się używania `typeid` do porównywania typów. Później pokażę Ci `type_traits`, które do tego służą.
<!-- .element: class="fragment fade-in" -->

Możesz też zauważyć, że zamiast słowa kluczowego `typename`, użyliśmy słowa `class`. Można je stosować zamiennie i nie ma między nimi absolutnie żadnej różnicy.
<!-- .element: class="fragment fade-in" -->

```cpp
template <typename T> == template <class T> != template <struct T>
```
<!-- .element: class="fragment fade-in" -->

___
<!-- .slide: style="font-size: .9em" -->

## No matching function

Jeśli chcemy użyć funkcji `showType()` z poprzedniego slajdu bez jawnego podania typu szablonowego, kod się nie skompiluje. Mam nadzieję że wiesz dlaczego 🙂

```c++
int main() {
    showType();
    return 0;
}
```

```bash
prog.cpp: In function ‘int main()’:
prog.cpp:15:12: error: no matching function for call to showType()’
  showType();
           ^
prog.cpp:7:6: note: candidate: template<class T> void showType()
 void showType()
      ^~~~~~~~~
prog.cpp:7:6: note:   template argument deduction/substitution failed:
prog.cpp:15:12: note:   couldn't deduce template parameter ‘T’
  showType();
```

___

## Dedukcja typów szablonowych dla funkcji

Kompilator nie może wydedukować parametrów, ponieważ funkcja nie przyjmuje żadnych parametrów. Musisz podać typ jawnie:

```c++
int main() {
    showType<int>();
    return 0;
}
```
<!-- .element: class="fragment fade-in" -->

lub np.
<!-- .element: class="fragment fade-in" -->

```c++
int main() {
    showType<std::vector<char>>();
    return 0;
}
```
<!-- .element: class="fragment fade-in" -->

[Tutaj](https://ideone.com/fork/oZZybw) możesz pobawić się tym kodem.
<!-- .element: class="fragment fade-in" -->

___

## Przykłady szablonów z STL

```cpp
template<class InputIt, class UnaryPredicate>
InputIt find_if(InputIt first, InputIt last, UnaryPredicate p)
{
    for(; first != last; ++first) {
        if(p(*first)) {
            return first;
        }
    }
    return last;
}
```

```cpp
std::vector<std::pair<int, int>> v{{-3, 1}, {2, 3}, {4, -5}};
auto it = std::find_if(begin(v), end(v), [](auto& e){ return e.first == 2; });
if(it != std::end(v)) {
    /* ... */
}
```
<!-- .element: class="fragment fade-in" -->
