<!-- .slide: data-background="#111111" -->

# Powtórka

<a href="https://coders.school">
    <img width="500" src="../img/coders_school_logo.png" alt="Coders School" class="plain">
</a>

___

## Punkty do zapamiętania

* <!-- .element: class="fragment fade-in" --> Szablon nie jest klasą ani funkcją. Szablon jest "wzorem", który kompilator wykorzystuje do generowania rodziny klas lub funkcji.
* <!-- .element: class="fragment fade-in" --> Aby kompilator mógł wygenerować kod, musi zobaczyć zarówno definicję szablonu (nie tylko deklarację), jak i specyficzne typy/cokolwiek używane do "wypełnienia" szablonu.
* <!-- .element: class="fragment fade-in" --> Templates itself are only instantiated upon usage. If some function/method was not used, it is not generated, even for class templates
* <!-- .element: class="fragment fade-in" --> Szablony są tworzone tylko podczas ich faktycznego użycia. Jeśli niektóre funkcje/metody nie są używane, to nie zostaną w ogóle wygenerowane. Co więcej, konkretna instancja klasy szablonowej może nie mieć wygenerowanych wszystkich metod!
* <!-- .element: class="fragment fade-in" --> Pełne specjalizacje są dozwolone zarówno dla szablonów klas, jak i funkcji
* <!-- .element: class="fragment fade-in" --> Częściowe specjalizacje są dozwolone tylko dla szablonów klas
* <!-- .element: class="fragment fade-in" --> Szukając możliwych przeciążeń w szablonach, kompilator rozważa tylko idealne dopasowania. Konwersje nie są rozważane.
* <!-- .element: class="fragment fade-in" --> <code>template &lt;typename T&gt;</code> == <code>template &lt;class T&gt;</code>
* <!-- .element: class="fragment fade-in" --> Biblioteka <code>type_traits</code> ma wiele przydatnych rzeczy. Używaj ich wraz ze <code>static_assert</code>.
