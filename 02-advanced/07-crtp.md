<!-- .slide: data-background="#111111" -->

# CRTP

## Curiously Recurring Template Pattern

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___

## Dynamiczny polimorfizm

```cpp []
class Base {
    virtual void setup() = 0;
    virtual void run() = 0;
    virtual void cleanup() = 0;
public:
    virtual ~Base() = default;
    void process() {
        setup();
        run();
        cleanup();
    }
};

class Derived : public Base {
    void setup() override   { /* ... */ }
    void run() override     { /* ... */ }
    void cleanup() override { /* ... */ }
};
```

___

## Statyczny polimorfizm = CRTP

```cpp []
template<class Child>
class Base {
public:
  void process()
  {
    static_cast<Child*>(this)->setup();
    static_cast<Child*>(this)->run();
    static_cast<Child*>(this)->cleanup();
  }
};

class Derived : public Base<Derived> {  // CRTP
  friend class Base<Derived>;
  void setup()   { /* ... */ }
  void run()     { /* ... */ }
  void cleanup() { /* ... */ }
};
```

## 🤯
<!-- .element: class="fragment fade-in" -->

___

## CRTP

* <!-- .element: class="fragment fade-in" --> Curiously Recurring Template Pattern
* <!-- .element: class="fragment fade-in" --> Idiom w C++, w którym klasa <code>X</code> dziedziczy po instancji szablonu klasy bazowej, używając jednocześnie <code>X</code> jako argumentu szablonu klasy bazowej
* <!-- .element: class="fragment fade-in" --> Czasami nazywane „Upside-Down Inheritance” (Dziedziczenie do góry nogami) ze względu na sposób, w jaki umożliwia rozszerzanie hierarchii klas poprzez zastępowanie różnych klas podstawowych
* <!-- .element: class="fragment fade-in" --> "Polimorfizm" czasu kompilacji bez dodatkowych kosztów (bez <code>vtable</code>, <code>vptr</code>)
* <!-- .element: class="fragment fade-in" --> Za pomocą CRTP możemy zrealizowa wzorzec Mixin (domieszka), który rozszerza funkcjonalność danej klasy poprzez odziedziczenie odpowiedniego zestawu funkcji

___

## Zadanie 1

Zaimplementuj licznik obiektów danej klasy za pomocą CRTP.

Klasa `Counter` powinna posiadać 2 pola mówiące o tym ile obiektów danej klasy zostało utworzonych do tej pory, a ile zniszczonych.

Użyj kodu z zadania `02-advanced/shapes` i policz ile jest obiektów poszczególnych kształtów.

Pomyśl, czy można łatwo zaimplementować licznik wywołań metody. Możesz spróbować go zaimplementować.

___

## Zadanie 2

Zaimplementuj wzorzec projektowy [Prototyp](https://refactoring.guru/design-patterns/prototype) za pomocą CRTP.

Wzorzec Prototyp rozwiązuje problem, w którym obiektu nie można skopiować "z zewnątrz", ponieważ używamy go poprzez jakiś interfejs i nie wiemy jaki jest faktyczny typ obiektu.

W tym celu implementujemy metodę `clone()`, które zwraca kopię obiektu odpowiedniego typu. Użyj CRTP, aby dodać metodę `clone()` poprzez odziedziczenie odpowiedniej klasy bazowej.

Użyj kodu z zadania `02-advanced/shapes`. Jest tam kolekcja kształtów, która posiada wskaźniki na klasę bazową, a więc nie wiemy z jakim typem obiektu faktycznie mamy do czynienia.