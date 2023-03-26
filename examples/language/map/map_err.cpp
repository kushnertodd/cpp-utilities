#include <iostream>
#include <map>
using namespace std;
int main() {
  map<string, string> sm;
  string test = sm["test"];
  cout << "test '" << test << "'"  << endl;
}
