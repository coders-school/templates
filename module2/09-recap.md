<!-- .slide: data-background="#111111" -->

# Recap

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___

## What have you learned today?

## What was the most difficult to understand?

___

### Points to remember

* <!-- .element: class="fragment fade-in" --> A

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
  fun(1);
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
4. <!-- .element: class="fragment highlight-green" --> <code>template&lt;typename T, template &lt;typname ...&gt; typename Policy&gt;</code> - this should make this code work
5. <!-- .element: class="fragment highlight-green" --> <code>template&lt;typename T, template &lt;typname&gt; typename Policy&gt;</code> - this should make this code work

___

## [Rate this training session](https://forms.gle/ADXRttpAaZgW8KwM6)
