#include <iostream>
using namespace std;
class A {
public:
  A() {
    cout << "A constructor" << endl;
  }
	A(const A& other) {
    cout << "A copy constructor" << endl;
  }
	A& operator=(const A& other) {
    cout << "A assignment" << endl;
    return *this;
  }
	A(A&& other) {
    cout << "A move constructor" << endl;
  }
	A& operator=(A&& other) {
    cout << "A move assignment" << endl;
    return *this;
  }
};

A getA() { A a; return a; }

/*
1
A constructor
2
A constructor
A move assignment
3
A copy constructor
4
A constructor
5
*/
int main() {
 cout << 1 << endl;
 A a;
 cout << 2 << endl;
 a = getA();
 cout << 3 << endl;
 A b(a);
 cout << 4 << endl;
 A c(getA());
 cout << 5 << endl;
}

