#include <iostream>
#include <map>
class A {
public:
  int i = 0;
  A() = default;
  A(int i_) : i(i_) {}
};
  using Map1 = std::map<int, A>; 
  using Map2 = std::map<int, Map1>;
int main() {
  Map2 map2;
  A a1(1);
  A a2(2);
  map2[1][1] = a1;
  map2[2][2] = a2;

  std::cout << "map2[1][1].i = " << map2[1][1].i << std::endl;
  std::cout << "map2[2][2].i = " << map2[2][2].i << std::endl;

  map2[1][1].i = 3;
  map2[2][2].i = 4;

  std::cout << "map2[1][1].i = " << map2[1][1].i << std::endl;
  std::cout << "map2[2][2].i = " << map2[2][2].i << std::endl;
}
