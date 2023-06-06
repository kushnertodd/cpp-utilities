#include <iostream>
#include <sstream>
/*
  E constructor
  E(int i) : c{i}: E c.i = 2
  E copy constructor
  E(const E& e) : c{e.c.i}: E c.i = 2
  E copy and move constructor
  E(int i) : c{i}: E c.i = 3
  e3: E c.i = 3
  E return by value
  E(const E& e) : c{e.c.i}: E c.i = 3
  finis
  ~E(): E c.i = 3
  ~E(): E c.i = 3
  ~E(): E c.i = 2
  ~E(): E c.i = 2
*/
struct C {
  int i{};
  C() : i{0} {
    std::cout << "C()" << std::endl;
}
  C(int i_) : i(i_) {
    std::cout << "C(int i_) : i{i_}: " << std::endl;
}
  C(const C& c) : i{c.i} {
    std::cout << "C(C&& c) : i{c.i}: " << std::endl;
}
  C(C&& c) : i{c.i} {
    std::cout << "C(C&& c) : i{c.i}: " << std::endl;
  }
  C& operator=(C& c) {
    std::cout << "C& operator=(C& c)" << std::endl;
    i = c.i;
    return *this;
  }
  C& operator=(C&& c) {
    std::cout << "C&& operator=(C& c)" << std::endl;
    i = c.i;
    return *this;
  }
};
struct E {
  C c;

  ~E() {
    print("~E(): ") ;
  }
  E() : c{1} {
    print("E() : c{1}: ");
  }
  E(int i) : c{i} {
    print("E(int i) : c{i}: ");
  }
  E(const E& e) : c{e.c.i} {
    print("E(const E& e) : c{e.c.i}: ");
  }
  E& operator=(E& e) = default;
  E(E&& e) : c{std::move(e.c)} {
    print("E(E&& e) : c{std::move(e.c)}: ");
  }
  E& operator=(E&& e) {
    c = std::move(e.c);
    print("E& operator=(E&& e) { c = std::move(e.c); } ");
    return *this;
  }
  void print(const std::string &message) {
    std::cout << message << "E c.i = " << c.i << std::endl;
  }
  E f() {
    return *this;
  }
};

int main() {
  std::cout << "E constructor" << std::endl;
  E e1(2);
  std::cout << "E copy constructor" << std::endl;
  E e2(e1);
  std::cout << "E copy and move constructor" << std::endl;
  E e3(E(3));
  e3.print("e3: ");
  std::cout << "E return by value" << std::endl;
  E e4(e3.f());
  std::cout << "finis" << std::endl;
}
