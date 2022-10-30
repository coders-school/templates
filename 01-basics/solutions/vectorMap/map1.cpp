#include <algorithm>
#include <iostream>
#include <vector>
#include <optional>

// template <typename KeyType, typename ValueType>
// class VectorMap {
// public:
//     void insert(const KeyType& key, const ValueType& value) {
//         keys_.push_back(key);
//         values_.push_back(value);
//     }

//     ValueType& operator[](const KeyType& key) {
//         for (int i = 0; i < keys_.size(); ++i) {
//             if (keys_[i] == key)
//                 return values_[i];
//         }
//         keys_.push_back(key);
//         values_.push_back(ValueType{});
//         return values_.back();
//     }

//     ValueType& at(const KeyType& key) {
//         for (int i = 0; i < keys_.size(); ++i) {
//             if (keys_[i] == key)
//                 return values_[i];
//         }

//         std::string errorMsg = std::string("Key: ") + std::to_string(key) + std::string(" is out of range.");
//         throw std::out_of_range(errorMsg);
//     }

// private:
//     std::vector<KeyType> keys_;
//     std::vector<ValueType> values_;
// };

// template <typename Key, typename Value>
// class VectorMap {
// public:
//     // typename std::vector<Key>::iterator iterator;
//     using iterator = typename std::vector<Key>::iterator;

//     Value& operator[](const Key& key) {
//         if (auto found = find_key(key); found != keys_.end()) {
//             auto idx = std::distance(keys_.begin(), found);
//             return values_[idx];
//         }

//         keys_.push_back(key);
//         values_.push_back(Value{});
//         return values_.back();
//     }

//     std::pair<iterator, bool> insert(const Key& key, const Value& value) {
//         if (auto found = find_key(key); found != keys_.end()) {
//             return {found, false};
//         }

//         keys_.push_back(key);
//         values_.push_back(value);

//         return {keys_.end() - 1, true};
//     }
//     Value& at(const Key& key) {
//         if (auto found = find_key(key); found == keys_.end()) {
//             throw std::out_of_range("Map does not have provided key!");
//         } else {
//             auto idx = std::distance(keys_.begin(), found);
//             return values_[idx];
//         }
//     }

// private:
//     iterator find_key(const Key& key) {
//         return std::find(keys_.begin(), keys_.end(), key);
//     }

//     std::vector<Key> keys_;
//     std::vector<Value> values_;
// };

template <typename Key, typename Value, size_t Size = 0>
class VectorMap {
    static_assert(std::is_default_constructible_v<Value>, "Default constructor needed for Value");

    std::vector<Key> keys_;
    std::vector<Value> values_;

public:
    static constexpr bool isIntKey();

    void insert(const Key& key, const Value& value);
    Value& operator[](const Key& key);
    Value& at(const Key& key);

    static constexpr bool is_int_key = isIntKey();
};

template <typename Value>
class VectorMap<bool, Value> {
    static_assert(std::is_default_constructible_v<Value>, "Default constructor needed for Value");

    std::optional<Value> t_;
    std::optional<Value> f_ = std::nullopt;

public:
    VectorMap() {
        std::cout << "bool specialization\n";
    }

    static constexpr bool isIntKey() {
        return false;
    }

    void insert(bool key, const Value& value) {
        if (key) {
            t_ = value;
        } else {
            f_ = value;
        }
    }

    Value& operator[](bool key) {
        if (key) {
            if (!t_) {
                t_ = Value{};
            }
            return *t_;
        } else {
            if (!f_) {
                f_ = Value{};
            }
            return *f_;
        }
    }

    Value& at(bool key) {
        if (key) {
            if (!t_) {
                throw std::out_of_range("Key not found");
            }
            return *t_;
        } else {
            if (!f_) {
                throw std::out_of_range("Key not found");
            }
            return *f_;
        }
    }

    static constexpr bool is_int_key = false;
};

template<typename T>
constexpr bool is_int_key_v = T::is_int_key;

