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

## Template instantiation

```cpp
template<typename T>
class Foo {
public:
    Foo();
    void someMethod(T x);
private:
    T x;
};
```

Along with similar definitions for the member functions:

```cpp
template<typename T>
Foo<T>::Foo()
{
    // ...
}
template<typename T>
void Foo<T>::someMethod(T x)
{
    // ...
}
```

Now suppose you have some code in file Bar.cpp that uses Foo<int>:

```cpp
// Bar.cpp
void blah_blah_blah()
{
    // ...
    Foo<int> f;
    f.someMethod(5);
    // ...
}
```

Clearly somebody somewhere is going to have to use the “pattern” for the constructor definition and for the someMethod() definition and instantiate those when T is actually int. But if you had put the definition of the constructor and someMethod() into file Foo.cpp, the compiler would see the template code when it compiled Foo.cpp and it would see Foo<int> when it compiled Bar.cpp, but there would never be a time when it saw both the template code and Foo<int>. So by rule #2 above, it could never generate the code for Foo<int>::someMethod().

___

So templates are overloading, right?
Yes and no.

Function templates participate in name resolution for overloaded functions, but the rules are different. For a template to be considered in overload resolution, the type has to match exactly. If the types do not match exactly, the conversions are not considered and the template is simply dropped from the set of viable functions. That’s what is known as “SFINAE” — Substitution Failure Is Not An Error. Example:


```cpp
#include <iostream>
#include <typeinfo>
template<typename T> void foo(T* x)
{ std::cout << "foo<" << typeid(T).name() << ">(T*)\n"; }
void foo(int x)
{ std::cout << "foo(int)\n"; }
void foo(double x)
{ std::cout << "foo(double)\n"; }
int main()
{
    foo(42);        // matches foo(int) exactly
    foo(42.0);      // matches foo(double) exactly
    foo("abcdef");  // matches foo<T>(T*) with T = char
    return 0;
}
```

In this example, foo<T> cannot be considered for the first or the second call to foo in the body of main because neither 42 nor 42.0 gives the compiler any information to deduce T. The third call, however, includes foo<T> with T = char and it wins.