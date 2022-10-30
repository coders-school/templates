#include <algorithm>
#include <iostream>
#include <optional>
#include <vector>
#include <type_traits>

template <typename Key, typename Value>
class VectorMap {
    static_assert(std::is_default_constructible<Value>::value, "Value must have a default c-tor");
    std::vector<Key> keys {};
    std::vector<Value> values {};
public:
    void insert(const Key & k, const Value & v) {
        keys.emplace_back(k);
        values.emplace_back(v);
    }

    Value& operator[](const Key & k) {
        for (size_t i = 0; i < keys.size(); ++i) {
            if (keys[i] == k) {
                return values[i];
            }
        }
        keys.emplace_back(k);
        values.emplace_back(Value{});
        return values.back();
    }

    const Value& at(const Key & k) const {
        for (size_t i = 0; i < keys.size(); ++i) {
            if (keys[i] == k) {
                return values[i];
            }
        }
        throw std::out_of_range{"Not in map"};
    }

    bool isIntKey() const {
        return std::is_same<Key, int>::value;
    }

    static constexpr bool is_int_key = std::is_same<Key, int>::value;
};

template <typename Value>
class VectorMap<bool, Value> {
    static_assert(std::is_default_constructible<Value>::value, "Value must have a default c-tor");
    std::optional<Value> t_{};
    std::optional<Value> f_{};
public:
    void insert(bool k, const Value & v) {
        if (k) {
            t_ = v;
        } else {
            f_ = v;
        }
    }

    Value& operator[](bool k) {
        if (k) {
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

    const Value& at(bool k) const {
        if (k && t_) {
            return *t_;
        } else if (!k && f_) {
            return *f_;
        }
        throw std::out_of_range{"Not in map"};
    }

    bool isIntKey() const {
        return false;
    }

    static constexpr bool is_int_key = false;
};

template <typename K, typename V>
constexpr bool is_int_key_v = VectorMap<K, V>::is_int_key;

class X {
    X() = delete;
};

int main() {
    // VectorMap<char, X> mapX;
    std::cout << std::boolalpha << is_int_key_v<bool, char> << '\n';

    VectorMap<int, char> map;
    std::cout << std::boolalpha << map.isIntKey() << '\n';
    std::cout << std::boolalpha << map.is_int_key << '\n';
    std::cout << std::boolalpha << is_int_key_v<int, char> << '\n';
    VectorMap<char, char> mapC;
    std::cout << std::boolalpha << mapC.isIntKey() << '\n';
    std::cout << std::boolalpha << mapC.is_int_key << '\n';
    VectorMap<unsigned, char> mapU;
    std::cout << std::boolalpha << mapU.isIntKey() << '\n';
    std::cout << std::boolalpha << mapU.is_int_key << '\n';
    map.insert(1, 'c');
    map[1] = 'e';
    std::cout << map[1];
    std::cout << map[1];
    std::cout << map[2];
    std::cout << map[2];
    std::cout << map.at(1);              // throw std::out_of_range
    std::cout <<  '\n';

    std::cout << "sizeof VectorMap<int, char> " << sizeof(map) << '\n';

    VectorMap<bool, int> boolMap;
    std::cout << std::boolalpha << boolMap.isIntKey() << '\n';  // false
    std::cout << std::boolalpha << boolMap.is_int_key << '\n';  // false
    boolMap.insert(true, 42);
    std::cout << boolMap[true] << '\n';     // 42
    boolMap[true] = 43;
    std::cout << boolMap[true] << '\n';     // 43
    try {
        std::cout << boolMap.at(false); // throw std::out_of_range
    } catch(...) {
        // silently ignore
    }
    std::cout << boolMap[false] << '\n';    // 0
    std::cout << boolMap.at(false);

    std::cout << "sizeof VectorMap<bool, int> " << sizeof(boolMap) << " " << sizeof(int) << '\n';  // sizeof(2*Value)

    return 0;
}
