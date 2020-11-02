#pragma once

#include <memory>

namespace cs
{
    template<typename ObjectType, typename... ArgTypes>
    std::unique_ptr<ObjectType> make_unique(ArgTypes&&... args) {
        return std::unique_ptr<ObjectType>(new ObjectType{std::forward<ArgTypes>(args)...});
    }
}
