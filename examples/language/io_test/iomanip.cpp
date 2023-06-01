#include <iostream>
#include <iomanip>
using namespace std;
int main ()
{
  double float_value =3.14159;
  cout << setw(10) << setprecision(4) << float_value << '\n';
  cout << setw(10) << setprecision(9) << float_value << '\n';
  cout << fixed;
  cout << setw(10) << setprecision(5) << float_value << '\n';
  cout << setw(10) << setprecision(10) << float_value << '\n';
  return 0;
}
