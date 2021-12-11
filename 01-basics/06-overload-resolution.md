<!-- .slide: data-background="#111111" -->

# Overload resolution

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___

## Instancjonowanie szablonów

* <!-- .element: class="fragment fade-in" --> Szablon sam z siebie nie jest typem, ani obiektem, ani funkcją ani nawet kodem programu
* <!-- .element: class="fragment fade-in" --> Żaden kod nie zostanie wygenerowany jeśli szablon nie zostanie użyty (np. gdy kompilujesz plik w którym jest tylko definicja szablonu)
* <!-- .element: class="fragment fade-in" --> Aby kompilator wygenerował kod, szablon musi zostać użyty z konkretnym typem. Dopiero wtedy kompilator generuje "instancję szablonu"

<span class="fragment highlight-green">Definicja szablonu musi być widoczna w miejscach, gdzie ich używamy. Dlatego szablony definiuje się w nagłówkach (<code>hpp</code>) i dołącza w każdym miejscu ich użycia. Gdyby ich implementacje były w plikach źródłowych (<code>cpp</code>) to kompilator wygenerowałby same definicje bez implementacji i mielibyśmy błąd linkera.</span>
<!-- .element: class="fragment fade-in" -->

### [cppinsights.io](https://cppinsights.io)
<!-- .element: class="fragment fade-in" -->

___

## Overload resolution

Wybór odpowiedniej funkcji do wywołania składa się z kilku kroków.
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> Candidate functions (+)
* <!-- .element: class="fragment fade-in" --> Viable functions (-)
* <!-- .element: class="fragment fade-in" --> Implicit conversions (+)
* <!-- .element: class="fragment fade-in" --> Best viable function (-)

Po tym procesie, kompilator wybrał jedną zwycięską funkcję. Dzięki temu linker wie, z którą implementacją funkcji powinien powiązać jej wywołanie.
<!-- .element: class="fragment fade-in" -->

___

## Candidate functions

Funkcje kandydujące są wybierane podczas procedury "name lookup".
<!-- .element: class="fragment fade-in" -->

Name lookup:
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> ADL (Argument Dependent Lookup)
* <!-- .element: class="fragment fade-in" --> Template Argument Deduction -> kompilator niejawnie generuje specjalizacje

Jeśli proces "name lookup" wyprodukuje więcej niż jedną funkcję kandydującą, następuje właściwy proces "overload resolution", czyli wyboru najlepszej funkcji do wywołania.
<!-- .element: class="fragment fade-in" -->

___

## A więc szablony są przeciążeniami, prawda?

I tak, i nie.
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> Szablony funkcji uczestniczą w procesie "overload resolution" ale reguły dla nich są inne.
* <!-- .element: class="fragment fade-in" --> Aby szablon funkcji w ogóle został rozważony to musi to być dokładne dopasowanie. Kompilator nie próbuje robić konwersji.
* <!-- .element: class="fragment fade-in" --> Jeśli typy <span class="fragment highlight-green">nie pasują idealnie, to kompilator nie próbuje robić konwersji, aby je dopasować</span>, więc szablon jest po prostu odrzucany z grupy możliwych kandydatów.
* <!-- .element: class="fragment fade-in" --> Jest to znane pod nazwą “SFINAE” — Substitution Failure Is Not An Error.

___

## SFINAE - przykład

```cpp []
#include <iostream>
#include <typeinfo>

template<typename T>
void foo(T* x)     { std::cout << "foo<" << typeid(T).name() << ">(T*)\n"; }
void foo(int x)    { std::cout << "foo(int)\n"; }
void foo(double x) { std::cout << "foo(double)\n"; }
```

### Które funkcje zostaną wywołane?
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> <code>foo(42)</code>
  * <!-- .element: class="fragment fade-in" --> matches <code>foo(int)</code> exactly
  * <!-- .element: class="fragment fade-in" --> for <code>foo&lt;T&gt;(T*)</code> there is a substitution failure
* <!-- .element: class="fragment fade-in" --> <code>foo(42.0)</code>
  * <!-- .element: class="fragment fade-in" --> matches <code>foo(double)</code> exactly
  * <!-- .element: class="fragment fade-in" --> for <code>foo&lt;T&gt;(T*)</code> there is a substitution failure
* <!-- .element: class="fragment fade-in" --> <code>foo("abcdef")</code>
  * <!-- .element: class="fragment fade-in" --> matches <code>foo&lt;T&gt;(T*) with T = char</code> and it wins

___

## Przeciążenia funkcji vs specjalizacje

```cpp
template<class T> void f(T);    // #1: overload for all types
template<>        void f(int*); // #2: specialization of #1 for pointers to int
template<class T> void f(T*);   // #3: overload for all pointer types
```
<!-- .element: class="fragment fade-in" -->

### Która funkcja zostanie wywołana?
<!-- .element: class="fragment fade-in" -->

```cpp
f(new int{1});
```
<!-- .element: class="fragment fade-in" -->

#3, pomimo tego, że #2 (która jest specjalizacją #1) jest idealnym dopasowaniem 🤯
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> Tylko GŁÓWNE SZABLONY i funkcje nieszablonowe uczestniczą w procesie "overload resolution"
* <!-- .element: class="fragment fade-in" --> Specjalizacje nie są przeciążeniami i nie są brane pod uwagę
* <!-- .element: class="fragment fade-in" --> Dopiero po tym, gdy "overload resolution" wybierze, że najlepiej pasuje główny szablon, to badane są jego specjalizacje, aby sprawdzić, czy któraś nie będzie lepszym dopasowaniem

___

## Ogólna zasada
<!-- .element: class="fragment fade-in" -->

Jeśli to możliwe, twórz przeciążenia funkcji, a nie specjalizacje.
<!-- .element: class="fragment fade-in" -->

___

## Więcej info

[Overload resolution rules na cppreference.com](https://en.cppreference.com/w/cpp/language/overload_resolution)
