<!-- .slide: data-background="#111111" -->

# Overload resolution

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___

## Template instantiation

* <!-- .element: class="fragment fade-in" --> Template by itself is not a type, or an object, or a function, or any other entity
* <!-- .element: class="fragment fade-in" --> No code is generated from a source file that contains only template definitions
* <!-- .element: class="fragment fade-in" --> In order for any code to appear, a template must be instantiated so that the compiler can generate an actual entity and its implementation

<span class="fragment highlight-green">The definition of a template must be visible at the point of implicit instantiation, which is why template libraries typically provide all template definitions in the headers.</span>
<!-- .element: class="fragment fade-in" -->

___

## Overload resolution

Selecting the right function to call consist of a few steps.
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> Candidate functions (+)
* <!-- .element: class="fragment fade-in" --> Viable functions (-)
* <!-- .element: class="fragment fade-in" --> Implicit conversions (+)
* <!-- .element: class="fragment fade-in" --> Best viable function (-)

After this process compiler has chosen the winner function. The linker knows which function should it be linked against.
<!-- .element: class="fragment fade-in" -->

___

## Candidate functions

Candidate functions are selected by the name lookup process.
<!-- .element: class="fragment fade-in" -->

Name lookup:
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> ADL (Argument Dependent Lookup)
* <!-- .element: class="fragment fade-in" --> Template Argument Deduction -> implicit specializations are generated

If name lookup produce more than one candidate function, the overload resolution is performed to select the function that will actually be called.
<!-- .element: class="fragment fade-in" -->

___

## So templates are overloading, right?

Yes and no.
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> Function templates participate in name resolution for overloaded functions, but the rules are different.
* <!-- .element: class="fragment fade-in" --> For a template to be considered in overload resolution, the type has to match exactly.
* <!-- .element: class="fragment fade-in" --> If the types do not match exactly, the conversions are not considered and the template is simply dropped from the set of viable functions.
* <!-- .element: class="fragment fade-in" --> That’s what is known as “SFINAE” — Substitution Failure Is Not An Error.

___

## SFINAE - example

```cpp []
#include <iostream>
#include <typeinfo>

template<typename T>
void foo(T* x)     { std::cout << "foo<" << typeid(T).name() << ">(T*)\n"; }
void foo(int x)    { std::cout << "foo(int)\n"; }
void foo(double x) { std::cout << "foo(double)\n"; }
```

### Which functions are called?
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

## Function overloads vs function specializations

```cpp
template<class T> void f(T);    // #1: overload for all types
template<>        void f(int*); // #2: specialization of #1 for pointers to int
template<class T> void f(T*);   // #3: overload for all pointer types
```
<!-- .element: class="fragment fade-in" -->

### Which function is called?
<!-- .element: class="fragment fade-in" -->

```cpp
f(new int{1});
```
<!-- .element: class="fragment fade-in" -->

Calls #3, even though specialization of #1 would be a perfect match
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> Only non-template and primary template overloads participate in overload resolution
* <!-- .element: class="fragment fade-in" --> The specializations are not overloads and are not considered
* <!-- .element: class="fragment fade-in" --> Only after the overload resolution selects the best-matching primary function template, its specializations are examined to see if one is a better match

___

## More information

[Overload resolution rules on cppreference.com](https://en.cppreference.com/w/cpp/language/overload_resolution)
