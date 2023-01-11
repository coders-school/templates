<!-- .slide: data-background="#111111" -->

# Overload resolution rules

## Reguły rozwiązywanie przeciążeń

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___

## Overload resolution

```cpp []
void foo(unsigned i) {
    std::cout << "unsigned " << i << "\n";
}

template <typename T>
void foo(const T& t) {
    std::cout << "template " << t << "\n";
}
```

Jaki jest wynik wywołania `foo(42)`?
<!-- .element: class="fragment fade-in" -->

`template 42`
<!-- .element: class="fragment fade-in" -->

Czemu `const int &` jest lepszym dopasowaniem niż  `unsigned`?
<!-- .element: class="fragment fade-in" -->

Przy dopasowaniu typu w szablonach nie może zajść konwersja. Stała referencja złapie r-value (jest nim `42`) i będzie to lepszym wyborem (exact match) niż konwersja z `int` na `unsigned`.
<!-- .element: class="fragment fade-in" -->

___

## Overload resolution

```cpp []
void foo(unsigned i) {
    std::cout << "unsigned " << i << "\n";
}

template <typename T>
void foo(T& t) {
    std::cout << "template " << t << "\n";
}
```

Jaki teraz będzie wynik wywołania `foo(42)`?
<!-- .element: class="fragment fade-in" -->

`unsigned 42`
<!-- .element: class="fragment fade-in" -->

Dlaczego `unsigned` jest lepszym wyborem niż `int &`?
<!-- .element: class="fragment fade-in" -->

Referencja (non-const) nie łapie r-values (obiektów tymczasowych). Mamy więc tylko jeden wybór. Zajdzie niejawna konwersja z `int` na `unsigned`.
<!-- .element: class="fragment fade-in" -->

___

## Overload resolution

```cpp []
void foo(unsigned i) {
    std::cout << "unsigned " << i << "\n";
}

void foo(double i) {
    std::cout << "double " << i << "\n";
}
```

Jaki teraz będzie wynik wywołania `foo(42)`?
<!-- .element: class="fragment fade-in" -->

`error: call of overloaded ‘foo(int)’ is ambiguous`
<!-- .element: class="fragment fade-in" -->

Dlaczego?
<!-- .element: class="fragment fade-in" -->

Promocja na `double` i konwersja na `unsigned` mają taki sam priorytet, więc kompilator nie wie co wybrać.
<!-- .element: class="fragment fade-in" -->

___

## Przeciążenia funkcji vs specjalizacje funkcji szablonowych

```cpp
template<class T> void f(T);    // #1: overload for all types
template<>        void f(int*); // #2: specialization of #1 for pointers to int
template<class T> void f(T*);   // #3: overload for all pointer types

f(new int{1});
```
<!-- .element: class="fragment fade-in" style="font-size: 1.3rem" -->

### Która wersja funkcji `f` zostanie wywołana?
<!-- .element: class="fragment fade-in" -->
### #3
<!-- .element: class="fragment fade-in" -->

Dlaczego?
<!-- .element: class="fragment fade-in" -->

Specjalizacje szablonów nie biorą udziału w pierwszej fazie procesu overload resolution.
<!-- .element: class="fragment fade-in" -->

Pomimo tego, że #2 wydaje się być idealnym dopasowaniem, to jest to specjalizacja szablonu #1, który jest gorszym dopasowaniem niż szablon #3.
<!-- .element: class="fragment fade-in" -->

___

## Zasady rozwiązywania przeciążeń

* <!-- .element: class="fragment fade-in" --> Tylko funkcje nie szablonowe oraz szablony główne uczestniczą w procesie rozwiązywania przeciążeń
* <!-- .element: class="fragment fade-in" --> Specjalizacje nie są przeciążeniami i nie są brane pod uwagę
* <!-- .element: class="fragment fade-in" --> Dopiero po zakończeniu procesu rozwiązywania przeciążeń dostajemy najlepiej pasującą funkcję. Jeśli jest to funkcja szablonowa, to sprawdzamy czy jej specjalizacje nie będą lepszym dopasowaniem.

___

## Zmieńmy kolejność

```cpp
template<class T> void f(T);    // #1: overload for all types
template<class T> void f(T*);   // #3: overload for all pointer types
template<>        void f(int*); // #2: now, it's a specialization of #3

f(new int{1});
```
<!-- .element: style="font-size: 1.3rem" -->

### Która wersja funkcji `f` zostanie teraz wywołana?

#### #2
<!-- .element: class="fragment fade-in" -->