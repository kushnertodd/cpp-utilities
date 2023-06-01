#include <iostream>
class static_array {
public:
  static int arr[2];
  static int arrlen;
};
int static_array::arr[2] = {
  1,
  2
};
int static_array::arrlen = 2;

int main() {
  for (int i = 0; i < static_array::arrlen; i++ ) {
    std::cout << i << " " << static_array::arr[i] << std::endl;
  }
}
