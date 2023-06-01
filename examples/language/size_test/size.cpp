#include <ctime>
#include <iostream>

enum class A {
B
};

int main() {
std::cout << "sizeof(double) " << sizeof(double) << std::endl;
std::cout << "sizeof(int) " << sizeof(int) << std::endl;
std::cout << "sizeof(long) " << sizeof(long) << std::endl;
std::cout << "sizeof(time_t) " << sizeof(time_t) << std::endl;
std::cout << "sizeof(enum) " << sizeof(A::B) << std::endl;
}
