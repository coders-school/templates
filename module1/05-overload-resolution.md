So templates are overloading, right?
Yes and no.

Function templates participate in name resolution for overloaded functions, but the rules are different. For a template to be considered in overload resolution, the type has to match exactly. If the types do not match exactly, the conversions are not considered and the template is simply dropped from the set of viable functions. That’s what is known as “SFINAE” — Substitution Failure Is Not An Error. Example:


```cpp
#include <iostream>
#include <typeinfo>
template<typename T> void foo(T* x)
{ std::cout << "foo<" << typeid(T).name() << ">(T*)\n"; }
void foo(int x)
{ std::cout << "foo(int)\n"; }
void foo(double x)
{ std::cout << "foo(double)\n"; }
int main()
{
    foo(42);        // matches foo(int) exactly
    foo(42.0);      // matches foo(double) exactly
    foo("abcdef");  // matches foo<T>(T*) with T = char
    return 0;
}
```

In this example, foo<T> cannot be considered for the first or the second call to foo in the body of main because neither 42 nor 42.0 gives the compiler any information to deduce T. The third call, however, includes foo<T> with T = char and it wins.