#pragma once
#include <complex>

template <typename TypeA, typename TypeB>
std::complex<TypeA> makeComplex(TypeA a, TypeB b) {
    return std::complex<TypeA>{a, b};
}