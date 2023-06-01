#include <array>
#include <iostream>
#include <string>
#include <vector>

class A {
public:
  int i;
  A(): i(0) {}
  A(int _i) : i(_i) {}
  std::string to_string() {
    return std::to_string(i);
  }
};

A& get(std::vector<A>& vec, int i) {
  return vec[i];
}

int main() {
  std::array<A, 3> arr;
  std::vector<A> vec;
  for (int i = 0; i < 3; i++) {
    arr[i].i = i;
    vec.push_back(A());
  }
  for (int i = 0; i < 3; i++) {
    //vec[i].i = i;
    get(vec, i).i = i;
    std::cout << "arr[" << i << "].i = " << arr[i].i << std::endl;
    std::cout << "vec[" << i << "].i = " << vec[i].i << std::endl;
  }
}
