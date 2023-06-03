#include <iostream>
#include <sstream>
/*
*/
class A {
public:
  std::string s{}; // else uninitialized
  ~A() {
    std::cout << "~A() " << this << " " << s << std::endl;
  }
  A() {
    std::cout << "A()  " << this << " " << s << std::endl;
  }
  A(const A& a) : s(a.s) {
    std::cout << "A(const A& "   << &a << " " << a.s<< ") " << this << " " << s << std::endl;
}
  A(A&& a) : s(std::move(a.s)) {
    std::cout << "A(A&& "   << &a << " " << a.s<< ") " << this << " " << s << std::endl;
  }
};
std::ostream& operator<<(std::ostream &os, const A& a) {
  os << "A.s: " << &a << " " << a.s;
  return os;
}
A A_rvalue(A& a) {
  std::cout << "A_rvalue(    " << a << ")     " << std::endl;
  return a;
}
A& A_lvalue(A& a) {
  std::cout << "A_lvalue(    " << a << ")     " << std::endl;
  return a;
}
A A_rvalue_ref(A&& a) {
  std::cout << "A_rvalue_ref(" << a << ") " << std::endl;
  return A_rvalue(a);
}

int main() {
  A a;
  A a3{A_rvalue(a)};
  std::cout << "A a3 = A_rvalue(    "<<a<<"); -> " << &a3 << std::endl;
}
