<!-- .slide: data-background="#111111" -->

# Templates

___

## Rationale

**Templates are used to avoid code duplication.**
<!-- .element: class="fragment fade-in" -->

Later it was discovered that C++ templates are a Turing-complete language. It means that the templates itself are a programming language. It is often called **C++ template metaprogramming**.
<!-- .element: class="fragment fade-in" -->

All templates are evaluated during compilation and only during that phase.
<!-- .element: class="fragment fade-in" -->

___

## Template types

In C++03 we could have

* <!-- .element: class="fragment fade-in" --> template classes
* <!-- .element: class="fragment fade-in" --> template functions

From C++11 we can also have
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> template variables

And from C++20 we will have
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> template lambdas

We will cover only template functions and classes here.
<!-- .element: class="fragment fade-in" -->
