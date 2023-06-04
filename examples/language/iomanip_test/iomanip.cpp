#include <iostream>
#include <iomanip>
using namespace std;

void prhex(int* x) {
  std::cout << std::hex << std::setfill(' ') << std::setw(8) << x << std::endl;
}

int main() {
  int i;
  prhex(&i);
  double float_value =3.14159;
  cout << setw(10) << setprecision(4) << float_value << '\n';
  cout << setw(10) << setprecision(9) << float_value << '\n';
  cout << fixed;
  cout << setw(10) << setprecision(5) << float_value << '\n';
  cout << setw(10) << setprecision(10) << float_value << '\n';
  return 0;
}
