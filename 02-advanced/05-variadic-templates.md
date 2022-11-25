<!-- .slide: data-background="#111111" -->

# Variadic templates

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___

## Motivation

<p>Variadic templates can be used to create template functions or classes that accept any numer of arguments of any type.</p>
<!-- .element: class="fragment fade-in" -->

<p>Do you know <code>printf()</code> function (from C)?</p>
<!-- .element: class="fragment fade-in" -->

<pre class="fragment"><code class="cpp" data-trim>
#include <cstdio>

int main() {
   printf("Hello %s, you are %d years old\n", "John", 25);
   printf("Just a text\n");
   return 0;
}
</code></pre>
<!-- .element: class="fragment fade-in" -->

___

## Parameter pack

<p>A template parameter pack is a template parameter that accepts zero or more template arguments</p>
<!-- .element: class="fragment fade-in" -->

<pre class="fragment"><code class="cpp" data-trim>
template<typename ... Types> struct Tuple {};
Tuple<> t0;           // Types contains no arguments
Tuple<int> t1;        // Types contains one argument: int
Tuple<int, float> t2; // Types contains two arguments: int and float
</code></pre>
<!-- .element: class="fragment fade-in" -->

<pre class="fragment"><code class="cpp" data-trim>
template<typename ... Types> void f(Types ... args);
f();                // OK: args contains no arguments
f(1);               // OK: args contains one argument: int
f(2, 1.0);          // OK: args contains two arguments: int and double
</code></pre>
<!-- .element: class="fragment fade-in" -->

___

## Składnia

Szablony ze zmienną liczbą argumentów używają nowej składni pakietu parametrów, która reprezentuje wiele (lub zero) parametrów szablonu.

<pre class="fragment"><code class="cpp" data-trim>
template<class ... Types>
void variadic_foo(Types&& ... args)
{ /*...*/ }

int main() {
    variadic_foo(1, "", 2u);
    return 0;
}
</code></pre>
<!-- .element: class="fragment fade-in" -->

<pre class="fragment"><code class="cpp" data-trim>
template<class ... Types>
class variadic_class
{ /*...*/ };

int main() {
    variadic_class<float, int, std::string> v1{};  // default c-tor
    variadic_class v2{2.0, 5, "Hello"}; // automatic deduction from C++17
}
</code></pre>
<!-- .element: class="fragment fade-in" -->

___

## Rozpakowywanie parametrów funkcji

<p>Rozpakowywanie grup parametrów wykorzystuje nową składnię operatora wielokropka - <code>...</code></p>
<!-- .element: class="fragment fade-in" -->

<p>W przypadku argumentów funkcji rozpakowuje je w kolejności podanej przy wywołaniu funkcji szablonowej.</p>
<!-- .element: class="fragment fade-in" -->

___

## Dwa sposoby przekazywania argumentów

```cpp
template <typename... Args>
void print_all(Args&&... args) {
    printMany(args...);
    // expands to printMany(arg1, arg2, ..., argN);
}

template <typename... Args>
void print_each(Args&&... args) {
    (printOne(args), ...);  // fold expression from C++17
    // expands to printOne(arg1), printOne(arg2), ..., printOne(argN);
}

int main() {
    print_all("Hello!", "Lukin");
    print_each("Hello!", "Lukin");
    return 0;
}
```

___

## Rozpakowywanie typów parametrów

```cpp
template <typename ... Foo>
void fun(Foo ... bar);
```

<code>Zakładając że powyższa funkcja poniżej wyrażeń zostanie rozwinięta następująco:</code>
<!-- .element: class="fragment fade-in" -->

<pre class="fragment"><code class="cpp" data-trim>
Foo...                => Foo1, Foo2, Foo3, etc
vector<Foo>...        => vector<Foo1>, vector<Foo2>, vector<Foo3>, etc
tuple<Foo...>(bar...) => tuple<Foo1, Foo2, Foo3, etc>(bar1, bar2, bar3, etc)
&bar...               => &bar1, &bar2, &bar3, etc
&&bar...              => &&bar1, &&bar2, &&bar3, etc
</code></pre>
<!-- .element: class="fragment fade-in" -->

___

## Przykłady z `std::variant`

<pre class="fragment"><code class="cpp" data-trim>
#include <functional>
#include <iostream>
#include <string>
#include <variant>

template <typename... Ts>
struct make_visitor
  : Ts...
{
  using Ts::operator()...;
};

