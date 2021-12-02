<!-- .slide: data-background="#111111" -->

# `<type_traits>`

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___

## Ograniczenia

Biblioteka `<type_traits>` jest używana do sprawdzania własności typów. Zazwyczaj używa się jej w szablonach, aby uzyskać jakąś wiedzę na temat dostarczonych typów.
<!-- .element: class="fragment fade-in" -->

Z jej pomocą możemy np. sprawić, że nasze szablony zadziałają tylko z określonymi typami. Najłatwiej używać jej wraz ze `static_assert`.
<!-- .element: class="fragment fade-in" -->

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
<!-- .element: class="fragment fade-in" -->

___

## [`<type_traits>` na cppreference](https://en.cppreference.com/w/cpp/types#Type_traits)

___

## Zaawansowane ograniczenia

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

## Zadanie - `static_assert`

Dodaj ograniczenie do naszej `VectorMap`.

Nie pozwól na stworzenie jej, gdy `ValueType` nie posiada domyślnego konstruktora.

Użyj `static_assert` wraz z odpowiednim [`type_traitem`](https://en.cppreference.com/w/cpp/types#Type_traits)

Sprawdź, czy działa prawidłowo 🙂

___

## Zadanie - `isIntKey()`

Napisz metodą `isIntKey()` w `VectorMap`. Powinna ona zwracać `true` gdy `KeyType` jest `int`em i lub `false` w przeciwnym przypadku.

Przejrzyj listę [`<type_traits>`](https://en.cppreference.com/w/cpp/types#Type_traits) w poszukiwaniu inspiracji 🙂
