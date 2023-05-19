#include <iostream>
#include <map>
class A {
public:
  std::map<int, std::string> m;
  std::string &operator[](int i) {
    return m[i];
  }
};
class B {
public:
  std::map<int, A> m;
  A &operator[](int i) {
    return m[i];
  }
};

int main() {
  A a;
  a[1] = "str 1";
  std::cout << "a[1] '" << a[1] << "'" << std::endl;
  B b;
  b[1][1] = "str 2";
  std::cout << "b[1][1] '" << b[1][1] << "'" << std::endl;
}