// Deduction guide
template <typename... Ts>
make_visitor(Ts...) -> make_visitor<Ts...>;

using variant = std::variant<int, std::string, double>;

int main()
{
  {
    const auto v0 = variant{42.2};

    std::visit(make_visitor{
      [](int){std::cout << "int\n";},
      [](std::string){std::cout << "std::string\n";},
      [](double){std::cout << "double\n";}
    }, v0);

    // Without deduction guide
    std::visit(make_visitor<
        std::function<void(int)>,
        std::function<void(std::string)>,
        std::function<void(double)>>
    {
      [](int){std::cout << "int\n";},
      [](std::string){std::cout << "std::string\n";},
      [](double){std::cout << "double\n";}
    }, v0);
  }
}
</code></pre>
<!-- .element: style="font-size: 1.2rem" -->

[Źródło](https://gist.github.com/ahamez/383f8e326d2b63d27a2ef6935162ce09)

___

## Rekurencja Head tail

Możliwe jest również użycie rekurencji do rozpakowania każdego pojedynczego argumentu. Wymaga to wariadycznego szablonu Head/Tail i funkcji nie będącej szablonem do zdefiniowania.

```cpp
void variadic_foo() {}

template<class Head, class... Tail>
void variadic_foo(Head const& head, Tail const&... tail) {
    takesOneParam(head);    //action on head
    variadic_foo(tail...);
}
```

___

## Rekurencja Head tail w klasach

Możliwe jest rozpakowanie wszystkich typów na raz (np. w przypadku bazowej klasy, będącej wariadyczną klasą szablonową) lub skorzystanie z częściowej, albo pełnej specjalizacji.

```cpp
template<int... Number>
struct Sum;

template<int Head, int... Tail>
struct Sum<Head, Tail...> {
    const static int RESULT = Head + Sum<Tail...>::RESULT;
};

template<>
struct Sum<> {
    const static int RESULT = 0;
}

constexpr auto value = Sum<1, 2, 3, 4, 5>::RESULT; // = 15
```

___

## Obsługa dziedziczenia z klas wariadycznych

```cpp
template<class... Types>
struct Base
{};

template<class... Types>
struct Derived : Base<Types...>
{};
```

___

## Operator `sizeof...`

`sizeof...` zwraca liczbę parametrów w pakiecie parametrów.

```cpp
template<class... Types>
struct NumOfArguments {
    const static unsigned value = sizeof...(Types);
};

constexpr auto num = NumOfArguments<A, B, C>::value;  // 3
```

___

## Zadanie

Napisz funkcję `make_array()`, która może utworzyć `std::array<T, N>` ze wszystkich przekazanych jej wartości.

```cpp
std::array<int, 3> a = make_array(1, 2, 3);
std::array<double, 4> b = make_array(1.1, 2.2, 3.3, 4.4);
```

### Podpowiedzi
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> funkcje wariadyczne
* <!-- .element: class="fragment fade-in" --> <code>sizeof...</code> by wydedukować rozmiar
* <!-- .element: class="fragment fade-in" --> <code>std::common_type</code> by wydedukować typ
* <!-- .element: class="fragment fade-in" --> końcowy typ powrotu z <code>-></code>
* <!-- .element: class="fragment fade-in" --> perfect forwarding
* <!-- .element: class="fragment fade-in" --> <code>constexpr</code>

___

## Rozwiązanie

<pre class="fragment"><code class="cpp" data-trim>
#include <array>
#include <iostream>
#include <type_traits>

template<typename... Ts>
constexpr auto make_array(Ts&&... ts) -> std::array<std::common_type_t<Ts...>, sizeof...(Ts)> {
    return { std::forward<Ts>(ts)... };
}

int main() {
    auto b = make_array(1, 2, 3);
    std::cout << b.size() << '\n';
    for(auto i : b)
        std::cout << i << ' ';
}
</code></pre>
<!-- .element: class="fragment fade-in" style="font-size: 1.18rem" -->

___

## Perfect forwarding

Rekomendowanym jest, by korzystać z  `&&` oraz `std::forward` z argumentami wariadycznymi, by obsługiwać r-values i l-values poprawnie. to tak zwany **perfect forwarding**.

```cpp
#include <utility>

template<typename Type>
void single_perfect_forwarding(Type&& t) {
    callable(std::forward<Type>(t));
}

template<typename... Types>
void variadic_perfect_forwarding(Types&&... args) {
    callable(std::forward<Types>(args)...);
}
```
