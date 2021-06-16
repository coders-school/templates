#include <complex>
#include <iostream>
#include <iomanip>
#include "c.hpp"

//generic function
template <typename T>
void print(T arg) {
    std::cout << arg << '\n';
}

template <>
void print<double>(double arg) {
    std::cout << arg << '\n';
}

// better: overload
void print(double arg) {
    std::cout << std::setprecision(10) << arg << " overload " << '\n';
}

template <typename T, typename U, typename V>
V fun(T arg1, U arg2)
{}

template<typename To, typename From>
To convert(From f) { return {}; }

int main() {
    // int aa = fun(4, 5.5);
    int(*p1)(float) = convert;

    print(1.1);
    std::complex<int> a = makeComplex(4, 5);        // both ints
    std::complex<double> b = makeComplex(3.0, 2.0); // both doubles
    std::complex<int> c = makeComplex(1, 5.0); // int, double -> takes int

    return 0;
}
