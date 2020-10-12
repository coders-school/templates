# Post-work

## `make_unique` (40 XP)

Implement `make_unique` function. It should be able to take any numer of parameters and it should return a unique_ptr with a given type. The object of a given type should be created with all parameters passed to it.
The main challenge is to properly unit tests for l-values and r-values. Do not forget about CI.

```cpp
struct MyType {
    MyType(int&, double&&, bool) { std::cout << "lvalue, rvalue, copy\n"; }
    MyType(int&&, double&, bool) { std::cout << "rvalue, lvalue, copy\n"; }
};

int main(){
    int lvalue{2020};
    std::unique_ptr<int> uniqZero = make_unique<int>();
    auto uniqEleven = make_unique<int>(2011);
    auto uniqTwenty = make_unique<int>(lvalue);
    auto uniqTypeLRC = make_unique<MyType>(lvalue, 3.14, true);
    auto uniqTypeRRC = make_unique<MyType>(2020, 3.14, true);
}
```
