#pragma once

#include <memory>
#include <type_traits>

namespace cs
{
    template<typename ObjectType, typename... ArgTypes>
    std::enable_if_t<!std::is_array_v<ObjectType>, std::unique_ptr<ObjectType>>
    make_unique(ArgTypes&&... args) {
        return std::unique_ptr<ObjectType>(new ObjectType{std::forward<ArgTypes>(args)...});
    }

    template<typename ArrayType, std::enable_if_t<std::is_array_v<ArrayType>, int> = 0>
    std::unique_ptr<ArrayType> make_unique(size_t size) {
        return std::unique_ptr<std::remove_extent_t<ArrayType>[]>(new std::remove_extent_t<ArrayType>[size]);
    }
}
