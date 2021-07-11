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
