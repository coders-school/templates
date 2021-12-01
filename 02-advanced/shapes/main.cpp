#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
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


int main() {
    Collection shapes = {
        make_shared<Circle>(2.0, Color::GREEN),
        make_shared<Circle>(3.0),
        make_shared<Circle>(4.0),
        make_shared<Rectangle>(10.0, 5.0),
        make_shared<Square>(3.0),
        make_shared<Circle>(4.0),
    };

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
