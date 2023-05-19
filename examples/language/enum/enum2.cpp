#include <iostream>
#include <map>

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

class Enums {
public:
  std::map<int, EnumClass::Enum> m;
  EnumClass::Enum &operator[](int i) {
    return m[i];
  }
};

/*
    ec: f1
    f1:1
    f2:2
    f4:4
    f1:1
    f2:2
    invalid enum:3
    f4:4
    enums[1]: f1:1
*/
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
  Enums enums;
  enums[1] = EnumClass::Enum::f1;
  std::cout << "enums[1]: " << EnumClass::to_string(enums[1]) << ":" << EnumClass::to_int(enums[1]) << std::endl;
}
