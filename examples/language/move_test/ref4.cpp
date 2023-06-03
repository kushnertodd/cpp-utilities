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
  A(std::string s_):s(s_) {
    std::cout << "A(std::string "   << s << ") " << this << " " << s << std::endl;
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
A& A_rvalue_ref(A&& a) {
  std::cout << "A_rvalue_ref(" << a << ") " << std::endl;
  return a;
}

int main() {
  A a;
  A a1("1");
  A a2{"2"};
  A a3{A_rvalue(a)};
  A a4{A_lvalue(a)};
  A a5{A_rvalue_ref(A_rvalue(a))};
  std::cout << "A a3 = A_rvalue(    "<<a<<"); -> " << &a3 << std::endl;
  std::cout << "A a4 = A_rvalue(    "<<a<<"); -> " << &a4 << std::endl;
  std::cout << "A a5 = A_rvalue_ref("<<a<<"); -> " << &a5 << std::endl;
}
