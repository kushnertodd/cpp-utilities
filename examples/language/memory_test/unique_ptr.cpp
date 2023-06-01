#include <memory>
#include <iostream>
class B {
public:
  int a;
  B() {
    std::cout << "B()" << std::endl;
    a = 1;
  }
};
class A {
public:
  B* ptr;
  ~A() {
    std::cout << "~A(): deleting ptr" << std::endl;
    delete ptr;
  }
  A() {
    std::cout << "A()" << std::endl;
    ptr = new B();
  }
};
int main() {
  std::unique_ptr<A> a(new A);
  std::cout << "a is " << (a == nullptr ? "" : " not ") << " a nullptr" << std::endl;
  std::unique_ptr<A> b(nullptr);
  std::cout << "b is " << (a == nullptr ? "" : " not ") << " a nullptr" << std::endl;
  std::cout << "main()" << std::endl;
}
