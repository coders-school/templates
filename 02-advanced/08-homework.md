<!-- .slide: data-background="#111111" -->

# Post-work

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___

## `make_unique`

Zaimplementuj funkcję `make_unique`. Powinna być w stanie przyjąć dowolną liczbę parametrów i powinna zwracać wartość `unique_ptr` dla danego typu. Należy stworzyć obiekt danego typu z przekazanymi mu wszystkimi parametrami.
Głównym wyzwaniem jest prawidłowe wykonanie testów jednostkowych dla l-values i r-values.

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

### Przegląd kodu

Wyślij mi link do repozytorium z twoją implementacją do mojej recenzji kodu.

#### [lukasz@coders.school](mailto:lukasz@coders.school)

___

## Post-test

Link zostanie przesłany po szkoleniu wraz ze wszystkimi materiałami.
