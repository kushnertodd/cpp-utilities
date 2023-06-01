// shuts off assert
//#define NDEBUG
#include <cassert>

/*
  running with no args should give:

  $ ./assert
  assert: assert.cpp:4: int main(int, char**): Assertion `argc > 1' failed.
  Aborted
*/
int main(int argc, char **argv) {
  assert(argc > 1);
}
