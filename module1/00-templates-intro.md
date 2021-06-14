<!-- .slide: data-background="#111111" -->

# Templates

___

## Rationale

**Templates are used to avoid code duplication.**
<!-- .element: class="fragment fade-in" -->

Later it was discovered that C++ templates are a Turing-complete language. It means that the templates itself are a programming language. It is often called **C++ template meta-programming**.
<!-- .element: class="fragment fade-in" -->

All templates are evaluated during the compilation phase.
<!-- .element: class="fragment fade-in" -->

In templates types are something like variables.
<!-- .element: class="fragment fade-in" -->

___

## Observation

* <!-- .element: class="fragment fade-in" --> A lot of C/C++ developers are afraid of C++ templates and thus don't know them, their features and usage
* <!-- .element: class="fragment fade-in" --> They blame templates for:
  * <!-- .element: class="fragment fade-in" --> magically generating the code
  * <!-- .element: class="fragment fade-in" --> need of putting the most of them in the header files
  * <!-- .element: class="fragment fade-in" --> code bloat
  * <!-- .element: class="fragment fade-in" --> hard to analyze compiler errors
  * <!-- .element: class="fragment fade-in" --> problems with debugging the code

* <!-- .element: class="fragment fade-in" --> The same developers are also amazingly comfortable with using preprocessor macros
* <!-- .element: class="fragment fade-in" --> Preprocessor macros:
  * <!-- .element: class="fragment fade-in" --> are generating the code
  * <!-- .element: class="fragment fade-in" --> need to be put mostly in the header files
  * <!-- .element: class="fragment fade-in" --> generate the code in place causing code duplications all over the binary
  * <!-- .element: class="fragment fade-in" --> generate inscrutable compiler errors in places where you don't expect them
  * <!-- .element: class="fragment fade-in" --> are really hard to debug

___

## Macros vs templates

Both are code generation tools.
<!-- .element: class="fragment fade-in" -->

### Macros
<!-- .element: class="fragment fade-in" -->

```cpp
#define min(i, j)  (((i) < (j)) ? (i) : (j))
```
<!-- .element: class="fragment fade-in" -->

Simple text substitution mechanism done during preprocessing stage (before compilation)
<!-- .element: class="fragment fade-in" -->

### Templates
<!-- .element: class="fragment fade-in" -->

```cpp
template<class T>
T min(T i, T j) { return (i < j) ? i : j; }
```
<!-- .element: class="fragment fade-in" -->

Functional Turing complete feature-rich language that is executed at compile time and is integrated into the C++ type system
<!-- .element: class="fragment fade-in" -->

___

### Problems with macros

* <!-- .element: class="fragment fade-in" --> There is no way for the compiler to verify that the macro parameters are of compatible types
* <!-- .element: class="fragment fade-in" --> The macro is expanded without any special type checking
* <!-- .element: class="fragment fade-in" --> Macro parameters are evaluated many times (in every place they are put to the code)
* <!-- .element: class="fragment fade-in" --> Compiler error messages will refer to the expanded macro, rather than the macro definition itself
* <!-- .element: class="fragment fade-in" --> Problems with single-stepping macro code during debugging

___

## Template types

In C++03 we have had

* <!-- .element: class="fragment fade-in" --> template functions
* <!-- .element: class="fragment fade-in" --> template classes

From C++11 we can also have
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> template variables
* <!-- .element: class="fragment fade-in" --> template aliases

And from C++20 we can have
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> template lambdas
