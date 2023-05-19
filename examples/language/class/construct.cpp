#include <iostream>
using namespace std;

class A {
public:
  int a;
  A() {a = 1;};
  A(int m_a) : a(m_a) {}
};

class B: public A {
public:
  int b;
  int c;
  B() {b = 2;};
  B(int m_b) : A(3), b(m_b) {}
  B(int m_b, int m_c) : A(3), b(m_b), c(m_c) {}
};

int main() {
 A* a1 = new A();
 cout << "A* a1->a " << a1->a << endl;
 A* a2 = new A(4);
 cout << "A* a2->a " << a2->a << endl;
}
