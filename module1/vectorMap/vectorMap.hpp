#pragma once

#include <vector>
#include <type_traits>

template <typename KeyType, typename ValueType, int Size = 0>   // size - ?
class VectorMap {
    static_assert(std::is_default_constructible<ValueType>::value,
                  "ValueType must have the default constructor");     // type_traits #1

    std::vector<KeyType> keys_;
    std::vector<ValueType> values_;

public:
    using iterator = typename std::vector<KeyType>::iterator;  // dependent type name
    using key_type = KeyType;
    using mapped_type = ValueType;
    using value_type = std::pair<const KeyType, ValueType>;

    static constexpr bool is_int_key = std::is_same_v<KeyType, int>;  // type_traits #2

    VectorMap() {   // int param
        keys_.reserve(Size);
        values_.reserve(Size);
        std::cout << keys_.capacity() << '\n';
    }

    void insert(KeyType&& key, ValueType&& value) {
        // what about duplication?
        keys_.emplace_back(std::forward<KeyType>(key));
        values_.emplace_back(std::forward<ValueType>(value));
    }

    ValueType& operator[](KeyType key) {
        auto it = std::find(keys_.begin(), keys_.end(), key);
        if (it == keys_.end()) {
            keys_.emplace_back(std::forward<KeyType>(key));
            values_.emplace_back();
            return values_.back();
        }
        auto dist = std::distance(keys_.begin(), it);
        return values_[dist];
    }

    ValueType& at(KeyType key) {
        auto it = std::find(keys_.begin(), keys_.end(), key);
        if (it == keys_.end()) {
            throw std::out_of_range("No such element");
        }
        auto dist = std::distance(keys_.begin(), it);
        return values_[dist];
    }
};

template <typename ValueType>
class VectorMap<bool, ValueType> {      // specialization
    static_assert(std::is_default_constructible<ValueType>::value,
                  "ValueType must have the default constructor");

    ValueType t_;
    ValueType f_;

public:
    static constexpr bool is_int_key = false;  // type_traits #2

    VectorMap() {
        std::cout << "bool specialization used\n";
    }

    void insert(bool key, ValueType&& value) {
        if (key) {
            t_ = value;
        } else {
            f_ = value;
        }
    }

    ValueType& operator[](bool key) {
        if (key) {
            return t_;
        }
        return f_;
    }

    ValueType& at(bool key) {
        if (key) {
            return t_;
        }
        return f_;
    }
};

template <class Map>
inline constexpr bool is_int_key_v = Map::is_int_key;
