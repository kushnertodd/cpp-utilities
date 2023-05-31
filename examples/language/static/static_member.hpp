#include <iostream>
#include <map>

class A {
public:
  enum class C { D, E };
  static int b;
  static void a_b();
  static const std::map<A::C, std::string> to_exts;
};
