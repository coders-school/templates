<!-- .slide: data-background="#111111" -->

# Recap

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___

## What was the most difficult thing?

## What have you learned today?


___

### Points to remember

* <!-- .element: class="fragment fade-in" --> Deduction guides help the compiler to deduce proper template classes
* <!-- .element: class="fragment fade-in" --> SFINAE is used to disable code generation for a certain types
* <!-- .element: class="fragment fade-in" --> To pass a template class to a template you need to use so-called template template arguments
* <!-- .element: class="fragment fade-in" --> If you want a function that can take any number of arguments use variadic templates
* <!-- .element: class="fragment fade-in" --> Use fold expressions to simplify operations on variadic arguments
* <!-- .element: class="fragment fade-in" --> If possible, you can replace template functions with generic lambdas (from C++14). Just keep in mind that lambdas are objects and have a limited lifespan.
* <!-- .element: class="fragment fade-in" --> If possible, use <code>if constexpr</code>, <code>static_assert</code> or concepts to emulate SFINAE.

___

## Pre-test answers

___

## Pre-test 1/3 🤯

### Is this code correct?

```cpp
template<typename... Args> bool f(Args... args) {
    return (args && ... && args);
}
```

1. <!-- .element: class="fragment highlight-red" --> Yes
2. <!-- .element: class="fragment highlight-green" --> No, the parameter pack is used twice in fold-expression
3. <!-- .element: class="fragment highlight-red" --> No, the ellipsis operator is used incorrectly in fold-expression
4. <!-- .element: class="fragment highlight-red" --> No, <code>Args&&</code> should be used as a function argument

___
<!-- .slide: style="font-size: 0.9em" -->

## Pre-test 2/3 🤯

### What is the output of this program?

```cpp
#include <iostream>

template <typename T>
void fun(T)
{
  static int i;
  std::cout << ++i;
}

int main()
{
  fun(1);
  fun(1.0);
  fun(2);
}
```

#### <code class="fragment fade-in">112</code>

___
<!-- .slide: style="font-size: 0.8em" -->

## Pre-test 3/3 🤯

### Mark true statements about this code

```cpp
template<typename T> class MyDeleter {};
template<typename T, typename Policy> class Handle { /* ... */ };
Handle<FILE, MyDeleter> h;
```

1. <!-- .element: class="fragment highlight-red" --> This code compiles
2. <!-- .element: class="fragment highlight-green" --> <code>MyDeleter</code> cannot be used as a <code>Policy</code> template argument
3. <!-- .element: class="fragment highlight-red" --> <code>template&lt;typename T, template typename Policy&gt;</code> - this should make this code work
4. <!-- .element: class="fragment highlight-green" --> <code>template&lt;typename T, template &lt;typename ...&gt; typename Policy&gt;</code> - this should make this code work
5. <!-- .element: class="fragment highlight-green" --> <code>template&lt;typename T, template &lt;typename&gt; typename Policy&gt;</code> - this should make this code work

___

## [Rate this training session](https://forms.gle/ADXRttpAaZgW8KwM6)
