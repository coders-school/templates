#pragma once

#include <memory>
#include <utility>

namespace cs {

template <typename Type, class... Args>
std::unique_ptr<Type> make_unique(Args&&... args) {
    return std::unique_ptr<Type>(new Type(std::forward<Args>(args)...));
}

} //namespace cs
