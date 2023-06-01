#include <iostream>
class A {
public:
  int i;
  A(int i_) : i(i_) {}
  ~A() { std::cout << "A: destroying " << i << std::endl; }
};

void swap(A& a, A& b) {
  std::cout << "swap(" << a.i << ", " << b.i << ")" << std::endl;
  const A tmp = a;
  a = b;
  b = tmp;
}

A x(A a) {
  std::cout << "x(A." << a.i << ")" << std::endl;
  return a;
}

A y(A& a) {
  std::cout << "y(A." << a.i << ")" << std::endl;
  return a;
}

A z(A&& a) {
  std::cout << "z(A." << a.i << ")" << std::endl;
  return a;
}

/*
swap(1, 2)
A: destroying 1
x(A.2)
A: destroying 2
A: destroying 2
y(A.1)
A: destroying 1
done.
A: destroying 3
A: destroying 1
A: destroying 2
*/
int main() {
  A a(1);
  A b(2);
  A c(3);
  swap(a, b);
  a = x(a);
  b = y(b);
  //c = z(b);
  std::cout << "done." << std::endl;
} 
