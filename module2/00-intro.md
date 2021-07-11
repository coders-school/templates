## Something about you

* Have you ever seen a SFINAE in a code?
* What do you expect from today's session?

___
<!-- .slide: data-background="../img/lukin.jpg" -->

<h2 style = "text-shadow: 2px 2px black;"> Łukasz Ziobroń </h2>
<div class="box fragment" style="width: 45%; left: 0; top: 100px;">

### Not only a programming XP

* Front-end dev, DevOps & Owner @ Coders School
* C++ and Python developer @ Nokia & Credit Suisse
* Team leader & Trainer @ Nokia
* Scrum Master @ Nokia & Credit Suisse
* Code Reviewer @ Nokia
* Web developer (HTML, PHP, CSS) @ StarCraft Area

</div>

<div class="box fragment" style="width: 45%; right: 0; top: 100px;">

### Experience as a trainer

* <a href="https://coders.school/kurs-online">C++ online course</a> @ Coders School
* Company trainings @ Coders School
* Practical Aspects Of Software Engineering @ PWr & UWr
* Nokia Academy @ Nokia

</div>

<div class="box fragment" style="width: 45%; left: 0; top: 400px;">

### Public speaking experience

* code::dive conference
* code::dive community
* Academic Championships in Team Programming
* <a href="http://youtube.com/c/CodersSchool">Coders School YouTube channel</a>

</div>

<div class="box fragment" style="width: 45%; right: 0; top: 400px;">

### Hobbies

* StarCraft Brood War & StarCraft II
* Motorcycles
* Photography
* Archery
* Andragogy

</div>

___

## Contract

* <!-- .element: class="fragment fade-in" --> 🎰 Vegas rule
* <!-- .element: class="fragment fade-in" --> 🗣 Discussion, not a lecture
* <!-- .element: class="fragment fade-in" --> ☕️ Additional breaks on demand
* <!-- .element: class="fragment fade-in" --> ⌚️ Be on time after breaks

___

## Pre-test 1/3 🤯

### Which of the following usages of a template function are correct?

```cpp
template <typename T, typename U>
U fun(T arg1, U arg2);
```

1. <code>fun(4, 5)</code>
2. <code>fun(4, 5.5)</code>
3. <code>fun&lt;int, int&gt;(4, 5)</code>
4. <code>fun&lt;int, double&gt;(4, 5.5)</code>
5. <code>fun&lt;int, int&gt;(4, 5.5)</code>

___
<!-- .slide: style="font-size: 0.9em" -->

## Pre-test 2/3 🤯

### Which of the following usages of a template function are correct?

```cpp
template <typename T, typename U, typename V>
V fun(T arg1, U arg2);
```

1. <code>fun(4, 5.5)</code>
2. <code>fun(4, 5.5, int)</code>
3. <code>fun(4, 5.5, 'c')</code>
4. <code>fun&lt;int, double, int&gt;(4, 5.5)</code>
5. <code>fun&lt;int, double, char&gt;(4, 5.5)</code>
6. <code>fun&lt;int, double, char&gt;(4, 5.5, 'c')</code>
7. <code>fun&lt;char&gt;(4, 5.5)</code>
8. <code>fun&lt;V = char&gt;(4, 5.5)</code>

___
<!-- .slide: style="font-size: 0.95em" -->

## Pre-test 3/3 🤯

### Which of the following usages of a template function are correct?

```cpp
template<typename To, typename From>
To convert(From f);
```

1. <code>auto a = convert(3.14);</code>
2. <code>auto b = convert&lt;int&gt;(3.14);</code>
3. <code>auto c = convert&lt;int, double&gt;(3.14);</code>
4. <code>int(*p1)(float) = convert;</code>
5. <code>int(*p2)(float) = convert&lt;int, float&gt;;</code>
