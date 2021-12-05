<!-- .slide: data-background="#111111" -->

# Post-work

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___

## `vector` - klasa szablonowa

Zaimplementuj swój własny `vector<T>`. Powinien on zachowywać się dokładnie tak samo jak `std::vector`.

W celu uproszczenia implementacji możesz wewnątrz użyć dynamicznie alokowanej zwykłej tablicy.

Pamiętaj o typach zdefiniowanych wewnątrz wektora.

Pamiętaj o specjalizacji dla `bool`.

Nie musisz implementować wszystkich możliwych przeciążeń dla funkcji.

### Bonusowe wymagania (niestety nie oceniane)

* Dodaj obsługę alokatorów poprzez zdefiniowane dodatkowego typu szablonowego - `Allocator`.
* Użyj `placement new`, aby odpowiednio zarządzać pamięcią. Dzięki niemu możesz tworzyć elementy wektora w uprzednio zaalokowanej, ale jeszcze nie wykorzystywanej pamięci (capacity).

___

## `remove` - funkcja szablonowa

Zaimplementuj własną funkcję `remove()`. Powinna robić to samo co algorytm `std::remove()`.
