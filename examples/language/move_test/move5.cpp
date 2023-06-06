#include <iostream>
#include <sstream>
/*
  E constructor
  E(const std::string &a_, const std::string &b_) : a{a_}, b{b_}: E a = 'a' b = 'b' c = 2
  E copy constructor
  E(const E& e) : a{e.a}, b{e.b}, c{e.c}: E a = 'a' b = 'b' c = 2
  E copy and move constructor
  E(const std::string &a_, const std::string &b_) : a{a_}, b{b_}: E a = 'a' b = 'b' c = 3
  e3: E a = 'a' b = 'b' c = 3
  E return by value
  E(const E& e) : a{e.a}, b{e.b}, c{e.c}: E a = 'a' b = 'b' c = 3
  finis
  ~E(): E a = 'a' b = 'b' c = 3
  ~E(): E a = 'a' b = 'b' c = 3
  ~E(): E a = 'a' b = 'b' c = 2
  ~E(): E a = 'a' b = 'b' c = 2
*/
struct C {
  int i{};
  C(int i_ = 1) : i(i_) {}
};
struct E {
  std::string a, b;
  C *c;

  ~E() {
    print("~E(): ") ;
    delete c;
  }
  E() : a{"a"},  b{"b"}, c{new C(1)} {
    print("E() : a{\"a\"},  b{\"b\"}, c{new C(1)}: ");
  }
  E(const std::string &a_, const std::string &b_, C* c_) : a{a_}, b{b_}, c{c_} {
    print("E(const std::string &a_, const std::string &b_) : a{a_}, b{b_}: ");
  }
  E(const E& e) : a{e.a}, b{e.b}, c{new C(e.c->i)} {
    print("E(const E& e) : a{e.a}, b{e.b}, c{e.c}: ");
  }
  E& operator=(E& e) = default;
  E(E&& e) : a{std::move(e.a)}, b{std::move(e.b)} {
    print("E(E&& e) : a{std::move(e.a)}, b{std::move(e.b)}: ");
    c = e.c;
    e.c = nullptr;
  }
  E& operator=(E&& e) {
    a = std::move(e.a);
    b = std::move(e.b);
    c = std::move(e.c);
    e.c = nullptr;
    print("E& operator=(E&& e) { a = std::move(e.a); b = std::move(e.b): ");
    return *this;
  }
  void print(const std::string &message) {
    std::cout << message << "E a = '" << a << "' b = '" << b << "' c = " << c->i << std::endl;
  }
  E f() {
    return *this;
  }
};

int main() {
  std::cout << "E constructor" << std::endl;
  std::string a{"a"};
  std::string b{"b"};
  E e1(a, b, new C(2));
  std::cout << "E copy constructor" << std::endl;
  E e2(e1);
  std::cout << "E copy and move constructor" << std::endl;
  E e3(E(a, b, new C(3)));
  e3.print("e3: ");
  std::cout << "E return by value" << std::endl;
  E e4(e3.f());
  std::cout << "finis" << std::endl;
}
