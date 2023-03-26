#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
using namespace std;
 
string intToString(int i, int width = -1) {
  ostringstream os;
//cout << "intToString: i " << i << " width " << width;
  if (width ==  -1) {
    // cout << " os << i";
    os << i;
  } else {
    //cout << "os << setw(width) << i" << endl << "os << setw(width) << \" a\"" << endl;
    os << setw(width) << i;
    os << setw(width) << " a";
  }
  //os << endl;
  return os.str();
}

int main() {
  cout << "string(intToString(1)): '" << string(intToString(1)) << "'" << endl;
  cout << "string(intToString(1, 4)): '" << string(intToString(1, 2)) << "'" << endl;
}
