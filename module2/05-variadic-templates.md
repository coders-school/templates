<!-- .slide: data-background="#111111" -->

# Variadic templates

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___

## Motivation

Variadic templates can be used to create template functions or classes that accept any numer of arguments of any type.

Do you know `printf()` function (from C)?

```cpp
#include <cstdio>

int main() {
   printf("Hello %s, you are %d years old\n", "John", 25);
   printf("Just a text\n");
   return 0;
}
```

___

## Syntax

Templates with variable number of arguments use new syntax of parameter pack, that represents many (or zero) parameters of a template.

```cpp
template<class... Types>
void variadic_foo(Types&&... args)
{ /*...*/ }

int main() {
    variadic_foo(1, "", 2u);
    return 0;
}
```

```cpp
template<class... Types>
class variadic_class
{ /*...*/ };

int main() {
    variadic_class<float, int, std::string> v1{};  // default c-tor
    variadic_class v2{2.0, 5, "Hello"}; // automatic template type deduction for classes from C++17
}
```

___

## Unpacking function parameters

Unpacking group parameters uses new syntax of elipsis operator - `...`

In case of function arguments it unpacks them in the order given in template function call.

It is possible to call a function on a parameter pack. In such case given function will be called on every argument from a function call.

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

```text
Foo...                => Foo1, Foo2, Foo3, etc
vector<Foo>...        => vector<Foo1>, vector<Foo2>, vector<Foo3>, etc
tuple<Foo...>(bar...) => tuple<Foo1, Foo2, Foo3, etc>(bar1, bar2, bar3, etc)
&bar...               => &bar1, &bar2, &bar3, etc
&&bar...              => &&bar1, &&bar2, &&bar3, etc
```

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

It is possible to unpack all types at once (e.g. in case of base class that is variadic template class) or using partial and full specializations.

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

## Perfect forwarding

It is recommended to use `&&` and `std::forward` with variadic arguments to handle r-values and l-values correctly. It is so called **perfect forwarding**.

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
