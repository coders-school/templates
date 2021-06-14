<!-- .slide: data-background="#111111" -->

# Template functions

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___
<!-- .slide: style="font-size: 0.9em" -->

## Examples

Let's assume that we have a function below:

```c++
int add(int first, int second) {
    return first + second;
}
```

If we want to have a function that takes doubles as well, we need to write:
<!-- .element: class="fragment fade-in" -->

```c++
double add(double first, double second) {
    return first + second;
}
```
<!-- .element: class="fragment fade-in" -->

And if we want a function that can take complex or any other numbers we would need to write:
<!-- .element: class="fragment fade-in" -->

```c++
std::complex<int> add(std::complex<int> first, std::complex<int> second) {
    return first + second;
}
```
<!-- .element: class="fragment fade-in" -->

You can clearly see that we have a code duplication here.
<!-- .element: class="fragment fade-in" -->

___

## Avoiding code duplication

Instead of writing so many functions we can have only one - template function:

```c++
template <typename Type>
Type add(Type first, Type second) {
    return first + second;
}
```
<!-- .element: class="fragment fade-in" -->

Instead of `Type`, you can have any name you wish. Typically you will see just `T` as a typename, but it is better to have a longer name than only one character, especially, when there is more than only one template parameter. Now, you can use this function like this:
<!-- .element: class="fragment fade-in" -->

```c++
auto resultI = add<int>(4, 5);  // resultI type is int
auto resultD = add<double>(4.0, 5.0);  // resultD type is double
auto resultC = add<std::complex<int>>({1, 2}, {2, 3});  // resultC type is std::complex<int>
```
<!-- .element: class="fragment fade-in" -->

You can play with the code [here](https://ideone.com/fork/NU0L8k)
<!-- .element: class="fragment fade-in" -->

___

## Function template type deduction

There is a function template types deduction in C++. It means that you can skip part with angle braces `<>` and write previous example like this:

```c++
auto resultI = add(4, 5);  // resultI type is int
auto resultD = add(4.0, 5.0);  // resultD type is double
auto resultC = add({1, 2}, {2, 3});  // error, does not compile
```

`resultC` will not compile, because in this case compiler will not know what is the type of `{1, 2}` or `{2, 3}`. `std::initializer_list` can never be a result of parametr type deduction in templates.
In this case we have to type it explicitly:
<!-- .element: class="fragment fade-in" -->

```c++
auto resultC = add(std::complex<int>{1, 2}, std::complex<int>{2, 3});
```
<!-- .element: class="fragment fade-in" -->

or
<!-- .element: class="fragment fade-in" -->

```c++
auto resultC = add<std::complex<int>>({1, 2}, {2, 3});
```
<!-- .element: class="fragment fade-in" -->

___

## Exercise

Write a function that creates `std::complex` number from two provided numbers. If the types of numbers are different, it should create `std::complex` of the first parameter. Usage:

```c++
std::complex<int> a = makeComplex(4, 5);        // both ints
std::complex<double> b = makeComplex(3.0, 2.0); // both doubles
std::complex<int> c = makeComplex(1, 5.0); // int, double -> takes int
```

___
<!-- .slide: style="font-size: 0.8em" -->

## Multiple template parameters

The compiler itself deduce which template function parameters should be used. However, if you write the code like this:

```c++
auto resultC = add(4, 5.0);  // error: int + double
```
<!-- .element: class="fragment fade-in" -->

We will have a compilation error. The compiler will not deduce parameter, because our template function takes only one type, and both parameters have to be of the same type. We can fix this by adding a new version of the template of add function.
<!-- .element: class="fragment fade-in" -->

```c++
template <typename TypeA, typename TypeB>
TypeA add(TypeA first, TypeB second) {
    return first + second;
}
```
<!-- .element: class="fragment fade-in" -->

Now the code should work:
<!-- .element: class="fragment fade-in" -->

```c++
auto resultC = add(4, 5.0);  // resultC type is int
```
<!-- .element: class="fragment fade-in" -->

The output type is the same as the first argument type because it was defined in the template function above as `TypeA`.
<!-- .element: class="fragment fade-in" -->

___

## `typeid`

Generally, you can freely use template types inside functions. For example, you can create new variables of provided types:

```cpp
#include <typeinfo>

template <class T>
void showType() {
    T value;
    std::cout << "Type: " << typeid(value).name() << std::endl;
}
```
<!-- .element: class="fragment fade-in" -->

You can use `typeid().name()` to print variable type. You need to include the `typeinfo` header for this. The output is implementation-defined.
<!-- .element: class="fragment fade-in" -->

You can also notice, that instead of the `typename` keyword, you can also use the `class` keyword. They are interchangeable.
<!-- .element: class="fragment fade-in" -->

```cpp
template <typename T> == template <class T> != template <struct T>
```
<!-- .element: class="fragment fade-in" -->

___
<!-- .slide: style="font-size: .9em" -->

## No matching function

In previous case if you want to use `showType()` function without providing explicit templates, the code will not compile:

```c++
int main() {
    showType();
    return 0;
}
```

```bash
prog.cpp: In function ‘int main()’:
prog.cpp:15:12: error: no matching function for call to showType()’
  showType();
           ^
prog.cpp:7:6: note: candidate: template<class T> void showType()
 void showType()
      ^~~~~~~~~
prog.cpp:7:6: note:   template argument deduction/substitution failed:
prog.cpp:15:12: note:   couldn't deduce template parameter ‘T’
  showType();
```

___

## Template function parameter type deduction

The compiler cannot deduce parameters, because the functions do not take any parameters. You need to provide the type explicitly:

<div style="display: flex; align-items:center;">

<div style="width: 50%">

```c++
int main() {
    doNothing<int>();
    return 0;
}
```

</div>

or

<div style="width: 50%">

```c++
int main() {
    doNothing<std::vector<char>>();
    return 0;
}
```

</div>

</div>
<!-- .element: class="fragment fade-in" -->

You can also play with the code [here](https://ideone.com/fork/oZZybw)
<!-- .element: class="fragment fade-in" -->

___

## STL example

```cpp
template<class InputIt, class UnaryPredicate>
InputIt find_if(InputIt first, InputIt last, UnaryPredicate p)
{
    for(; first != last; ++first) {
        if(p(*first)) {
            return first;
        }
    }
    return last;
}
```

```cpp
std::vector<std::pair<int, int>> v{{-3, 1}, {2, 3}, {4, -5}};
auto it = std::find_if(begin(v), end(v), [](auto& e){ return e.first == 2; });
if(it != std::end(v)) {
    /* ... */
}
```
<!-- .element: class="fragment fade-in" -->
