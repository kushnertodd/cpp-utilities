// swapping ostringstream objects
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream

int main () {
  //-----------------------------------
  std::stringstream ss1;

  std::cout << "good" << std::endl;
  ss1 << 100 << ' ' << 200;

  int var1=-1,var2=-1;
  std::cout << "ss1 >> var1 >> var2; " << (ss1 >> var1 >> var2 ? "gots" : "nogots") << std::endl;

  std::cout << "var1: " << var1 << std::endl;
  std::cout << "var2: " << var2 << std::endl;

  //-----------------------------------
  std::stringstream ss2;

  std::cout << "bad" << std::endl;
  ss2 << 300 << " uhoh";

  int var3=-1,var4=-1;
  std::cout << "ss2 >> var3 >> var4; " << (ss2 >> var3 >> var4 ? "gots" : "nogots") << std::endl;
  std::cout << "var3: " << var3 << std::endl;
  std::cout << "var4: " << var4 << std::endl;

  //-----------------------------------
  std::stringstream ss3;

  std::cout << "var3: " << var3 << std::endl;
  std::cout << "var4: " << var4 << std::endl;

  int var5=-1,var6=-1;
  ss3 << 400 << " uhoh";

  std::cout << "ss3 >> var5; " << (ss3 >> var5 ? "gots" : "nogots") << std::endl;
  std::cout << "var5: " << var5 << std::endl;
  std::cout << "ss3 >> var6; " << (ss3 >> var6 ? "gots" : "nogots") << std::endl;
  std::cout << "var6: " << var6 << std::endl;

  return 0;
}
