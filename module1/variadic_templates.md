<!-- .slide: data-background="#111111" -->

# Variadic templates

___

## Motivation

Variadic templates can be used to create template functions or classes which accept any numer of arguments of any type.

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
    variadic_class<float, int, std::string> v{};  // default c-tor
    variadic_class v{2.0, 5, "Hello"}; // automatic template type deduction for classes from C++17
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

Sum<1, 2, 3, 4, 5>::RESULT; // = 15
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

auto num = NumOfArguments<A, B, C>::value;  // 3
```

___

## Fold expressions (C++17)

Fold expressions allow to write compact code with variadic templates without using explicit recursion.

```cpp
template<typename... Args> auto sum(Args... args) {
    return (args + ...);
    // return (... + args);
    // return (0 + ... + args);
    // return (args + ... + 0);
}

template<typename... Args> bool f(Args... args) {
    return (true && ... && args); // OK
}

template<typename... Args> bool f(Args... args) {
    return (args && ... && args); // error: both operands
}                                 // contain unexpanded
                                  // parameter packs
```

___

## Exercise

Write a `print()` function that can print anything on a screen. You should be able to pass any number of parameters to it. Use fold expressions.

Write an `areEven()` function, that

* prints all parameters on screen using above `print()` function
* check if all numbers in parameter pack are even and return a proper boolean value

___

## Solution

```cpp
template<typename ...Args>
void print(Args&&... args) {
    (std::cout << ... << args) << '\n';
}

template<typename... Numbers>
auto areEven(Numbers... nums) {
    print(nums...);
    return ((nums % 2 == 0) && ...);
}
```

Try to add a space between elements in `print()`.

___
