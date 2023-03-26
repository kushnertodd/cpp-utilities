// compile this with to shut off assert:
//g++ -DNDEBUG no_assert.cpp -o no_assert

#include <cassert>

/*
  running with no args should give no error
*/
int main(int argc, char **argv) {
  assert(argc > 1);
}
