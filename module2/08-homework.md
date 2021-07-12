<!-- .slide: data-background="#111111" -->

# Post-work

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___

## `make_unique`

Implement `make_unique` function. It should be able to take any number of parameters and it should return a unique_ptr to the given type. The object of the given type should be created with all parameters passed to it.
The main challenge is to properly unit tests for l-values and r-values.

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


___

### Code Review

Send me a link to the repository with your implementation for my code review.

#### [lukasz@coders.school](mailto:lukasz@coders.school)

___

## Post-test

The link will be sent after the training with all materials.
