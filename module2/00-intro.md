## Something about you

* Have you ever seen/used the SFINAE technique?
* Have you heard about a static polymorphism?
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

### Is this code correct?

```cpp
template<typename... Args> bool f(Args... args) {
    return (args && ... && args);
}
```

1. Yes
2. No, the parameter pack is used twice in fold-expression
3. No, the ellipsis operator is used incorrectly in fold-expression
4. No, <code>Args&&</code> should be used as a function argument

___
<!-- .slide: style="font-size: 0.9em" -->

## Pre-test 2/3 🤯

### What is the output of this program?

```cpp
#include <iostream>

template <typename T>
void fun(T)
{
  static int i;
  std::cout << ++i;
}

int main()
{
  fun(1);
  fun(1.0);
  fun(1);
}
```

___
<!-- .slide: style="font-size: 0.8em" -->

## Pre-test 3/3 🤯

### Mark true statements about this code

```cpp
template<typename T> class MyDeleter {};
template<typename T, typename Policy> class Handle { /* ... */ };
Handle<FILE, MyDeleter> h;
```

1. This code compiles
2. <code>MyDeleter</code> cannot be used as a <code>Policy</code> template argument
3. <code>template&lt;typename T, template typename Policy&gt;</code> - this should make this code work
4. <code>template&lt;typename T, template &lt;typname ...&gt; typename Policy&gt;</code> - this should make this code work
5. <code>template&lt;typename T, template &lt;typname&gt; typename Policy&gt;</code> - this should make this code work
