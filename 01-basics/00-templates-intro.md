<!-- .slide: data-background="#111111" -->

# Intro

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___

## Motywacja

**Szablony są używane aby unikać duplikacji kodu.**
<!-- .element: class="fragment fade-in" -->

Później odkryto, że szablony języka C++ są same w sobie kompletnym językiem programowania. Często pisanie programów za pomocą samych szablonów nazywa się **metaprogramowaniem**.
<!-- .element: class="fragment fade-in" -->

Wszystkie szablony są ewaluowane podczas fazy kompilacji.
<!-- .element: class="fragment fade-in" -->

W szablonach typy szablonowe są odpowiednikiem zmiennych.
<!-- .element: class="fragment fade-in" -->

___

## Obserwacja

* <!-- .element: class="fragment fade-in" --> Wiele programistów C/C ++ boi się szablonów, bo ich nie znają i nie wiedzą jak ich używać
* <!-- .element: class="fragment fade-in" --> Obwiniają oni szablony za:
  * <!-- .element: class="fragment fade-in" --> magiczne generowanie kodu
  * <!-- .element: class="fragment fade-in" --> potrzebę definiowania ich w plikach nagłówkowych
  * <!-- .element: class="fragment fade-in" --> zaśmiecanie kodu
  * <!-- .element: class="fragment fade-in" --> trudne do analizy błędy kompilatora
  * <!-- .element: class="fragment fade-in" --> problemy z debugowaniem kodu

* <!-- .element: class="fragment fade-in" --> Ci sami programiści zaskakująco dobrze czują się, gdy używają makr preprocesora
* <!-- .element: class="fragment fade-in" --> Makra preprocesora:
  * <!-- .element: class="fragment fade-in" --> generują kod
  * <!-- .element: class="fragment fade-in" --> muszą być zazwyczaj umieszczane w plikach nagłówkowych
  * <!-- .element: class="fragment fade-in" --> generują kod w miejscu użycia i powodują powielanie kodu w całej binarce
  * <!-- .element: class="fragment fade-in" --> generują błędy kompilatora w miejscach, w których ich nie oczekujesz
  * <!-- .element: class="fragment fade-in" --> są naprawdę trudne do debugowania

___

## Makra vs szablony

Oba są narzędziami do generowania kodu.
<!-- .element: class="fragment fade-in" -->

### Makra
<!-- .element: class="fragment fade-in" -->

```cpp
#define min(i, j)  (((i) < (j)) ? (i) : (j))
```
<!-- .element: class="fragment fade-in" -->

Prosty mechanizm zastępowania tekstu wykonywany podczas etapu preprocessingu (przed kompilacją)
<!-- .element: class="fragment fade-in" -->

### Szablony
<!-- .element: class="fragment fade-in" -->

```cpp
template<class T>
T min(T i, T j) { return (i < j) ? i : j; }
```
<!-- .element: class="fragment fade-in" -->

"Functional Turing complete feature-rich language". Szablony są ewaluowane w czasie kompilacji i są zintegrowane z systemem typów języka C++. Dzięki temu kod nie skompiluje się, gdy będą używane niewłaściwe typy.
<!-- .element: class="fragment fade-in" -->

___

### Problemy z makrami

* <!-- .element: class="fragment fade-in" --> Nie ma możliwości, aby kompilator sprawdził, czy parametry makra mają poprawne typy
* <!-- .element: class="fragment fade-in" --> Makra są rozwijane bez żadnego specjalnego sprawdzania typów
* <!-- .element: class="fragment fade-in" --> Parametry makr są ewaluowane wiele razy (w każdym miejscu użycia w kodzie)
* <!-- .element: class="fragment fade-in" --> Komunikaty błędów kompilatora będą odnosić się do rozwiniętego makra, a nie samej definicji makra
* <!-- .element: class="fragment fade-in" --> Są problemy z debugowaniem makr, gdy próbujemy wykonywać je instrukcja po instrukcji (single-stepping)

___

## Rodzaje szablonów

W C++03 mieliśmy

* <!-- .element: class="fragment fade-in" --> szablony funkcji
* <!-- .element: class="fragment fade-in" --> szablony klas

Od C++11 mamy także
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> szablony zmiennych
* <!-- .element: class="fragment fade-in" --> szablonowe aliasy

A od C++20 mamy także
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> szablonowe lambdy
