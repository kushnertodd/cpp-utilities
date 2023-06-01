#include <bitset>
#include <iostream>

int main()
{
  std::bitset<5> y;
  std::bitset<5> x(0x1e);

  std::cout << "x before: " << x << std::endl;
  std::cout << "y before: " << y << std::endl;
  x[1] = 1;
  x[2] = 0;
  y[1] = 1;
  y[4] = 1;
  // Note x[0-4]  valid

  std::cout << "x after: " << x << std::endl;
  std::cout << "y after: " << y << std::endl;
}

