#include <iostream>
struct cstring {
  const char* ptr = 0;
  const char* begin() const {
    return ptr?ptr:"";  // return empty string if we are null
  }
  null_sentinal_t end() const {
    return {};
  }
};

int main(int argc, char **argv) {
  cstring str{"abc"};
  for (char c : str) {
    std::cout << c;
  }
  std::cout << "\n";

}

