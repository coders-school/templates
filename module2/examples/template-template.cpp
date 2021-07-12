#include <array>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>

template <typename T, template <typename...> typename Container>
class Holder {
    std::vector<T> v_;
public:
    Holder(const Container<T> & c)
        : v_{c.begin(), c.end()}
    {}

    template <size_t N>
    Holder(const std::array<T, N> & a)
        : v_{a.begin(), a.end()}
    {}

    void print() {
        std::copy(v_.begin(), v_.end(), std::ostream_iterator<T>(std::cout, " "));
    }
};

template <typename T, size_t N>
Holder(const std::array<T, N> & a) -> Holder<T, std::vector>;

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
