#include <cstring>
#include <iostream>
int main() {
  char c[3];
  std::memcpy(c, "abc", 3);
  std::string s(c, 3);
  std::cout << "s '" << s << "' from c '" << std::string(c) << "'" << std::endl;
  std::string s1 = std::string(c, 3);
  std::cout << "s1 '" << s1 << "' from c '" << std::string(c) << "'" << std::endl;
}
