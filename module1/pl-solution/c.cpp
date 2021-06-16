#include "c.hpp"

template <typename Type, typename TypeB>
std::complex<Type> makeComplex(Type a, TypeB b) {
    return std::complex<Type>{a, b};
}
