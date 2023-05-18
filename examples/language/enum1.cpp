#include <iostream>
#include <cstdio>
/*
enum class Traffic_light { red, yellow, green };
enum class Warning { green, yellow, orange, red }; // fire alert lev els
Warning a1 = 7; // error : no int->War ning conversion
int a2 = green; // error : green not in scope
int a3 = Warning::green; // error : no War ning->int conversion
Warning a4 = Warning::green; // OK
void f(Traffic_light x)
{
  if (x == 9) {  } // error : 9 is not a Traffic_light
  if (x == red) {  } // error : no red in scope
  if (x == Warning::red) {  } // error : x is not a War ning
  if (x == Traffic_light::red) {  } // OK
}
*/
//enum Warning : int { green, yellow, orange, red=7 }; // sizeof(War ning)==sizeof(int)
enum class Warning : char { green, yellow, orange, red=7 }; // sizeof(War ning)==1
//enum class Warning { green, yellow, orange, red=7 }; // sizeof(War ning)==1
int main() {
  //std::cout << "red " << std::string(Warning::red) << std::endl;
  printf("red %d\n", static_cast<int>(Warning::red));
  static_cast<int>(Warning::green)==0;
  static_cast<int>(Warning::yellow)==1;
  static_cast<int>(Warning::orange)==2;
  static_cast<int>(Warning::red)==5;
  printf("red %d\n", static_cast<int>(Warning::red));
  //std::cout << "red " << Warning::red << std::endl;
}
