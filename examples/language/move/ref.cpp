#include <iostream>
class A {
public:
  int i;
  int& f() {
    return i;
  }
};
int main() {
  A a;
  a.i = 1;
  int& b = a.f();
  b =3;
  std::cout << "A.i " << a.i << " b " << b << std::endl;
}

