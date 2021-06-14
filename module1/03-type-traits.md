<!-- .slide: data-background="#111111" -->

# `<type_traits>`

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___

## Constraints

`<type_traits>` library is used to examine type properties. It is usually used in templates to gain some knowledge about provided types.

We can for example constrain our templates to work only with some specific types. The common practice is using it together with `static_assert`.

```cpp
#include <type_traits>

template <typename E>
class Choice {
    static_assert(std::is_enum<E>::value, "You need to provide an enum");

    E choice;
public:
    Choice(E arg) { /* ... */ }
};
```

___

## [`<type_traits>` on cppreference](https://en.cppreference.com/w/cpp/types#Type_traits)

___

## Advanced constraints

* [SFINAE](https://en.cppreference.com/w/cpp/language/sfinae)
* [`constexpr if`](https://en.cppreference.com/w/cpp/language/if#Constexpr_if)
* [named requirements](https://en.cppreference.com/w/cpp/named_req) (C++20)
* [`concept`](https://en.cppreference.com/w/cpp/concepts) (C++20)

```cpp
template <class T>
concept copy_constructible =
  std::move_constructible<T> &&
  std::constructible_from<T, T&> && std::convertible_to<T&, T> &&
  std::constructible_from<T, const T&> && std::convertible_to<const T&, T> &&
  std::constructible_from<T, const T> && std::convertible_to<const T, T>;
```


___

## Exercise - `static_assert`

Add a constraint to our VectorMap.

Do not allow to create an object when `ValueType` does not have a default constructor.

Use `static_assert` and proper trait from [`<type_traits>`](https://en.cppreference.com/w/cpp/types#Type_traits) library.

Check if it works properly.

## Exercise - `isIntKey()`

Write a function `isIntKey()`. It should return `true` when the KeyType is `int` and `false` otherwise.

Check the [`<type_traits>`](https://en.cppreference.com/w/cpp/types#Type_traits) library for some inspiration 🙂
