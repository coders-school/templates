<!-- .slide: data-background="#111111" -->

# CRTP

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

___

## CRTP

* <!-- .element: class="fragment fade-in" --> Curiously Recurring Template Pattern
* <!-- .element: class="fragment fade-in" --> Idiom w C++, w którym klasa X wywodzi się z instancji szablonu klasy, używając samego X jako argumentu szablonu
* <!-- .element: class="fragment fade-in" --> Czasami nazywane „Upside-Down Inheritance” (Dziedziczenie do góry nogami) ze względu na sposób, w jaki umożliwia rozszerzanie hierarchii klas poprzez zastępowanie różnych klas podstawowych
* <!-- .element: class="fragment fade-in" --> Polimorfizm czasu kompilacji bez dodatkowych kosztów (bez <code>vtable</code>, <code>vptr</code>)
