#include <iostream>
#include <sstream>
/*
    A()  0x7ffc632525c8 0
    A(int 1) 0x7ffc632525c4 1
    A(int 2) 0x7ffc632525c0 2
    A_rvalue(    A.i: 0x7ffc632525c8 0)     
    A(const A& 0x7ffc632525c8 0) 0x7ffc632525bc 0
    A_lvalue(    A.i: 0x7ffc632525c8 0)     
    A(const A& 0x7ffc632525c8 0) 0x7ffc632525b8 0
    A_rvalue(    A.i: 0x7ffc632525c8 0)     
    A(const A& 0x7ffc632525c8 0) 0x7ffc632525cc 0
    A_rvalue_ref(A.i: 0x7ffc632525cc 0) 
    A(const A& 0x7ffc632525cc 0) 0x7ffc632525b4 0
    ~A() 0x7ffc632525cc 0
    A a3 = A_rvalue(    A.i: 0x7ffc632525c8 0); -> 0x7ffc632525bc
    A a4 = A_rvalue(    A.i: 0x7ffc632525c8 0); -> 0x7ffc632525b8
    A a5 = A_rvalue_ref(A.i: 0x7ffc632525c8 0); -> 0x7ffc632525b4
    ~A() 0x7ffc632525b4 0
    ~A() 0x7ffc632525b8 0
    ~A() 0x7ffc632525bc 0
    ~A() 0x7ffc632525c0 2
    ~A() 0x7ffc632525c4 1
    ~A() 0x7ffc632525c8 0
*/
class A {
public:
  int i{}; // else uninitialized
  ~A() {
    std::cout << "~A() " << this << " " << i << std::endl;
  }
  A() {
    std::cout << "A()  " << this << " " << i << std::endl;
  }
A(const A& a) : i(a.i) {
    std::cout << "A(const A& "   << &a << " " << a.i<< ") " << this << " " << i << std::endl;
}
A(A&& a) : i(a.i) {
    std::cout << "A(const A&& "   << &a << " " << a.i<< ") " << this << " " << i << std::endl;
}
  A(int i_):i(i_) {
    std::cout << "A(int "   << i << ") " << this << " " << i << std::endl;
  }
};
std::ostream& operator<<(std::ostream &os, const A& a) {
  os << "A.i: " << &a << " " << a.i;
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
  A a1(1);
  A a2{2};
  A a3 = A_rvalue(a);
  A a4 = A_lvalue(a);
  A a5 = A_rvalue_ref(A_rvalue(a));
  std::cout << "A a3 = A_rvalue(    "<<a<<"); -> " << &a3 << std::endl;
  std::cout << "A a4 = A_rvalue(    "<<a<<"); -> " << &a4 << std::endl;
  std::cout << "A a5 = A_rvalue_ref("<<a<<"); -> " << &a5 << std::endl;
}
