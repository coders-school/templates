<!-- .slide: data-background="#111111" -->

# Variadic templates

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___

## Motivation

Variadic templates can be used to create template functions or classes that accept any numer of arguments of any type.
<!-- .element: class="fragment fade-in" -->

Do you know `printf()` function (from C)?
<!-- .element: class="fragment fade-in" -->

```cpp
#include <cstdio>

int main() {
   printf("Hello %s, you are %d years old\n", "John", 25);
   printf("Just a text\n");
   return 0;
}
```
<!-- .element: class="fragment fade-in" -->

___

## Parameter pack

A template parameter pack is a template parameter that accepts zero or more template arguments
<!-- .element: class="fragment fade-in" -->

```cpp
template<typename ... Types> struct Tuple {};
Tuple<> t0;           // Types contains no arguments
Tuple<int> t1;        // Types contains one argument: int
Tuple<int, float> t2; // Types contains two arguments: int and float
```
<!-- .element: class="fragment fade-in" -->

```cpp
template<typename ... Types> void f(Types ... args);
f();                // OK: args contains no arguments
f(1);               // OK: args contains one argument: int
f(2, 1.0);          // OK: args contains two arguments: int and double
```
<!-- .element: class="fragment fade-in" -->

___

## Syntax

Templates with a variable number of arguments use the new syntax of parameter pack, which represents many (or zero) parameters of a template.

```cpp
template<class ... Types>
void variadic_foo(Types&& ... args)
{ /*...*/ }

int main() {
    variadic_foo(1, "", 2u);
    return 0;
}
```
<!-- .element: class="fragment fade-in" -->

```cpp
template<class ... Types>
class variadic_class
{ /*...*/ };

int main() {
    variadic_class<float, int, std::string> v1{};  // default c-tor
    variadic_class v2{2.0, 5, "Hello"}; // automatic deduction from C++17
}
```
<!-- .element: class="fragment fade-in" -->

___

## Unpacking function parameters

Unpacking group parameters uses new syntax of elipsis operator - `...`
<!-- .element: class="fragment fade-in" -->

In the case of function arguments, it unpacks them in the order given in the template function call.
<!-- .element: class="fragment fade-in" -->

___

## Two ways of passing arguments

```cpp
template <typename... Args>
void print_all(Args&&... args) {
    printMany(args...);
    // expands to printMany(arg1, arg2, ..., argN);
}

template <typename... Args>
void print_each(Args&&... args) {
    (printOne(args), ...);  // fold expression from C++17
    // expands to printOne(arg1), printOne(arg2), ..., printOne(argN);
}

int main() {
    print_all("Hello!", "Lukin");
    print_each("Hello!", "Lukin");
    return 0;
}
```

___

## Unpacking parameter types

```cpp
template <typename ... Foo>
void fun(Foo ... bar);
```

Assuming the above function below expressions will be expanded in this way:
<!-- .element: class="fragment fade-in" -->

```text
Foo...                => Foo1, Foo2, Foo3, etc
vector<Foo>...        => vector<Foo1>, vector<Foo2>, vector<Foo3>, etc
tuple<Foo...>(bar...) => tuple<Foo1, Foo2, Foo3, etc>(bar1, bar2, bar3, etc)
&bar...               => &bar1, &bar2, &bar3, etc
&&bar...              => &&bar1, &&bar2, &&bar3, etc
```
<!-- .element: class="fragment fade-in" -->

___

## Example with `std::variant`

```cpp
#include <functional>
#include <iostream>
#include <string>
#include <variant>

template <typename... Ts>
struct make_visitor
  : Ts...
{
  using Ts::operator()...;
};

// Deduction guide
template <typename... Ts>
make_visitor(Ts...) -> make_visitor<Ts...>;

using variant = std::variant<int, std::string, double>;

int main()
{
  {
    const auto v0 = variant{42.2};

    std::visit(make_visitor{
      [](int){std::cout << "int\n";},
      [](std::string){std::cout << "std::string\n";},
      [](double){std::cout << "double\n";}
    }, v0);

    // Without deduction guide
    std::visit(make_visitor<
        std::function<void(int)>,
        std::function<void(std::string)>,
        std::function<void(double)>>
    {
      [](int){std::cout << "int\n";},
      [](std::string){std::cout << "std::string\n";},
      [](double){std::cout << "double\n";}
    }, v0);
  }
}
```
<!-- .element: style="font-size: 1.2rem" -->

[Source](https://gist.github.com/ahamez/383f8e326d2b63d27a2ef6935162ce09)

___

## Head tail recursion

It is also possible to use recursion to unpack every single argument. It requires the variadic template Head/Tail and non-template function to be defined.

```cpp
void variadic_foo() {}

template<class Head, class... Tail>
void variadic_foo(Head const& head, Tail const&... tail) {
    takesOneParam(head);    //action on head
    variadic_foo(tail...);
}
```

___

## Head tail recursion in classes

It is possible to unpack all types at once (e.g. in the case of a base class that is a variadic template class) or using partial and full specializations.

```cpp
template<int... Number>
struct Sum;

template<int Head, int... Tail>
struct Sum<Head, Tail...> {
    const static int RESULT = Head + Sum<Tail...>::RESULT;
};

template<>
struct Sum<> {
    const static int RESULT = 0;
}

constexpr auto value = Sum<1, 2, 3, 4, 5>::RESULT; // = 15
```

___

## Handling inheritance from variadic classes

```cpp
template<class... Types>
struct Base
{};

template<class... Types>
struct Derived : Base<Types...>
{};
```

___

## `sizeof...` operator

`sizeof...` returns the number of parameters in a parameter pack.

```cpp
template<class... Types>
struct NumOfArguments {
    const static unsigned value = sizeof...(Types);
};

constexpr auto num = NumOfArguments<A, B, C>::value;  // 3
```

___

## Task

Write a `make_array()` function, that can create `std::array<T, N>` from all values passed to it.

```cpp
std::array<int, 3> a = make_array(1, 2, 3);
std::array<double, 4> b = make_array(1.1, 2.2, 3.3, 4.4);
```

### Hints
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> variadic function
* <!-- .element: class="fragment fade-in" --> `sizeof...` to deduce size
* <!-- .element: class="fragment fade-in" --> `std::common_type` to deduce the type
* <!-- .element: class="fragment fade-in" --> trailing return type with `->`
* <!-- .element: class="fragment fade-in" --> perfect forwarding
* <!-- .element: class="fragment fade-in" --> `constexpr`

___

## Solution

```cpp
#include <array>
#include <iostream>
#include <type_traits>

template<typename... Ts>
constexpr auto make_array(Ts&&... ts) -> std::array<std::common_type_t<Ts...>, sizeof...(Ts)> {
    return { std::forward<Ts>(ts)... };
}

int main() {
    auto b = make_array(1, 2, 3);
    std::cout << b.size() << '\n';
    for(auto i : b)
        std::cout << i << ' ';
}
```
<!-- .element: class="fragment fade-in" style="font-size: 1.18rem" -->

___

## Perfect forwarding

It is recommended to use `&&` and `std::forward` with variadic arguments to handle r-values and l-values correctly. It is so-called **perfect forwarding**.

```cpp
#include <utility>

template<typename Type>
void single_perfect_forwarding(Type&& t) {
    callable(std::forward<Type>(t));
}

template<typename... Types>
void variadic_perfect_forwarding(Types&&... args) {
    callable(std::forward<Types>(args)...);
}
```
