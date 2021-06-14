#include <iostream>
#include "vectorMap.hpp"

class K {
public:
    K(int k) {}
};


int main()
{
    VectorMap<int, char> ic;
    ic.insert(4, 'a');
    std::cout << ic[4] << '\n';
    ic[4] = 'b';
    std::cout << ic[4] << '\n';
    std::cout << ic.at(4) << '\n';

    // VectorMap<int, K> kc;

    VectorMap<int, char>::key_type v1 = 10;

    std::cout << ic.is_int_key << '\n';
    std::cout << VectorMap<char, int>::is_int_key << '\n';

    std::cout << "is_int_key_v<VectorMap<int, char>>: " << is_int_key_v<VectorMap<int, char>> << '\n';
    std::cout << "is_int_key_v<decltype(ic)>: " << is_int_key_v<decltype(ic)> << '\n';
    std::cout << "is_int_key_v<VectorMap<char, char>>: " << is_int_key_v<VectorMap<char, char>> << '\n';

    VectorMap<bool, char> bc;
    bc.insert(true, 'a');
    std::cout << bc[true] << '\n';
    bc[true] = 'b';
    std::cout << bc[true] << '\n';
    std::cout << bc.at(true) << '\n';

    std::cout << bc.is_int_key << '\n';
    std::cout << VectorMap<bool, int>::is_int_key << '\n';

    return 0;
}
