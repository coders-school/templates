<!-- .slide: data-background="#111111" -->

# Template template parameters

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___

## Example

We want to use a template class as a template argument.

```cpp
template<typename T> class my_deleter {};
template<typename T, typename Policy> class handle { /* ... */ };
handle<FILE, my_deleter> h;
```
<!-- .element: class="fragment fade-in" style="font-size: 1.35rem" -->

It causes compilation error:

`error: type/value mismatch at argument 2 in template parameter list for ‘template<class T, class Policy> class handle’`
<!-- .element: class="fragment fade-in" style="font-size: 1.35rem" -->

To allow that, we need to use so called `template template` arguments.

```cpp
template<typename T> class my_deleter {};
template<typename T, template<typename> typename Policy> class handle { /* ... */ };
handle<FILE, my_deleter> h;
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

```cpp
template<size_t N, template<typename, typename> typename Data, typename T1, typename T2>
struct data_array {
  std::array<Data<T1, T2>, N> data;
};
```

```cpp
data_array<16, data, int, double> a1;
a1.data[0].val1 = 4;
a1.data[0].val2 = 3.14;

data_array<8, std::pair, std::string, std::string> a2;
a2.data[0].first = "Mickey";
a2.data[0].second = "Mouse";
```

___

## Task

1. Write a template class that can take any of 4 sequential containers (`vector`, `list`, `forward_list`, `deque`) in one constructor. Do not forget about their versions with allocator as an additional template argument.

2. The class should have a `vector<T>` as a member field. The constructor should copy all values to that vector.

3. The template parameter of the class `(T)` should be deduced as the type hold in the container. Write a deduction guide to allow automatic type deduction.

4. Add a print function for printing the content of the internal `vector<T>` field

5. Add a support of `std::array<T, N>`. The constructor should allow to copy the content of it to the internal vector.
