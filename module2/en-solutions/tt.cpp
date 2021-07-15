#include <array>
#include <iostream>
#include <iterator>
#include <list>
#include <set>
#include <vector>

// template <template <typename, typename> typename Container, typename T, typename A = std::allocator<T>>
// class Holder {
// public:
//     Holder(Container<T, A> container)
//         : members{container.begin(), container.end()} {
//     }

//     template <size_t N = 0>
//     Holder(std::array<T, N> container)
//         : members{container.begin(), container.end()} {
//     }

//     void print() {
//         std::copy(begin(members), end(members), std::ostream_iterator<T>(std::cout, " "));
//         std::cout << '\n';
//     }

// private:
//     std::vector<T> members;
// };

// template <typename T, size_t N = 0>
// Holder(std::array<T, N> container) -> Holder<std::vector, T, std::allocator<T>>;

template <typename T>
class Holder {
    std::vector<T> v_;

public:
    template <typename Container>
    Holder(const Container& container)
        : v_{container.begin(), container.end()} {
            // static_assert(!std::is_same_v<Container, std::set<char>>);
    }

    template <typename ... Args>
    Holder(Args ... args)
        : v_{args...} {
    }

    void print() {
        std::copy(v_.begin(), v_.end(), std::ostream_iterator<T>(std::cout, " "));
    }
};

template <typename Container>
Holder(const Container& container) -> Holder<typename Container::value_type>;

int main() {
    Holder<int> h9{1, 2, 3, 4, 5};
    h9.print();

    std::vector<int> v = {1, 2, 3};
    Holder h{v};
    h.print();

    std::list<char> l = {'a', 'b', 'z', 'f'};
    Holder h2{l};
    h2.print();

    std::array a = {'a', 'b', 'z', 'f', 'e'};
    Holder h3{a};
    h3.print();

    std::set<char> s = {'a', 'b', 'z', 'f'};
    Holder h4{s};
    h4.print();

    return 0;
}