template<typename K, typename V>
constexpr bool is_int_key_v1 = VectorMap<K, V>::is_int_key;

template <typename Key, typename Value, size_t Size>
constexpr bool VectorMap<Key, Value, Size>::isIntKey() {
    return std::is_same_v<Key, int>;
}

// template <typename Value>
// constexpr bool VectorMap<int, Value>::isIntKey() {
//     return true;
// }

template <typename Key, typename Value, size_t Size>
void VectorMap<Key, Value, Size>::insert(const Key& key, const Value& value) {
    keys_.emplace_back(key);
    values_.emplace_back(value);
}

template <typename Key, typename Value, size_t Size>
Value& VectorMap<Key, Value, Size>::operator[](const Key& key) {
    auto it = std::find(begin(keys_), end(keys_), key);
    if (it == end(keys_)) {
        keys_.emplace_back(key);
        values_.emplace_back();
    }
    auto dist = std::distance(begin(keys_), it);
    return values_[dist];
}

template <typename Key, typename Value, size_t Size>
Value& VectorMap<Key, Value, Size>::at(const Key& key) {
    auto it = std::find(begin(keys_), end(keys_), key);
    if (it == end(keys_)) {
        throw std::out_of_range("Key not found");
    }
    auto dist = std::distance(begin(keys_), it);
    return values_[dist];
}

struct K {
    K(int) {}
};

// primary template
template <typename T1, typename T2, typename T3>
class A {};

// partial specialization with T1 = int
template <typename T2, typename T3>
class A<int, T2, T3> {};

// partial specialization with T1 = int and T2 = double
template <typename T3>
class A<int, double, T3> {};

// partial specialization with T1 = int and T3 = char
template <typename T2>
class A<int, T2, char> {};

// full specialization with T1 = T2 = double and T3 = int
template <>
class A<double, double, int> {};

template<class T> void f(T)     { std::cout << "f1\n"; }    // #1: overload for all types
template<class T> void f(T*)    { std::cout << "f3\n"; }   // #3: overload for all pointer types
template<>        void f(int*)  { std::cout << "f2\n"; } // #2: specialization of #1 for pointers to int


int main() {
    f(new int{1});
    A<int, int, char> a;
    VectorMap<int, char, 10> map;
    // VectorMap<int, K> map2;
    // map2[1];

    map.insert(1, 'c');
    std::cout << map[1] << '\n';  // prints 'e'
    map[1] = 'e';                 // replaces value under 1
    std::cout << map[1] << '\n';  // prints 'e'
    // map.at(2);                    // throw std::out_of_range
    std::cout << std::boolalpha << map.isIntKey() << '\n';  // prints 'e'

    VectorMap<char, char> map2;
    std::cout << std::boolalpha << map2.isIntKey() << '\n';
    std::cout << std::boolalpha << VectorMap<char, char>::is_int_key << '\n';
    std::cout << std::boolalpha << VectorMap<int, char>::is_int_key << '\n';

    VectorMap<bool, int> map3;
    map3.insert(true, 3);
    // map3.at(true);
    std::cout << map3[true] << '\n';  // prints 'e'
    map3[true] = 10;                 // replaces value under 1
    std::cout << map3[1] << '\n';  // prints 'e'

    std::cout << std::boolalpha << std::is_same_v<VectorMap<char, int>, VectorMap<int, int>> << '\n';

    // VectorMap<int, char> ic;
    // ic.begin();

    // std::vector v = {1, 2, 3};
    std::cout << std::boolalpha << is_int_key_v<VectorMap<char, char>> << '\n';
    std::cout << std::boolalpha << is_int_key_v<VectorMap<int, char>> << '\n';

    std::cout << std::boolalpha << is_int_key_v1<char, char> << '\n';
    std::cout << std::boolalpha << is_int_key_v1<int, char> << '\n';
    // std::cout << std::boolalpha << is_int_key_v<int> << '\n';

    return 0;
}
