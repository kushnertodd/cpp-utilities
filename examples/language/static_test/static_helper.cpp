#include <iostream>

using namespace std;

class Statics {
public:
  static int not_inited;
  static int* not_inited_ptr;
  static void init() {
    not_inited = 1;
    not_inited_ptr = new int[1];
  }
};

// does not work without these
int Statics::not_inited = 0;
int* Statics::not_inited_ptr = nullptr;

int main() {
  cout << "not_inited before init() " << Statics::not_inited << endl;
  cout << "not_inited_ptr before init() " << Statics::not_inited_ptr << endl;
  Statics::init();
  cout << "not_inited after init() " << Statics::not_inited << endl;
  cout << "not_inited_ptr after init() " << Statics::not_inited_ptr << endl;
}
