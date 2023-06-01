#include <iostream>
#include "my_namespace.hpp"

namespace my_namespace {

int my_variable2 = 2;
void my_func2() {
  std::cout << "my_namespace::my_func2() my_namespace::my_variable2 " << my_namespace::my_variable2 << std::endl;
}
}

void my_class::my_func1(std::string message) {
  std::cout << "my_class::my_func1(): message '" 
<< message << "'" << std::endl;
}

int main() {
  my_namespace::my_func1();
  // this is too early
  //my_func2();
  using namespace my_namespace;
  my_func2();
  my_class::my_func1("my_func1 called by main"); my_class::my_func2();

}
