#include <fstream>
using namespace std;

int main() {
  ofstream fo1;
  fo1.open("fstream1.txt");
  fo1 << "fstream.txt" << endl;
  fo1.close();

  ofstream fo2;
  fo2.open("fstream2.txt");
  fo2 << "fstream.txt" << endl;
  fo2.close();

  ofstream fo3;
  fo3.open("fstream2.txt");
  fo3.close();
}
