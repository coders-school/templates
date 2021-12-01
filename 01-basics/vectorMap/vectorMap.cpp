#include "vectorMap.hpp"

// this is not proper
// you should not have implementations of templates in cpp files
// template classes are not classes

template <typename KeyType, typename ValueType>
void VectorMap<KeyType, ValueType>::insert(KeyType&& key, ValueType&& value) {
    keys_.emplace_back(std::forward<KeyType>(key));
    values_.emplace_back(std::forward<ValueType>(value));
}

template <typename KeyType, typename ValueType>
ValueType& VectorMap<KeyType, ValueType>::operator[](KeyType key) {
    auto it = std::find(keys_.begin(), keys_.end(), key);
    if (it == keys_.end()) {
        keys_.emplace_back(std::forward<KeyType>(key));
        values_.emplace_back();
        return values_.back();
    }
    auto dist = std::distance(keys_.begin(), it);
    return values_[dist];
}

template <typename KeyType, typename ValueType>
ValueType& VectorMap<KeyType, ValueType>::at(KeyType key) {
    auto it = std::find(keys_.begin(), keys_.end(), key);
    if (it == keys_.end()) {
        throw std::out_of_range("No such element");
    }
    auto dist = std::distance(keys_.begin(), it);
    return values_[dist];
}
