#include <complex>
#include <algorithm>
#include <vector>
#include "complexImpl.hpp"


int main() {
    std::vector<std::pair<int, int>> v{{-3, 1}, {2, 3}, {4, -5}};
    auto it = std::find_if(begin(v), end(v), [](auto& e){ return e.first == 2; });
    if(it != std::end(v)) {
        /* ... */
    }


    std::complex<int> a = makeComplex(4, 5);        // both ints
    std::complex<double> b = makeComplex(3.0, 2.0); // both doubles
    std::complex<int> c = makeComplex(1, 5.0); // int, double -> takes int
    return 0;
}
