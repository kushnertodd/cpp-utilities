#include <iostream>
#include <sstream>
using namespace std;

class A {
public:
  int i;
  A() {
    i = 1;
  };
  A(int m_i) : i(m_i) {}
  A(const A &m_a) : i(m_a.i) {}
  A(A* m_a) : i(m_a->i) {}
  string to_string() {
    ostringstream os;
    os << "A.i " << i;
    return os.str();
  }
};

class B {
public:
  A a;
  B() {};
  B(A m_a) : a(m_a.i) {}
  B(A* m_a) : a(*m_a) {}
  string to_string() {
    ostringstream os;
    os << "B.a '" << a.to_string() << "'";
    return os.str();
  }
};

int main() {
  A a0();
  A a1(1);
  A a2(2);
  A a3(a2);
  A a4(&a2);
  A a5(new A(5));
  B b6(a1);
  B b7(&a2);
  B b8(new A(8));

  //cout << "a0 " << a0.to_string() << endl;
  cout << "a1 " << a1.to_string() << endl;
  cout << "a2 " << a2.to_string() << endl;
  cout << "a3 " << a3.to_string() << endl;
  cout << "a4 " << a4.to_string() << endl;
  cout << "a5 " << a5.to_string() << endl;
  cout << "b6 " << b6.to_string() << endl;
  cout << "b7 " << b7.to_string() << endl;
  cout << "b8 " << b8.to_string() << endl;
}
/*
a1 A.i 1
a2 A.i 2
a3 A.i 2
a4 A.i 2
a5 A.i 5
b6 B.a 'A.i 1'
b7 B.a 'A.i 2'
b8 B.a 'A.i 8'
*/
