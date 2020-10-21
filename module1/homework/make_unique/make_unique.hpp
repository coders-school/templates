#pragma once

#include <memory>
#include <utility>
#include <type_traits>

namespace cs {

template <typename Type, class... Args>
std::enable_if_t<!std::is_array_v<Type>, std::unique_ptr<Type>>
make_unique(Args&&... args) {
    return std::unique_ptr<Type>(new Type(std::forward<Args>(args)...));
}

template<typename Type>
std::unique_ptr<Type> make_unique(std::size_t size) {
    return std::unique_ptr<Type>(new typename std::remove_extent<Type>::type[size]());
}

} //namespace cs
