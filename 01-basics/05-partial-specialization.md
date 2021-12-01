<!-- .slide: data-background="#111111" -->

# Partial specialization

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___

## Template function partial specialization

In C++ we cannot partially specialize functions.

___
<!-- .slide: style="font-size: 0.85em" -->

## Template class partial specialization

In C++ we can specialize classes partially. It means that we need to leave at least one template parameter.

```cpp
// primary template
template <typename T1, typename T2, typename T3>
class A {};

// partial specialization with T1 = int
template <typename T2, typename T3>
class A<int, T2, T3> {};

// partial specialization with T1 = int and T2 = double
template <typename T3>
class A<int, double, T3> {};

// partial specialization with T1 = int and T3 = char
template <typename T2>
class A<int, T2, char> {};

// full specialization with T1 = T2 = double and T3 = int
template <>
class A<double, double, int> {};
```

___
<!-- .slide: style="font-size: 0.85em" -->

## Advanced partial specialization

```cpp
template <typename T1, typename T2, typename I>
class A {};                  // primary template

template<typename T, typename I>
class A<T, T*, I> {};        // #1: partial specialization where T2 is a pointer to T1

template<typename T, typename T2, typename I>
class A<T*, T2, I> {};       // #2: partial specialization where T1 is a pointer

template<typename T>
class A<int, T*, double> {}; // #3: partial specialization where T1 is int, I is double,
                             //     and T2 is a pointer

template<typename X, typename T, typename I>
class A<X, T*, I> {};        // #4: partial specialization where T2 is a pointer
```

___

## Exercise

Write a partial specialization of `VectorMap` for boolean keys. We can have only 2 values for boolean keys. There is no need to keep vectors inside.

Implement properly all currently available functions.
