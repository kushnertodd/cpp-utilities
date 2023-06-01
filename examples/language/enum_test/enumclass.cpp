#include <iostream>

  enum ENUM {
    ENUM1,
    ENUM2,
    ENUM3
  };
  enum ENUM_CLASS {
    ENUM_CLASS1,
    ENUM_CLASS2,
    ENUM_CLASS3
  };

void p_enum( ENUM test ) {
    std::cout << "ENUM " << test << std::endl;
}

void p_enum_class( ENUM_CLASS test ) {
    std::cout << "ENUM_CLASS " << test << std::endl;
}

int main() {
  //for (ENUM test = ENUM1; test < ENUM3; ENUM(test+1))
  //for (ENUM test = ENUM1; test < ENUM3; test++)
  for (auto test : { ENUM1, ENUM2, ENUM3})
    //std::cout << "ENUM " << test << std::endl;
    p_enum(test);
  for (auto test : { ENUM_CLASS1, ENUM_CLASS2, ENUM_CLASS3})
    //std::cout << "ENUM_CLASS " << test << std::endl;
    p_enum_class(test);
}
