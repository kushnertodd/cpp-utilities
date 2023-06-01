#include <iostream>
#include <map>
class A {
public:
  int i;
  A() : i(0) {}
  A(int i_) : i(i_) {}
  friend std::ostream &operator<<( std::ostream &output, const A &a ) {
    output << a.i;
    return output;
  }
};

int main() {
  std::map<std::string, A> myMap
  = {{"Ground", 1},
    {"Floor", 2},
    {"Table", 3}
  };

  for (const auto& [key, value]: myMap) {
    std::cout << key << " has value " << value << std::endl;
  }
}
