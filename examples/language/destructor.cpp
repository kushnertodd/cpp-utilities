#include <iostream>
#include <vector>

using namespace std;

class A {
public:
  int i = 3;
  A() {
    cout << "A: construct" << endl;
  }
  ~A() {
    cout << "A: destruct" << endl;
  }
};

class B {
public:
  A* pa;
  B(A* m_pa) : pa(m_pa) {
    cout << "B: construct" << endl;
  }
  ~B() {
    cout << "B: destruct before" << endl;
    delete pa;
    cout << "b: destruct after" << endl;
  }
};

class C {
public:
  B* b1;
  C(B* m_pb) : b1(m_pb) {
    cout << "C: construct" << endl;
  }
  ~C() {
    cout << "C: destruct before" << endl;
    delete b1;
    cout << "C: destruct after" << endl;
  }
};

int main() {
  A* pa = new A();
  B* pb = new B(pa);
  C c(pb);
}
