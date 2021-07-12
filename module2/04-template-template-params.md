<!-- .slide: data-background="#111111" -->

# Template template parameters

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___

## Example

We want to use a template class as a template argument.
<!-- .element: class="fragment fade-in" -->

```cpp
template<typename T> class MyDeleter {};
template<typename T, typename Policy> class Handle { /* ... */ };
Handle<FILE, MyDeleter> h;
```
<!-- .element: class="fragment fade-in" style="font-size: 1.35rem" -->

It causes a compilation error:
<!-- .element: class="fragment fade-in" -->

`error: type/value mismatch at argument 2 in template parameter list for ‘template<class T, class Policy> class Handle’`
<!-- .element: class="fragment fade-in" style="font-size: 1.35rem" -->

We tried to pass a template class instead of a specific class (like instantiated template class). This should work:
<!-- .element: class="fragment fade-in" -->

```cpp
Handle<FILE, MyDeleter<FILE>> h;
```
<!-- .element: class="fragment fade-in" -->

___

## Template of template

To allow using a template class, we need to use so-called `template template` arguments.
<!-- .element: class="fragment fade-in" -->

```cpp
template<typename T> class MyDeleter {};
template<typename T, template<typename> typename Policy> class Handle { /* ... */ };
// template<typename T, typename Policy> class Handle { /* ... */ };  // previously
Handle<FILE, MyDeleter> h;
```
<!-- .element: class="fragment fade-in" style="font-size: 1.35rem" -->

___

## Template template parameters

```cpp
template<template<parameter-list> typename|class name> declaration
template<template<parameter-list> typename|class> declaration

template<template<parameter-list> typename|class name = default> declaration
template<template<parameter-list> typename|class = default> declaration

template<template<parameter-list> typename|class ... name> declaration
template<template<parameter-list> typename|class ...> declaration
```

___

## More examples

```cpp
template<typename T1, typename T2>
struct data {
    T1 val1;
    T2 val2;
};
```
<!-- .element: class="fragment fade-in" style="font-size: 1.3rem" -->

```cpp
template<size_t N, template<typename, typename> typename Data, typename T1, typename T2>
struct data_array {
  std::array<Data<T1, T2>, N> data;
};
```
<!-- .element: class="fragment fade-in" style="font-size: 1.3rem" -->

```cpp
data_array<16, data, int, double> a1;
a1.data[0].val1 = 4;
a1.data[0].val2 = 3.14;

data_array<8, std::pair, std::string, std::string> a2;
a2.data[0].first = "Mickey";
a2.data[0].second = "Mouse";
```
<!-- .element: class="fragment fade-in" style="font-size: 1.3rem" -->

___

## Task

1. Write a template class `Holder`.
   1. <!-- .element: style="font-size: 0.7em" --> The class should have a <code>vector&lt;T&gt;</code> as a member field.
   2. <!-- .element: style="font-size: 0.7em" --> The class should have a constructor, that can take any of 4 sequential containers (<code>vector</code>, <code>list</code>, <code>forward_list</code>, <code>deque</code>). This constructor should copy all values to the internal vector.
   3. <!-- .element: style="font-size: 0.7em" --> The template parameter of the class <code>T</code> should be automatically deduced. Write a deduction guide if needed.

2. Add a print function for printing the content of the internal `vector<T>` field

3. Add support of `std::array<T, N>`. The constructor should allow copying the content to the internal vector.

___

## Solution #1 (easier)

```cpp
template <typename T>
class Holder {
    std::vector<T> v_;
public:
    template <typename Container>
    Holder(const Container & c)
        : v_{c.begin(), c.end()}
    {}

    void print() {
        std::copy(v_.begin(), v_.end(), std::ostream_iterator<T>(std::cout, " "));
    }
};

template <typename Container>
Holder(const Container & c) -> Holder<typename Container::value_type>;
```
<!-- .element: class="fragment fade-in" style="font-size: 1.3rem" -->

* <!-- .element: class="fragment fade-in" --> No template template arguments
* <!-- .element: class="fragment fade-in" --> Simple deduction guide

___
<!-- .slide: style="font-size: 0.85em" -->
## Solution #2

```cpp
template <typename T, template <typename...> typename Container>
class Holder {
    std::vector<T> v_;
public:
    Holder(const Container<T> & c)
        : v_{c.begin(), c.end()}
    {}

    template <size_t N>
    Holder(const std::array<T, N> & a)
        : v_{a.begin(), a.end()}
    {}

    void print() {
        std::copy(v_.begin(), v_.end(), std::ostream_iterator<T>(std::cout, " "));
    }
};

template <typename T, size_t N>
Holder(const std::array<T, N> & a) -> Holder<T, std::vector>;
```
<!-- .element: class="fragment fade-in" style="font-size: 1.3rem" -->

* <!-- .element: class="fragment fade-in" --> Template template arguments
* <!-- .element: class="fragment fade-in" --> Additional constructor for <code>std::array</code>
* <!-- .element: class="fragment fade-in" --> Additional and counterintuitive deduction guide for array
