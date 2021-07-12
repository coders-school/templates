#include <array>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>

template <typename T>
class Holder {
    std::vector<T> v_;
public:
    template <typename Container>
    Holder(const Container & c)
        : v_{c.begin(), c.end()}
    {}

    void print() {
        std::copy(v_.begin(), v_.end(), std::ostream_iterator<T>(std::cout, " "));
    }
};

template <typename Container>
Holder(const Container & c) -> Holder<typename Container::value_type>;


int main() {
    std::vector v {1, 2, 3, 4, 5};
    std::list l {1.1, 2.2, 3.3};
    std::array a {9, 8, 7, 6};
    Holder h1{v};
    Holder h2{l};
    Holder h3{a};
    h1.print();
    h2.print();
    h3.print();
    return 0;
}
