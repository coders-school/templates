<!-- .slide: data-background="#111111" -->

# SFINAE

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___

## Simple SFINAE example

<pre><code class="cpp" data-trim data-line-numbers>
template &lt;typename T&gt;
void foo(T arg) {}

template &lt;typename T&gt;
void foo(T* arg) {}
</code></pre>

<p class="fragment">Calling <code>foo(42)</code> makes a compiler to generate two functions.</p>
<pre class="fragment"><code class="cpp" data-trim data-line-numbers>
void foo(int arg) {}
void foo(int* arg) {}
</code></pre>

The compiler cannot substitute `42` as an argument to the second function. It would cause a compilation error. Therefore this overload is discarded.
<!-- .element: class="fragment fade-in" -->

There is no compilation error - this is how SFINAE works.
<!-- .element: class="fragment fade-in" -->

If the first function is missing, there is a compilation error.
<!-- .element: class="fragment fade-in" -->

___

## SFINAE

<p class="fragment">Substitution Failure Is Not An Error is a meta-programming technique.</p>

> This rule applies during overload resolution of function templates: When substituting the explicitly specified or deduced type for the template parameter fails, the specialization is discarded from the overload set instead of causing a compile error.
>
> -- <a href="https://en.cppreference.com/w/cpp/language/sfinae">cppreference.com</a>

<p class="fragment"><strong>Rationale</strong>: have a universal interface without letting the caller to decide which implementation should be called. The selection of an optimal implementation is done by a compiler and is coded by library creators.</p>

___

<h2><code>type_traits</code> library</h2>
<p><a href="https://en.cppreference.com/w/cpp/header/type_traits">&lt;type_traits&gt; on cppreference.com</a></p>

___

## `std::enable_if`

<p>C++11 has a metaprogramming helper struct - <code>std::enable_if</code>. It is a compile-time switch for enabling or disabling some templates.</p>

```cpp
template <bool Condition, class T = void>;
struct enable_if {};

template <class T>
struct enable_if<true, T> { using type = T; };
```
<!-- .element: class="fragment fade-in" -->

<ul>
    <li class="fragment">If <code>Condition</code> is <code>true</code>, accessing internal type by <code>enable_if&lt;Condition, T&gt;::type</code> is valid.</li>
    <li class="fragment">If <code>Condition</code> is <code>false</code>, accessing internal type by <code>enable_if&lt;Condition, T&gt;::type</code> is invalid and substitution is not correct - SFINAE works.</li>
</ul>

___

## `std::enable_if_t`

<p>C++14 defines a helper type:</p>
<pre><code data-trim data-line-numbers>
template &lt;bool B, class T = void&gt;
using enable_if_t = typename enable_if&lt;B, T&gt;::type;
</code></pre>
<p class="fragment">Using both is equivalent.</p>

```cpp []
template <
    typename T,
    typename std::enable_if<std::is_integral<T>::value, T>::type* = nullptr
> void function(T& t) {}
```
<!-- .element: class="fragment fade-in" -->

```cpp []
template <
    typename T,
    typename std::enable_if_t<std::is_integral_v<T>, T>* = nullptr
> void function(T& t) {}
```
<!-- .element: class="fragment fade-in" -->

<p class="fragment">Why <code>* = nullptr</code>?</p>

Note:

Show in IDE

```cpp
// function(4) generates this implicit instantiation
template <
    int,
    typename std::enable_if<std::is_integral<int>::value, int>::type* = nullptr
> void function(int& t) {}

template <
    int,
    int* = nullptr
> void function(int& t) {}
```

___

## `enable_if` variations

<pre class="fragment"><code class="cpp" data-trim>
template&lt;class T&gt;     // #1 return type
auto construct(T* t) -&gt;
typename std::enable_if_t&lt;std::has_virtual_destructor_v&lt;T&gt;, T&gt;*
{ return new T{}; }
</code></pre>
<pre class="fragment"><code class="cpp" data-trim>
template&lt;class T&gt;     // #2 parameter
T* construct(
    T* t,
    typename std::enable_if_t&lt;std::has_virtual_destructor_v&lt;T&gt;&gt;* = nullptr
) { return new T{}; }
</code></pre>
<pre class="fragment"><code class="cpp" data-trim>
template&lt;
    class T,          // #3 template parameter - usual choice from C++11
    typename std::enable_if_t&lt;std::has_virtual_destructor_v&lt;T&gt;&gt;* = nullptr
&gt; T* construct(T* t)
{ return new T{}; }
</code></pre>

___

## `enable_if` variations

<p>The most elegant way</p>
<pre class="fragment"><code class="cpp" data-trim>
template &lt;typename T&gt;
using HasVirtDtor = std::enable_if_t&lt;std::has_virtual_destructor_v&lt;T&gt;&gt;;
</code></pre>

<pre class="fragment"><code class="cpp" data-trim>
template&lt;
    class T,          // the same as #3 - template parameter
    typename = HasVirtDtor&lt;T&gt;
&gt; T* construct(T* t)
{ return new T{}; }
</code></pre>

___

## Concepts (C++20)

```cpp
template <class T>
concept HasVirtualDtor = std::has_virtual_destructor_v<T>;

template <HasVirtualDtor T>
T* construct(T* t)
{ return new T{}; }
```

From C++20 concepts should replace the usage of `std::enable_if`.

___

## Task

Take a look into `module2/shapes` directory.

Write a function `insert()` in `main.cpp` that allows inserting only subclasses of Shape to the collection. Parameters other than `Circle`, `Square` or `Rectangle` should not compile. Use SFINAE. Use proper type_traits.

The function should create a `shared_ptr` of the Shape passed as the first parameter and put it in the collection, which should be provided as the second parameter.

<p class="fragment">Hints:</p>
<ul>
    <li class="fragment"><code>std::is_base_of</code></li>
    <li class="fragment"><code>std::remove_reference</code></li>
    <li class="fragment"><code>std::remove_cv</code></li>
</ul>

___

## Conclusions

* <!-- .element: class="fragment fade-in" --> SFINAE is a very powerful and difficult technique
* <!-- .element: class="fragment fade-in" --> Proper usage may not be too ugly 🥴
* <!-- .element: class="fragment fade-in" --> Where applicable, tag dispatch, static_assert, and concepts, are usually preferred over the direct use of SFINAE
