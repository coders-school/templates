#include <deque>
#include <forward_list>
#include <array>
#include <iostream>
#include <list>
#include <vector>

template <typename T> class Holder {
public:
  template <template <typename> typename Container>
  Holder(Container<T> &&list) {
    for (auto const &value : list)
      values.push_back(value);
  }

  template <std::size_t N>
  Holder(std::array<T, N> &&list) {
    for (auto const &value : list)
      values.push_back(value);
  }

  void print() {
    for (auto const &value : values)
      std::cout << value << '\n';
  }

  std::vector<T> values;
};

int main() {
  Holder h{std::initializer_list{1, 2, 3}};
  h.print();

  Holder h2{std::list{1, 2, 3}};
  h2.print();

  Holder h3{std::deque{1, 2, 3}};
  h3.print();

  Holder h4{std::forward_list{1, 2, 3}};
  h4.print();

  Holder h5{std::array{1, 2, 3}};
  h5.print();
}
