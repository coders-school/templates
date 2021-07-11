#include <string>

template <typename T>
void copy(T arg) {}

template <typename T>
void reference(T& arg) {}

template <typename T>
void universal_reference(T&& arg) {}


int main() {
    int number = 4;
    copy(number);       // int
    copy(5);            // int

    reference(number);  // int&
    // reference(5);    // candidate function [with T = int] not viable: expects an l-value for 1st argument

    universal_reference(number);            // int&
    universal_reference(std::move(number)); // int&&
    universal_reference(5);                 // int&&
}