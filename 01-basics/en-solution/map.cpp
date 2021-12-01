#include <algorithm>
#include <iostream>
#include <type_traits>
#include <vector>

template <typename Key, typename Value>
class VectorMap {
    std::vector<Key> keys_;
    std::vector<Value> values_;

    static_assert(std::is_default_constructible<Value>::value, "Value should have the default constructor");
    static_assert(std::is_default_constructible_v<Value>, "Value should have the default constructor");

public:
    using K = Key;
    using V = Value;
    template <typename T>
    using iterator = typename std::vector<T>::iterator;

    void insert(const Key& k, const Value& v) {
        keys_.emplace_back(k);
        values_.emplace_back(v);
    }

    static constexpr bool isIntKey() {
        // if (std::is_integral_v<Key>) {
        if (std::is_same_v<Key, int>) {
            return true;
        }
        return false;
    }

    Value& operator[](const Key& k);
    Value& at(const Key& k);

    static constexpr bool is_int_key = std::is_same_v<Key, int>;
};

template <typename Key, typename Value>
Value& VectorMap<Key, Value>::operator[](const Key& k) {
    auto it = std::find(std::begin(keys_), std::end(keys_), k);
    if (it == std::end(keys_)) {
        keys_.emplace_back(k);
        values_.emplace_back(Value{});
        return values_.back();
    }
    auto dist = std::distance(keys_.begin(), it);
    return values_[dist];
}

template <typename Key, typename Value>
Value& VectorMap<Key, Value>::at(const Key& k) {
    auto it = std::find(std::begin(keys_), std::end(keys_), k);
    if (it == std::end(keys_)) {
        throw std::out_of_range("This key does not exist");
    }
    auto dist = std::distance(keys_.begin(), it);
    return values_[dist];
}


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

// template <typename Value>
// class VectorMap<bool, Value> {
//     std::pair<bool, Value> true_pair;
//     std::pair<bool, Value> false_pair;

// public:
//     void insert(const bool& choice, const Value& v) {
//         if (choice) {
//             true_pair.second = v;
//         } else {
//             false_pair.second = v;
//         }
//     }

//     Value& operator[](const bool& choice);
//     Value& at(const bool& choice);
// };

// template <typename Value>
// Value& VectorMap<bool, Value>::operator[](const bool& choice) {
//     if (choice) {
//         return true_pair.second;
//     } else {
//         return false_pair.second;
//     }
// }

// template <typename Value>
// Value& VectorMap<bool, Value>::at(const bool& choice) {
//     return (*this)[choice];
// }

struct K {
    K(int) {}
};

// primary template
template <typename T1, typename T2, typename T3>
class A {
};

// // partial specialization with T1 = int
// template <typename T2, typename T3>
// class A<int, T2, T3> {
// };

// // partial specialization with T1 = int and T2 = double
// template <typename T3>
// class A<int, double, T3> {
// };

// // partial specialization with T1 = int and T3 = char
// template <typename T2>
// class A<int, T2, char> {};

// // full specialization with T1 = T2 = double and T3 = int
// template <>
// class A<double, double, int> {};

template<class T> void f(T)     { std::cout << "f1\n"; };    // #1: overload for all types
template<class T> void f(T*)    { std::cout << "f3\n"; };   // #3: overload for all pointer types
template<>        void f(int*)  { std::cout << "f2\n"; }; // #2: specialization of #1 for pointers to int

template<typename T>
constexpr bool is_int_key_v = T::is_int_key;

template <typename Key, typename Value>
constexpr bool is_int_key_v1 = VectorMap<Key,Value>::is_int_key;

int main() {
    f(new int{1});
    A<int, char, double> a;
    A<int, char, double> b;

    std::cout << std::boolalpha << std::is_same_v<decltype(a), decltype(b)> << '\n';

    VectorMap<int, char> map;
    // VectorMap<int, char>::iterator<K> k;
    map.insert(1, 'c');
    std::cout << map[1] << '\n';
    map[1] = 'e';                 // replaces value under 1
    std::cout << map[1] << '\n';  // prints 'e'
    // map.at(2);              // throw std::out_of_range
    std::cout << std::boolalpha << map.isIntKey() << '\n';
    std::cout << std::boolalpha << map.is_int_key << '\n';

    VectorMap<char, char> map3;
    std::cout << std::boolalpha << map3.isIntKey() << '\n';

    VectorMap<bool, int> map4;
    map4.insert(true, 3);
    map4.insert(false, 0);
    std::cout << map4[true] << '\n';
    map4[true] = 10;                 // replaces value under 1
    std::cout << map4[true] << '\n';  // prints 'e'
    std::cout << std::boolalpha << is_int_key_v<decltype(map4)> << '\n';
    std::cout << std::boolalpha << is_int_key_v<decltype(map)> << '\n';
    // std::cout << std::boolalpha << is_int_key_v<K> << '\n';
    std::cout << std::boolalpha << is_int_key_v1<VectorMap<int, char>, VectorMap<int, char>> << '\n';
    std::cout << std::boolalpha << is_int_key_v1<bool, int> << '\n';
    std::cout << std::boolalpha << is_int_key_v1<int, int> << '\n';

    std::vector<int> v{1, 2, 3};
    find(begin(v), end(v), 2);

    // VectorMap<int, K> map2;
    // map2.insert(1, 'c');
    // // std::cout << map2[1] << '\n';
    // map2[1] = 'e';           // replaces value under 1
    // // std::cout << map[1] << '\n';    // prints 'e'



    return 0;
}
