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
  vector<A*> vap;
  B(vector<A*> m_vap) : vap(m_vap) {
    cout << "B: construct" << endl;
  }
  ~B() {
    cout << "B: destruct before" << endl;
    delete vap[0];
    cout << "b: destruct after" << endl;
  }
};

class C {
public:
  vector<A*> vap;
  C(vector<A*> m_vap) : vap(m_vap) {
    cout << "C: construct" << endl;
  }
  ~C() {
    cout << "C: destruct before" << endl;
    delete vap[0];
    cout << "C: destruct after" << endl;
  }
};

int main() {
  A* pa = new A();
  vector<A*> vap;
  vap.push_back(pa);
  B* pb = new B(vap);
  C* pc = new C(vap);
  delete pc;
  delete pb;
}
