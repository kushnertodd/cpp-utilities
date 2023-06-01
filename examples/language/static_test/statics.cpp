#include <iostream>
#include "statics.hpp"

using namespace std;

  void Statics::init() {
    not_inited = 1;
    not_inited_ptr = new int[1];
  }

  void Globals::init() {
    not_inited = 1;
    not_inited_ptr = new int[1];
  }

void statics_helper();

// does not work without these
//int Statics::not_inited = 0;
int Statics::not_inited;
//int* Statics::not_inited_ptr = nullptr;
int* Statics::not_inited_ptr;
Globals globals;

int main() {
  cout << "main: Statics::not_inited before init() " << Statics::not_inited << endl;
  cout << "main: Statics::not_inited_ptr before init() " << Statics::not_inited_ptr << endl;
  Statics::init();
  cout << "main: Statics::not_inited after init() " << Statics::not_inited << endl;
  cout << "main: Statics::not_inited_ptr after init() " << Statics::not_inited_ptr << endl;

  cout << "main: globals.not_inited before init() " << globals.not_inited << endl;
  cout << "main: globals.not_inited_ptr before init() " << globals.not_inited_ptr << endl;
  globals.init();
  cout << "main: globals.not_inited after init() " << globals.not_inited << endl;
  cout << "main: globals.not_inited_ptr after init() " << globals.not_inited_ptr << endl;

  statics_helper();
}
