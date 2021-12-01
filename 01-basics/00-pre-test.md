# Pre-test 🤯

___

## Pre-test 1/3 🤯

### Które z poniższych użyć funkcji szablonowej `fun` są poprawne?

```cpp
template <typename T, typename U>
U fun(T arg1, U arg2);
```

1. <code>fun(4, 5)</code>
2. <code>fun(4, 5.5)</code>
3. <code>fun&lt;int, int&gt;(4, 5)</code>
4. <code>fun&lt;int, double&gt;(4, 5.5)</code>
5. <code>fun&lt;int, int&gt;(4, 5.5)</code>

___
<!-- .slide: style="font-size: 0.9em" -->

## Pre-test 2/3 🤯

### Które z poniższych użyć funkcji szablonowej `fun` są poprawne?

```cpp
template <typename T, typename U, typename V>
V fun(T arg1, U arg2);
```

1. <code>fun(4, 5.5)</code>
2. <code>fun(4, 5.5, int)</code>
3. <code>fun(4, 5.5, 'c')</code>
4. <code>fun&lt;int, double, int&gt;(4, 5.5)</code>
5. <code>fun&lt;int, double, char&gt;(4, 5.5)</code>
6. <code>fun&lt;int, double, char&gt;(4, 5.5, 'c')</code>
7. <code>fun&lt;char&gt;(4, 5.5)</code>
8. <code>fun&lt;V = char&gt;(4, 5.5)</code>

___
<!-- .slide: style="font-size: 0.95em" -->

## Pre-test 3/3 🤯

### Które z poniższych użyć funkcji szablonowej `convert` są poprawne?

```cpp
template<typename To, typename From>
To convert(From f);
```

1. <code>auto a = convert(3.14);</code>
2. <code>auto b = convert&lt;int&gt;(3.14);</code>
3. <code>auto c = convert&lt;int, double&gt;(3.14);</code>
4. <code>int(*p1)(float) = convert;</code>
5. <code>int(*p2)(float) = convert&lt;int, float&gt;;</code>
