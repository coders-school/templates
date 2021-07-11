
template <typename T>
using removeCvRef = std::remove_cv_t<std::remove_reference_t<T>>;
template <typename T>
using isBaseOfShape = std::enable_if_t<std::is_base_of_v<Shape, removeCvRef<T>>>;

template <
    class T,
    typename = isBaseOfShape<T>
>
void insert(T&& item, Collection& collection) {
    collection.emplace_back(make_shared<removeCvRef<T>>(item));
}

template <class T>
void insertC(T&& item, Collection& collection) {
    if constexpr (std::is_base_of_v<Shape, removeCvRef<T>>)
        collection.emplace_back(make_shared<removeCvRef<T>>(item));
    else
        std::cout << "Sorry\n";
}



    const Square s{400.0};
    insertC(s, shapes);
    insertC(Rectangle{4.0, 50.0}, shapes);
    insertC(4, shapes);     // compilation doesn't fail. Function is empty for int.