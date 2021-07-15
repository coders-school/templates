#include <array>
#include <deque>
#include <list>
#include <vector>
#include <iostream>
#include <algorithm>


template<typename T>
using element_type_t = std::remove_reference_t<decltype(*std::begin(std::declval<T&>()))>;

template<typename T>
using element_type_t2 = typename T::value_type;

template<typename T>
struct Holder
{
    template<typename C>
    Holder(const C& c)
     : data{std::begin(c), std::end(c)}
    {
    }

    void print() const {
        std::copy(data.begin(), data.end(), std::ostream_iterator<T>(std::cout, " "));
    }
    std::vector<T> data;
};

template<typename C>
Holder(const C& c) -> Holder<element_type_t2<C>>;

int main()
{
    const std::list<int>        l{1, 2,3};
    const std::vector<int>      v{1, 2,3};
    const std::deque<int>       d{1, 2,3};
    const std::array<int, 3>    a{1, 2,3};
    // const int    ca[]{1, 2,3};

    const Holder h_l{l};
    const Holder h_v{v};
    const Holder h_d{d};
    const Holder h_a{a};

    h_l.print();
    h_v.print();
    h_d.print();
    h_a.print();
    // const Holder h_ca{ca};
}
