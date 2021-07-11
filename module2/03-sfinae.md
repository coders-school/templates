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
<p class="fragment">Compiler cannot substitute <code>42</code> as an argument to the second function. It would cause a compilation error. Therefore this overload is discarded.</p>
<p class="fragment">There is no compilation error - this is SFINAE works.</p>
<p class="fragment">If the first function is missing, there is a compilation error.</p>

___

## SFINAE

<p class="fragment">Substitution Failure Is Not An Error is a meta-programming technique.</p>
<blockquote class="fragment" cite="https://en.cppreference.com/w/cpp/language/sfinae">
    &ldquo;This rule applies during overload resolution of function templates: When substituting the explicitly specified or deduced type for the template parameter fails, the specialization is discarded from the overload set instead of causing a compile error.&rdquo;
    <small>-- <a href="https://en.cppreference.com/w/cpp/language/sfinae">cppreference.com</a></small>
</blockquote>
<p class="fragment"><strong>Rationale</strong>: have a universal interface without letting the caller to decide which implementation should be called. Selection of an optimal implementation is done by a compiler and is coded by a library creators.</p>

___

## `std::enable_if`

<p>C++11 has a metaprogramming helper struct - <code>std::enable_if</code>. It is a compile-time switch for enabling or disabling some templates.</p>
<pre class="fragment"><code class="cpp" data-trim data-line-numbers>
template &lt;bool Condition, class T = void&gt;
struct enable_if {};

template &lt;class T&gt;
struct enable_if&lt;true, T&gt; { using type = T; };
</code></pre>
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

___

## `enable_if` occurences

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

## `enable_if` occurences

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

<h2><code>type_traits</code> library</h2>
<p><a href="https://en.cppreference.com/w/cpp/header/type_traits">&lt;type_traits&gt; on cppreference.com</a></p>

___

## Task

<p>Write a function that allows inserting only subclasses of Shape to the collection. Other parameter types should not compile. Use SFINAE. Find proper type_traits.</p>
<p class="fragment">Hints:</p>
<ul>
    <li class="fragment"><code>std::is_base_of</code></li>
    <li class="fragment"><code>std::remove_reference</code></li>
    <li class="fragment"><code>std::remove_cv</code></li>
</ul>
