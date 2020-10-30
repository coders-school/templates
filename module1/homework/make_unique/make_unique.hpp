#pragma once

#include <memory>
#include <type_traits>
#include <utility>

namespace coders {

template <typename T, typename... Args, typename = std::enable_if_t<!std::is_array_v<T>>>
auto make_unique(Args&&... args) {
    return std::unique_ptr<T>{new T{std::forward<Args>(args)...}};
}

template <typename T>
auto make_unique(size_t size) {
    return std::unique_ptr<T>{new typename std::remove_extent_t<T>[size]()};
}

}  // namespace coders