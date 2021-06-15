<!-- .slide: data-background="#111111" -->

# Recap

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___

## How did you enjoy this training session?

## What have you learned today?

___

### Points to remember

* <!-- .element: class="fragment fade-in" --> A template is not a class or a function. A template is a "pattern" that the compiler uses to generate a family of classes or functions.
* <!-- .element: class="fragment fade-in" --> In order for the compiler to generate the code, it must see both the template definition (not just declaration) and the specific types/whatever used to "fill in" the template.
* <!-- .element: class="fragment fade-in" --> Templates itself are only instantiated upon usage. If some function/method was not used, it is not generated, even for class templates
* <!-- .element: class="fragment fade-in" --> Full specializations are allowed for both class and function templates
* <!-- .element: class="fragment fade-in" --> Partial specializations are only allowed for class templates
* <!-- .element: class="fragment fade-in" --> When looking for possible overloads within templates, only perfect matches are considered. No conversions are tried.
* <!-- .element: class="fragment fade-in" --> <code>template &lt;typename T&gt;</code> == <code>template &lt;class T&gt;</code>
* <!-- .element: class="fragment fade-in" --> <code>type_traits</code> has a lot of useful stuff. Use it with <code>static_assert</code> or SFINAE technique.

___

## Pre-test answers

___

## Pre-test 1/3 🤯

### Which of the following usages of a template function are correct?

```cpp
template <typename T, typename U>
U fun(T arg1, U arg2);
```

1. <code class="fragment highlight-green">fun(4, 5)</code>
2. <code class="fragment highlight-green">fun(4, 5.5)</code>
3. <code class="fragment highlight-green">fun&lt;int, int&gt;(4, 5)</code>
4. <code class="fragment highlight-green">fun&lt;int, double&gt;(4, 5.5)</code>
5. <code class="fragment highlight-green">fun&lt;int, int&gt;(4, 5.5)</code>

___
<!-- .slide: style="font-size: 0.9em" -->

## Pre-test 2/3 🤯

### Which of the following usages of a template function are correct?

```cpp
template <typename T, typename U, typename V>
V fun(T arg1, U arg2);
```

1. <code class="fragment highlight-red">fun(4, 5.5)</code>
2. <code class="fragment highlight-red">fun(4, 5.5, int)</code>
3. <code class="fragment highlight-red">fun(4, 5.5, 'c')</code>
4. <code class="fragment highlight-green">fun&lt;int, double, int&gt;(4, 5.5)</code>
5. <code class="fragment highlight-green">fun&lt;int, double, char&gt;(4, 5.5)</code>
6. <code class="fragment highlight-red">fun&lt;int, double, char&gt;(4, 5.5, 'c')</code>
7. <code class="fragment highlight-red">fun&lt;char&gt;(4, 5.5)</code>
8. <code class="fragment highlight-red">fun&lt;V = char&gt;(4, 5.5)</code>

___
<!-- .slide: style="font-size: 0.95em" -->

## Pre-test 3/3 🤯

### Which of the following usages of a template function are correct?

```cpp
template<typename To, typename From>
To convert(From f);
```

1. <code class="fragment highlight-red">auto a = convert(3.14);</code>
2. <code class="fragment highlight-green">auto b = convert&lt;int&gt;(3.14);</code>
3. <code class="fragment highlight-green">auto c = convert&lt;int, double&gt;(3.14);</code>
4. <code class="fragment highlight-green">int(*p1)(float) = convert;</code>
5. <code class="fragment highlight-green">int(*p2)(float) = convert&lt;int, float&gt;;</code>

___

## [Rate this training session](https://forms.gle/ADXRttpAaZgW8KwM6)
