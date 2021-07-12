#include <type_traits>
#include <iostream>

struct Point1D {
    int x;
};
struct Point2D {
    int x, y;
};
struct Point3D {
    int x, y, z;
};
int getY(const Point1D & p) {
    std::cout << "Point1D\n";
    return 0;
}
template <typename T>
int getY(const T & p)
{
    std::cout << "Template\n";
    return p.y;
}

int main() {
    Point1D a { 1 };
    Point2D b { 1, 2 };
    Point3D c { 1, 2, 3 };

    getY(a);
    getY(b);
    getY(c);
    return 0;
}