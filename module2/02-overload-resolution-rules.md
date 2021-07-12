<!-- .slide: data-background="#111111" -->

# Overload resolution rules

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___

<h2>Overload resolution</h2>

<pre><code class="cpp" data-trim data-line-numbers>
void foo(unsigned i) {
    std::cout &lt;&lt; "unsigned " &lt;&lt; i &lt;&lt; "\n";
}

template &lt;typename T&gt;
void foo(const T& t) {
    std::cout &lt;&lt; "template " &lt;&lt; t &lt;&lt; "\n";
}
</code></pre>

<p>What is the result of calling <code>foo(42)</code>?</p>
<p class="fragment"><code>template 42</code></p>
<p class="fragment">Why <code>const int &</code> is a better match than <code>unsigned</code>?</p>
<p class="fragment">Const reference can bind to r-values. No conversion is needed, there is an exact match, so this option is chosen.</p>

___

<h2>Overload resolution</h2>

<pre><code class="cpp" data-trim data-line-numbers>
void foo(unsigned i) {
    std::cout &lt;&lt; "unsigned " &lt;&lt; i &lt;&lt; "\n";
}

template &lt;typename T&gt;
void foo(T& t) {
    std::cout &lt;&lt; "template " &lt;&lt; t &lt;&lt; "\n";
}
</code></pre>

<p>What is the result of calling <code>foo(42)</code> now?</p>
<p class="fragment"><code>unsigned 42</code></p>
<p class="fragment">Why <code>unsigned</code> is a better match than <code>int &</code>?</p>
<p class="fragment">Reference (non-const) cannot bind to r-values. There is only one function matching. Implicit conversion from int to unsigned is applied.</p>

___

<h2>Overload resolution</h2>

<pre><code class="cpp" data-trim data-line-numbers>
void foo(unsigned i) {
    std::cout &lt;&lt; "unsigned " &lt;&lt; i &lt;&lt; "\n";
}

void foo(double i) {
    std::cout &lt;&lt; "double " &lt;&lt; i &lt;&lt; "\n";
}
</code></pre>

<p>What is the result of calling <code>foo(42)</code>?</p>
<p class="fragment"><code>error: call of overloaded ‘foo(int)’ is ambiguous</code></p>
<p class="fragment">Why?</p>
<p class="fragment">Promotion to double and conversion to unsigned are equally viable.</p>

___

## Function overloads vs function specializations

```cpp
template<class T> void f(T);    // #1: overload for all types
template<>        void f(int*); // #2: specialization of #1 for pointers to int
template<class T> void f(T*);   // #3: overload for all pointer types

f(new int{1});
```
<!-- .element: class="fragment fade-in" style="font-size: 1.3rem" -->

### Which function is chosen?
<!-- .element: class="fragment fade-in" -->

It calls #3, even though specialization of #1 would be a perfect match.
<!-- .element: class="fragment fade-in" -->

### Rules
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> Only non-template and primary template overloads participate in overload resolution
* <!-- .element: class="fragment fade-in" --> The specializations are not overloads and are not considered
* <!-- .element: class="fragment fade-in" --> Only after the overload resolution selects the best-matching primary function template, its specializations are examined to see if one is a better match
