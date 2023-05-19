#include <iostream>

class EnumClass {
public:
  enum class Enum {
    f1 = 1,
    f2 = 2,
    f4 = 4
  };
  Enum e;
  EnumClass() : e(Enum::f1) {}
  static Enum from_int(int i) {
    return static_cast<Enum>(i);
  }
  int to_int() {
    return to_int(e);
  }
  static int to_int(EnumClass::Enum e) {
    return static_cast<int>(e);
  }
  std::string to_string() { return to_string(e); }
  static std::string to_string(EnumClass::Enum e) {
    switch (e) {
    case Enum::f1:
      return "f1";
    case Enum::f2:
      return "f2";
    case Enum::f4:
      return "f4";
    default:
      return "invalid enum";
    }
  }
};

int main() {
  EnumClass ec;
  std::cout << "ec: " << ec.to_string() << std::endl;
  for (auto e : {
         EnumClass::Enum::f1, EnumClass::Enum::f2, EnumClass::Enum::f4
       })
    std::cout << EnumClass::to_string(e) << ":" << EnumClass::to_int(e) << std::endl;
  for (auto i : {
         1, 2, 3, 4
       })  {
    EnumClass::Enum e = EnumClass::from_int(i);
    std::cout << EnumClass::to_string(e) << ":" << EnumClass::to_int(e) << std::endl;
  }
}
