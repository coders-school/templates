#pragma once

#include <memory>
#include <type_traits>

namespace myMakeUnique {
template <typename Type, typename... Args, typename = std::enable_if_t<!std::is_array_v<Type>>>
std::unique_ptr<Type> make_unique(Args&&... args) {
    return std::unique_ptr<Type>(new Type(std::forward<Args>(args)...));
}

template <typename Type>
std::unique_ptr<Type> make_unique(std::size_t size) {
    return std::unique_ptr<Type>(new typename std::remove_extent<Type>::type[size]());
}
}  // namespace myMakeUnique
