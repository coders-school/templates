<!-- .slide: data-background="#111111" -->

# Powtórka

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___

## Co wydaje Ci się być najtrudniejsze?

## Czego się nauczyłeś z tych materiałów?

___

### Rzeczy do zapamiętania

* <!-- .element: class="fragment fade-in" --> Podpowiedzi dedukcyjne pomagają kompilatorowi wydedukować odpowiednie klasy szablonów
* <!-- .element: class="fragment fade-in" --> SFINAE służy do wyłączania generowania kodu dla niektórych typów
* <!-- .element: class="fragment fade-in" --> Aby przekazać klasę szablonu do szablonu, musisz użyć tak zwanych argumentów szablonu szablonu (template template arguments)
* <!-- .element: class="fragment fade-in" --> Jeśli potrzebujesz funkcji, która może przyjmować dowolną liczbę argumentów, użyj szablonów wariancyjnych
* <!-- .element: class="fragment fade-in" --> Używaj fold expressions, aby uprościć operacje na argumentach wariadycznych
* <!-- .element: class="fragment fade-in" --> Jeśli to możliwe, możesz zastąpić funkcje szablonu generycznymi wyrażeniami lambda (z C++ 14). Pamiętaj tylko, że lambdy są obiektami i mają ograniczony czas życia.
* <!-- .element: class="fragment fade-in" -->Jeśli to możliwe, użyj <code>if constexpr</code>, <code>static_assert</code> lub koncepcji, aby emulować SFINAE.

___

## Odpowiedzi do pre-testu

___

## Pre-test 1/3 🤯

### Czy poniższy kod jest poprawny?

```cpp
template<typename... Args> bool f(Args... args) {
    return (args && ... && args);
}
```

1. <!-- .element: class="fragment highlight-red" --> Tak
2. <!-- .element: class="fragment highlight-green" --> Nie, paczka parametrów jest użyta dwukrotnie w wyrażeniu fold
3. <!-- .element: class="fragment highlight-red" --> Nie, operator elipsis (wielokropka) jest źle użyty
4. <!-- .element: class="fragment highlight-red" --> Nie, jako typ argumentu funkcja powinna przyjmować <code>Args&&...</code>

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

#### <code class="fragment fade-in">112`

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

1. <!-- .element: class="fragment highlight-red" --> Kod się kompiluje
2. <!-- .element: class="fragment highlight-green" --> <code>MyDeleter</code>  nie może być użyte jako argument szablonowy <code>Policy</code>
3. <!-- .element: class="fragment highlight-red" --> <code>template&lt;typename T, template typename Policy&gt;</code> - to powinno naprawić ten kod
4. <!-- .element: class="fragment highlight-green" --> <code>template&lt;typename T, template &lt;typename ...&gt; typename Policy&gt;</code> - to powinno naprawić ten kod
5. <!-- .element: class="fragment highlight-green" --> <code>template&lt;typename T, template &lt;typename&gt; typename Policy&gt;</code> - to powinno naprawić ten kod
