<!-- .slide: data-background="#111111" -->

# CRTP

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___

## Dynamic polymorphism

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

## Static polymorphism = CRTP

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
* <!-- .element: class="fragment fade-in" --> An idiom in C++ in which a class X derives from a class template instantiation using X itself as a template argument
* <!-- .element: class="fragment fade-in" --> Sometimes called "Upside-Down Inheritance" due to the way it allows class hierarchies to be extended by substituting different base classes
* <!-- .element: class="fragment fade-in" --> Compile time polymorphism at no extra cost (no vtable, no vptr)
