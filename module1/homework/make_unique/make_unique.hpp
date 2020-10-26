#include <memory>

namespace  cs {

    template<typename T, typename... Args, typename = std::enable_if_t<!std::is_array_v<T>>>
    std::unique_ptr <T> make_unique(Args &&... args) {
        return std::unique_ptr<T>{new T{std::forward<Args>(args)...}};
    }

    template<typename T>
    std::unique_ptr <T> make_unique(size_t size) {
        return std::unique_ptr<T>{new std::remove_extent_t<T>[size] {}};
    }
}