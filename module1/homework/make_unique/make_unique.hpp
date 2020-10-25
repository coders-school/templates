#pragma once

#include <memory>
#include <type_traits>
#include <utility>

namespace cs {
template <typename T, typename... Types, typename = std::enable_if_t<!std::is_array_v<T>>>
auto make_unique(Types&&... args) {
    return std::unique_ptr<T>{new T{std::forward<Types>(args)...}};
}

template <typename T>
auto make_unique(size_t size) {
    return std::unique_ptr<T>{new std::remove_extent_t<T>[size] {}};
}

}  // namespace cs
