#include <iostream>
#include <vector>
#include <utility>
#include <type_traits>

class K {
public:
    K(int k) {}
};

template <typename Key, typename Value>
class VectorMap {
    static_assert(std::is_default_constructible<Value>::value);

    std::vector<Key> keys_;
    std::vector<Value> values_;
public:
    void insert(Key&& key, Value&& value) {
        keys_.emplace_back(std::forward<Key>(key));
        values_.emplace_back(std::forward<Value>(value));
    }

    Value& operator[](Key key) {
        auto it = std::find(keys_.begin(), keys_.end(), key);
        if (it == keys_.end()) {
            keys_.emplace_back(std::forward<Key>(key));
            values_.emplace_back();
            return values_.back();
        }
        auto dist = std::distance(keys_.begin(), it);
        return values_[dist];
    }
    Value& at(Key key) {
        auto it = std::find(keys_.begin(), keys_.end(), key);
        if (it == keys_.end()) {
            throw std::out_of_range("No such element");
        }
        auto dist = std::distance(keys_.begin(), it);
        return values_[dist];
    }
};

int main() {
    VectorMap<int, char> map;
    map.insert(1, 'c');
    map[1] = 'e';  // replaces value under 1
    std::cout << map[1];  // prints 'e'
    map[2] = 'd';  // replaces value under 1
    std::cout << map[2];  // prints 'e'
    map.at(3); // throw std::out_of_range
    // VectorMap<int, K> map2;

    return 0;
}