#include <iostream>
class A {
public:
  int i = 1;
  A(int _i) : i(_i) {}
};

int main() {
  A a(2);
  A* pa = new A(3);
  std::cout << "A a(2) - a.i = " << a.i << std::endl;
  std::cout << "A* pa = new A(3) - pa->i = " << pa->i << std::endl;
}
