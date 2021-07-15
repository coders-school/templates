#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <type_traits>
#include "Circle.hpp"
#include "Rectangle.hpp"
#include "Shape.hpp"
#include "Square.hpp"

using namespace std;

using Collection = vector<shared_ptr<Shape>>;

void printCollectionElements(const Collection& collection) {
    for (auto it = collection.cbegin(); it != collection.cend(); ++it) {
        (*it)->print();
    }
}

void printAreas(const Collection& collection) {
    for (const auto& it : collection) {
        cout << it->getArea() << std::endl;
    }
}

template <typename Sh>
using RemoveCvRef = std::decay_t<Sh>;

template <typename Sh>
using IsDerivedFromShape = std::enable_if_t<std::is_base_of_v<Shape, RemoveCvRef<Sh>>>;

template <typename C>
using hasEmplaceBack = std::enable_if_t<std::is_member_function_pointer_v<decltype(&C::template emplace_back<typename C::value_type>)>>;

template< class, class = void >
struct has_emplace_back : std::false_type { };

template< class T >
struct has_emplace_back<T,
           std::void_t<decltype( std::declval<T>().hello() )>
       > : std::true_type { };

template <typename C>
using hasEmplaceBack2 = std::enable_if_t<has_emplace_back<C>::value>;


template <typename Sh,
          typename Coll,
        //   typename = IsDerivedFromShape<Sh>,
          typename = hasEmplaceBack<Coll>
        >
void insert(Sh&& shape, Coll& collection) {
    // static_assert(has_emplace_back<Coll>::value, "Has not emplace_back member");
    collection.emplace_back(make_shared<RemoveCvRef<Sh>>(shape));
}

template <typename Sh,
          typename Coll,
        //   typename = IsDerivedFromShape<Sh>,
          typename = hasPushBack<Coll>
        >
void insert(Sh&& shape, Coll& collection) {
    // static_assert(has_emplace_back<Coll>::value, "Has not emplace_back member");
    collection.emplace_back(make_shared<RemoveCvRef<Sh>>(shape));
}
template <typename Sh,
          typename Coll,
        //   typename = IsDerivedFromShape<Sh>,
        >
void insert(Sh&& shape, Coll& collection) {
    // static_assert(has_emplace_back<Coll>::value, "Has not emplace_back member");
    collection.emplace_back(make_shared<RemoveCvRef<Sh>>(shape));
}

template <typename Sh>
void insertC(Sh&& shape, Collection& collection) {
    if constexpr (std::is_base_of_v<Shape, RemoveCvRef<Sh>>) {
        collection.emplace_back(make_shared<RemoveCvRef<Sh>>(shape));
    } else {
        std::cout << "sorry\n";
    }
}

int main() {
    Collection shapes = {
        make_shared<Circle>(2.0, Color::GREEN),
        make_shared<Circle>(3.0),
        make_shared<Circle>(4.0),
        make_shared<Rectangle>(10.0, 5.0),
        make_shared<Square>(3.0),
        make_shared<Circle>(4.0),
    };

    const Square sq{5.0};
    insertC(sq, shapes);
    insertC(1, shapes);

    printCollectionElements(shapes);

    cout << "Areas before sort: " << std::endl;
    printAreas(shapes);

    std::sort(shapes.begin(), shapes.end(), [](auto first, auto second) {
        return (first->getArea() < second->getArea());
    });

    cout << "Areas after sort: " << std::endl;
    printAreas(shapes);

    auto square = make_shared<Square>(4.0);
    shapes.push_back(square);

    return 0;
}
