#include <iostream>
#include <map>
class A {
public:
  int i = 0;
  A() = default;
  A(int i_) : i(i_) {}
};
int main() {
  std::map<int, A> a_map;
  A a(1);
  A aa;
  aa = A(2);
  a_map[1] = a;
  a_map[2] = aa;
  a_map[3] = A(3);
  std::cout << "a_map[1] " << a_map[1].i << std::endl;
  std::cout << "a_map[2] " << a_map[2].i << std::endl;
  std::cout << "a_map[3] " << a_map[3].i << std::endl;
  a_map[3].i = 4;
  std::cout << "a_map[3] " << a_map[3].i << std::endl;
  std::map<int, std::map<int, int>> b;
  b[1][1] = 2;
  std::cout << "b[1][1] " << b[1][1]  << std::endl;
}
