#include <iostream>
#include <vector>

using namespace std;

int main() {
  int argc = 8;
  const char* argv[] = { "test_linear_image_create", "test", "5", "1", "90", "10", "285", "20" };
  for (int i = 0; i < argc; i++)
    cout << "argv[" << i << "] = '" << argv[i] << "'" << endl;
}
