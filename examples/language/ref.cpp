#include <iostream>
/*
ref.cpp: In function ‘int main()’:
ref.cpp:6:11: error: binding reference of type ‘int&’ to ‘const int’ discards qualifiers
   16 |   int& l{k};
      |           ^
ref.cpp:10:5: error: assignment of read-only reference ‘k’
   20 |   k = 3;
      |   ~~^~~
make: *** [<builtin>: ref] Error 1
*/
void lvalue_ref(int& i) {
  std::cout << "void lvalue_ref(int& " << i << ")" << std::endl;
}

void rvalue_ref(int&& i) {
  std::cout << "void rvalue_ref(int&& " << i << ")" << std::endl;
}

int main() {
  int i{1};
  int& j{i};
  const int& k{j};
  //int& l{k};
  std::cout << "i " << i << " j " << j << " k " << k << std::endl;
  j = 2;
  std::cout << "i " << i << " j " << j << " k " << k << std::endl;
  //k = 3;
  //l = 4;
  std::cout << "i " << i << " j " << j << " k " << k << std::endl;

  // lvalue_ref(1);
  rvalue_ref(2);
  int x{3};
  lvalue_ref(x);
  //int y{4};
  //rvalue_ref(y);
}
