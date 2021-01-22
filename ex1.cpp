#include <iostream>
#include <complex>

template <typename RealType, typename ImagType>
auto makeComplex(RealType real, ImagType imag) {
    return std::complex<decltype(real)>{real, imag};
}

int main() {
    std::complex<int> a = makeComplex(4, 5);        // both ints
    std::complex<double> b = makeComplex(3.0, 2.0); // both doubles
    std::complex<int> c = makeComplex(1, 5.0);      // int, double -> takes int
    return 0;
}