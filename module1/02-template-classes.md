<!-- .slide: data-background="#111111" -->

# Template classes

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___

## Template class example

Template classes are as well used to avoid code duplication, as to create so-called meta-programs within them. Here is an example of a simple template class and its usage:
<!-- .element: class="fragment fade-in" -->

```c++
#include <iostream>

template <typename T, typename U>
class SomeClass {
public:
    T getValue() { return value; }
private:
    T value = {};
    U* ptr = nullptr;
};

int main() {
    SomeClass<int, void> sc;
    std::cout << sc.getValue() << std::endl;
    return 0;
}
```
<!-- .element: class="fragment fade-in" -->

___

## Template classes in STL

Template classes are heavily used in STL. For example `std::vector`, `std::list` and other containers are template classes and if you want to use them, you do it like here:
<!-- .element: class="fragment fade-in" -->

```c++
std::vector<int> v = {1, 2, 3};
std::list<char> l{'c', 'd', 'b'};
```
<!-- .element: class="fragment fade-in" -->

___
<!-- .slide: style="font-size: .95em" -->

## Template type deduction for classes (C++17)

Template types can also be automatically deduced by the compiler thanks to... template functions.
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
// clang error: no viable constructor or deduction guide for deduction of
//   template arguments of 'vector'
// g++ error: class template argument deduction failed:
//   no matching function for call to 'vector()'
```
<!-- .element: class="fragment fade-in" -->

___

## Exercise - `VectorMap`

Write a template class `VectorMap` that represents an over-engineered `std::map`.

It should hold 2 `std::vectors` inside with the same size, each with different types. The first vector should hold keys, the other one values.

Elements at the same position in both vectors should create a pair like `1` and `'c'` below.

```c++
VectorMap<int, char> map;
map.insert(1, 'c');
map[1] = 'e';           // replaces value under 1
std::cout << map[1];    // prints 'e'
map.at(2);              // throw std::out_of_range
```

Implement the mentioned above `insert()`, `operator[]`, `at()` methods.

Do not bother about duplicated keys for now.
You can also try to implement additional methods from `std::map` interface 🙂

Use [cppreference](http://en.cppreference.com/w/cpp/container/map).
