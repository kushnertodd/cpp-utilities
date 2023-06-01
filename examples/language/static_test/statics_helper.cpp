#include <iostream>
#include "statics.hpp"

using namespace std;

extern Globals globals;

void statics_helper() {
  cout << "statics_helper: Statics::not_inited after init() " << Statics::not_inited << endl;
  cout << "statics_helper: Statics::not_inited_ptr after init() " << Statics::not_inited_ptr << endl;

  cout << "statics_helper: globals.not_inited after init() " << globals.not_inited << endl;
  cout << "statics_helper: globals.not_inited_ptr after init() " << globals.not_inited_ptr << endl;
}
