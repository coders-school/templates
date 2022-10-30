# Pre-test 🤯

___

## Pre-test 1/3 🤯

### Czy poniższy kod jest poprawny?

```cpp
template<typename... Args> bool f(Args... args) {
    return (args && ... && args);
}
```

1. Tak
2. Nie, paczka parametrów jest użyta dwukrotnie w wyrażeniu fold
3. Nie, operator elipsis (wielokropka) jest źle użyty
4. Nie, jako typ argumentu funkcja powinna przyjmować <code>Args&&...</code>

___
<!-- .slide: style="font-size: 0.9em" -->

## Pre-test 2/3 🤯

### Co wypisze się na ekranie?

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

___
<!-- .slide: style="font-size: 0.8em" -->

## Pre-test 3/3 🤯

### Zaznacz prawdziwe stwierdzenia o poniższym kodzie

```cpp
template<typename T> class MyDeleter {};
template<typename T, typename Policy> class Handle { /* ... */ };

int main() {
    Handle<int, MyDeleter> h;
}
```

1. Kod się kompiluje
2. <code>MyDeleter</code> nie może być użyte jako argument szablonowy <code>Policy</code>
3. <code>template&lt;typename T, template typename Policy&gt;</code> - to powinno naprawić ten kod
4. <code>template&lt;typename T, template &lt;typename ...&gt; typename Policy&gt;</code> - to powinno naprawić ten kod
5. <code>template&lt;typename T, template &lt;typename&gt; typename Policy&gt;</code> -  to powinno naprawić ten kod
