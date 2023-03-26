#include <iostream>
#include "my_namespace.hpp"

namespace my_namespace {

int my_variable1 = 1;

}

void my_namespace::my_func1() {
  //std::cout << "my_namespace::my_func1() my_namespace::my_variable1 " << my_namespace::my_variable1 << std::endl;
  std::cout << "my_namespace::my_func1() my_namespace::my_variable1 " << my_variable1 << std::endl;
}

void my_class::my_func2() {
  std::cout << "my_class::my_func2()" << std::endl;
  my_func1("my_func1 called by my_func2");
}
