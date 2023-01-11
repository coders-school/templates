<!-- .slide: data-background="#111111" -->

# Post-work

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___
<!-- .slide: style="font-size: 0.85em" -->
## `make_unique`

Zaimplementuj funkcję `make_unique`. Powinna być w stanie przyjąć dowolną liczbę parametrów i powinna zwracać `unique_ptr` dla danego typu. Należy stworzyć obiekt danego typu i przekazać mu wszystkie parametry do konstruktora. Pamiętaj o perfect forwardingu.

Głównym wyzwaniem jest prawidłowe napisanie testów jednostkowych dla l-value i r-value, które pokryje wszystkie przypadki.

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

### Code review

Wyślij na Discordzie na kanale `#szablony` link do repozytorium z twoją implementacją, abym ja lub inni kursanci rzucili na nią okiem i powiedzieli czy jest ok, czy jeszcze coś trzeba poprawić 🙂

___

## Post-test

[Link do testu](https://forms.gle/jPk9ntqhdTVtbVvv5)
