#include <array>
#include <deque>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

template <typename T, typename A>
class Dummy {};

template <typename T, template <typename...> typename Container, typename A = std::allocator<T>>
class Holder {
public:
    Holder(Container<T, A> c)
        : data{std::begin(c), std::end(c)} {}

    template <std::size_t N>
    Holder(const std::array<T, N>& list)
        : data{std::begin(list), std::end(list)} {
    }

    void print() const {
        for (auto& element : data) {
            cout << element;
        }
    }

private:
    vector<T> data;
};

template <typename T, std::size_t N>
Holder(const std::array<T, N>& list) -> Holder<T, Dummy>;

int main() {
    const std::list<int> l{1, 2, 3};
    const std::vector<int> v{1, 2, 3};
    const std::deque<int> d{1, 2, 3};
    std::array<int, 3>    a{1, 2,3};
    // const int    ca[]{1, 2,3};

    const Holder h_l{l};
    const Holder h_v{v};
    const Holder h_d{d};
    Holder h_a{a};
    // const Holder h_ca{ca};

    h_l.print();
    h_a.print();
    // h_v.print();
    // h_d.print();

    return 0;
}