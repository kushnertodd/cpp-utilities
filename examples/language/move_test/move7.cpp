#include <iostream>
#include <sstream>
/*
    A:
    A constructor
    A(int i_) : i{i_}  i = 1
    A copy constructor
    A(A&& a)  : i{a.i} a.i = 1
    A move constructor
    A(int i_) : i{i_}  i = 3
    A return by value
    A() : i{0}
    A() : i{0}
    ~A() i = 0
    C:
    C constructor
    C(int i_) : i{i_}  i = 1
    C copy constructor
    C(C&& c)  : i{c.i} c.i = 1
    C move constructor
    C(int i_) : i{i_}  i = 3
    C return by value
    C() : i{0}
    C() : i{0}
    ~C() i = 0
    ~C() i = 0
    ~C() i = 3
    ~C() i = 1
    ~C() i = 1
    ~A() i = 0
    ~A() i = 3
    ~A() i = 1
    ~A() i = 1
*/
struct B {
  int i;
  B() : i{0} {}
  B(int i_) : i{i_} {}
};
struct A {
  int i{};
  B b;
  ~A()                   { std::cout << "~A() i = " << i           << std::endl; }
  A() : i{0}             { std::cout << "A() : i{0}"               << std::endl; }
  A(int i_)     : i{i_}  { std::cout << "A(int i_) : i{i_}  i = "   << i_ << std::endl; }
  A(const A& a) : i{a.i} { std::cout << "A(A&& a)  : i{a.i} a.i = " << a.i << std::endl; }
  A(A&& a)      : i{a.i} { std::cout << "A(A&& a)  : i{a.i} a.i = " << a.i << std::endl; }
  A& operator=(A& a) {
    std::cout << "A& operator=(A& a)" << std::endl;
    i = a.i;
    return *this;
  }
  A& operator=(A&& a) {
    std::cout << "A&& operator=(A& a)" << std::endl;
    i = a.i;
    return *this;
  }
  A f() { return A(); }
};

struct C {
  int i{};
  B b;
  ~C()                   { std::cout << "~C() i = " << i            << std::endl; }
  C()           : i{0}   { std::cout << "C() : i{0}"                << std::endl; }
  C(int i_)     : i{i_}  { std::cout << "C(int i_) : i{i_}  i = "    << i_ << std::endl; }
  C(const C& c) : i{c.i} { std::cout << "C(C&& c)  : i{c.i} c.i = " << c.i << std::endl; }
  C(C&& c) = default;
  C& operator=(C& c) {
    std::cout << "C& operator=(C& c)" << std::endl;
    i = c.i;
    return *this;
  }
  C& operator=(C&& c) = default;
  C f() { return C(); }
};
int main() {
  std::cout << "A:" << std::endl;
  std::cout << "A constructor" << std::endl;
  A a1(1);
  std::cout << "A copy constructor" << std::endl;
  A a2(a1);
  std::cout << "A move constructor" << std::endl;
  A a3(A(3));
  std::cout << "A return by value" << std::endl;
  A a4;
  a4.f();

  std::cout << "C:" << std::endl;
  std::cout << "C constructor" << std::endl;
  C c1(1);
  std::cout << "C copy constructor" << std::endl;
  C c2(c1);
  std::cout << "C move constructor" << std::endl;
  C c3(C(3));
  std::cout << "C return by value" << std::endl;
  C c4;
  c4.f();
}
