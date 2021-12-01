<!-- .slide: data-background="#111111" -->

# Deduction guides

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___

## Template type deduction for classes (C++17)

Template types can be automatically deduced by the compiler thanks to... template functions.
<!-- .element: class="fragment fade-in" -->

The compiler uses class constructors to achieve that.
<!-- .element: class="fragment fade-in" -->

From C++17 you can write a code like this:
<!-- .element: class="fragment fade-in" -->

```c++
std::vector v = {1, 2, 3};  // std::vector<int> is deduced
std::list l{'c', 'd', 'b'}; // std::list<char> is deduced
```
<!-- .element: class="fragment fade-in" -->

That's not gonna work:
<!-- .element: class="fragment fade-in" -->

```cpp
// std::vector v1;          // compilation error, vector of what?
// std::vector v2(10)       // compilation error, 10 elements of what?
```
<!-- .element: class="fragment fade-in" -->

___
<!-- .slide: data-visibility="hidden" style="font-size: 0.85em" -->

## Template class argument deduction

```cpp
template<class T>
struct UniquePtr {
    UniquePtr(T* t);
    // ...
};
```
<!-- .element: class="fragment fade-in" -->

### What is deduced here?
<!-- .element: class="fragment fade-in" -->

```cpp
UniquePtr p1{new auto(2.0)};
```
<!-- .element: class="fragment fade-in" -->

`UniquePtr<double>`
<!-- .element: class="fragment fade-in" -->

### And what is deduced here?
<!-- .element: class="fragment fade-in" -->

```cpp
UniquePtr p2{new double[10]{}};  // T should be a single object or an array?
```
<!-- .element: class="fragment fade-in" -->

`UniquePtr<double>`
<!-- .element: class="fragment fade-in" -->

When automatic deduction guides work against you, it is better to disable them for a specific constructor argument.
<!-- .element: class="fragment fade-in" -->

___
<!-- .slide: data-visibility="hidden" -->

## Disabling deduction guides

```cpp
template<typename T>
struct type_identity { using type = T; };

template<typename T>
using type_identity_t = typename type_identity<T>::type;
```
<!-- .element: class="fragment fade-in" -->

```cpp
template<class T>
struct UniquePtr {
    UniquePtr(type_identity_t<T>* t);
    // UniquePtr(T* t);
    // ...
};
```
<!-- .element: class="fragment fade-in" -->

```cpp
UniquePtr<double> p1{new auto(2.0)};
UniquePtr<double[]> p2{new double[10]{}};
```
<!-- .element: class="fragment fade-in" -->

___

## User-defined deduction guides

* <!-- .element: class="fragment fade-in" --> The syntax is similar to function declaration with a trailing return type, except that it uses the name of a class template as the function name.
* <!-- .element: class="fragment fade-in" --> It's not a function and does not have a body.

```cpp
template<class T>
struct container {
    container(T t);
    template<class Iter> container(Iter beg, Iter end);
};

// additional deduction guide
template<class Iter>
container(Iter b, Iter e) -> container<typename std::iterator_traits<Iter>::value_type>;
```
<!-- .element: class="fragment fade-in" style="font-size: 1.2rem" -->

```cpp
container c1{2.71};                       // deduces T = double using an automatic guide
std::vector v = {1, 2, 3, 4};             // deduces std::vector<int>
container c2{v.begin(), v.end()};         // deduces T = int
auto c3 = container{v.begin(), v.end()};  // deduces T = int
//container c4{5, 6};                     // Error: no std::iterator_traits<int>::value_type
```
<!-- .element: class="fragment fade-in" style="font-size: 1.2rem" -->

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

### [More on cppreference.com](https://en.cppreference.com/w/cpp/language/class_template_argument_deduction)
