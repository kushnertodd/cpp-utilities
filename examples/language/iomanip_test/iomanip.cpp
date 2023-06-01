#include <iostream>
#include <iomanip>

void prhex(int* x) {
  std::cout << std::hex << std::setfill(' ') << std::setw(8) << x << std::endl;
}

int main() {
  int i;
  prhex(&i);
}
