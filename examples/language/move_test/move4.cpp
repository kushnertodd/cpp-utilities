#include <iostream>
#include <sstream>
struct E {
  std::string a, b;

  ~E() {
    print("~E(): ") ;
  }
  E() : a{"a"},  b{"b"} {
    print("E() : a{\"a\"},  b{\"b\"}: ");
  }
  E(const std::string &a_, const std::string &b_) : a{a_}, b{b_} {
    print("E(const std::string &a_, const std::string &b_) : a{a_}, b{b_}: ");
  }
  E(const E& e) : a{e.a}, b{e.b} {
    print("E(const E& e) : a{e.a}, b{e.b}: ");
  }
//E(const E&& e) = delete;
  E(const E&& e) : a{std::move(e.a)}, b{std::move(e.b)} {
    print("E(const E&& e) : a{std::move(e.a)}, b{std::move(e.b)}: ");
  }
  E& operator=(E& e) = default;
  E(E&& mE) : a{std::move(mE.a)}, b{std::move(mE.b)} {
    print("E(E&& mE) : a{std::move(mE.a)}, b{std::move(mE.b)}: ");
  }
  E& operator=(E&& mE) {
    a = std::move(mE.a);
    b = std::move(mE.b);
    print("E& operator=(E&& mE) { a = std::move(mE.a); b = std::move(mE.b): ");
    return *this;
  }
  void print(const std::string &message) {
    std::cout << message << "E a = '" << a << "' b = '" << b << "'" << std::endl;
  }
  E f() {
    return *this;
  }
};

int main() {
  std::cout << "E constructor" << std::endl;
  std::string a{"a"};
  std::string b{"b"};
  E e1(a, b);
  std::cout << "E copy constructor" << std::endl;
  E e2(e1);
  std::cout << "E copy and move constructor" << std::endl;
  E e3(E(a, b));
  e3.print("e3: ");
  std::cout << "E return by value" << std::endl;
  E e4(e3.f());
  std::cout << "finis" << std::endl;
}
