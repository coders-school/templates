template <typename T>
class Holder {
public:
    template <typename C>
    Holder(C const& container)
        : vect{container.begin(), container.end()} {}

    void printVect() {
        for (auto v : vect) {
            std::cout << v << " ";
        }
    }

private:
    std::vector<T> vect;
};