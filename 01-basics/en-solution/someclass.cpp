#include <iostream>

template <typename T, typename U>
class SomeClass {
public:
    T getValue() { return value; }
private:
    T value = {};
    U* ptr = nullptr;
};

int main() {
    SomeClass<int, void> sc;
    std::cout << sc.getValue() << std::endl;
    return 0;
}
