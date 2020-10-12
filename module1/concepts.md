<!-- .slide: data-background="#111111" -->

# Concepts

___

## Concepts

Right now when we need special checks on types, it is usually done by using `<type_traits>` library.

Concepts are introduced in C++20 to help programmers to apply a specific requirements on types in templates. Named sets of such requirements are called **concepts**.

Variadic templates can be used to create template functions or classes which accept any numer of arguments of any type.

There are 2 new keywords: `concept` and `requires`.

**There will one major advantage of concepts. Error messages from templates will not take a few pages to read. They will be very readable and meaningful one-liners 🙂.**

Check an example on [cppreference.com](https://en.cppreference.com/w/cpp/language/constraints)
