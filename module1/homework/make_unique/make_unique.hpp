#pragma once

#include <memory>
#include <utility>

template <typename T, typename... Types>
auto make_unique(Types&&... args) {
    return std::unique_ptr<T>{new T{std::forward<Types>(args)...}};
}
