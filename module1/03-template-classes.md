<!-- .slide: data-background="#111111" -->

# Template classes

___

## Examples

Template classes are as well used to avoid code duplication, as to create so-called meta-programs within them. Here is an example of a simple template class and its usage:

```c++
#include <iostream>
using namespace std;

template <typename T>
class SomeClass {
public:
    T getValue() { return value; }
private:
    T value;
};

int main() {
    SomeClass<int> sc;
    std::cout << sc.getValue() << std::endl;
    return 0;
}
```

___

## Template classes in STL

Template classes are heavily used in STL. For example `std::vector`, `std::list` and other containers are template classes and if you want to use them, you do it like here:

```c++
std::vector<int> v = {1, 2, 3};
std::list<char> l{'c', 'd', 'b'};
```

___

## Exercise 2

Write a template class which create an over-engineered `std::map`. It should hold 2 `std::vectors` inside with the same size, each with different types. Usage should look like this:

```c++
VectorMap<int, char> map;
map.insert(1, 'c');
map[1] = 'e';  // replaces value under 1
std::cout << map[1];  // prints 'e'
map.at(2); // throw std::out_of_range
```

The first vector should hold keys, the other one values. Elements at the same position in both vectors should create a pair like 1 and 'c' above. Try to implement as much of `std::map` interface as possible, at least the mentioned above `insert`, `operator[]`, `at`

Use [cppreference](http://en.cppreference.com/w/cpp/container/map).
