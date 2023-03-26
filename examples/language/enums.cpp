#include <iostream>

enum NO_NS1 {
  NO_NS_TEST
};

enum NO_NS2 {
  NO_NS_TEST
};

namespace enum_test {
enum NS_ENUM {
  NS_ENUM_TEST
};
}

int main() {

  NO_NS1 no_ns1 = NO_NS_TEST;
  NO_NS2 no_ns2 = NO_NS_TEST;
  NS_ENUM ns_enum1 = NS_ENUM_TEST;
  enum_test::NS_ENUM ns_enum2 = NS_ENUM_TEST;
  NS_ENUM ns_enum3 = enum_test::NS_ENUM_TEST;
  enum_test::NS_ENUM ns_enum4 = enum_test::NS_ENUM_TEST;
}

/*
expected errors: 

=============================================================
enums.cpp:8:3: error: ‘NO_NS_TEST’ conflicts with a previous declaration
    8 |   NO_NS_TEST
      |   ^~~~~~~~~~
enums.cpp:4:3: note: previous declaration ‘NO_NS1 NO_NS_TEST’
    4 |   NO_NS_TEST
      |   ^~~~~~~~~~
=============================================================
enums.cpp: In function ‘int main()’:
enums.cpp:20:19: error: cannot convert ‘NO_NS1’ to ‘NO_NS2’ in initialization
   20 |   NO_NS2 no_ns2 = NO_NS_TEST;
      |                   ^~~~~~~~~~
      |                   |
      |                   NO_NS1
=============================================================
enums.cpp:21:3: error: ‘NS_ENUM’ was not declared in this scope; did you mean ‘enum_test::NS_ENUM’?
   21 |   NS_ENUM ns_enum1 = NS_ENUM_TEST;
      |   ^~~~~~~
      |   enum_test::NS_ENUM
enums.cpp:12:6: note: ‘enum_test::NS_ENUM’ declared here
   12 | enum NS_ENUM {
      |      ^~~~~~~
=============================================================
enums.cpp:22:33: error: ‘NS_ENUM_TEST’ was not declared in this scope; did you mean ‘enum_test::NS_ENUM_TEST’?
   22 |   enum_test::NS_ENUM ns_enum2 = NS_ENUM_TEST;
      |                                 ^~~~~~~~~~~~
      |                                 enum_test::NS_ENUM_TEST
enums.cpp:13:3: note: ‘enum_test::NS_ENUM_TEST’ declared here
   13 |   NS_ENUM_TEST
      |   ^~~~~~~~~~~~
=============================================================
enums.cpp:23:10: error: expected ‘;’ before ‘ns_enum3’
   23 |   NS_ENUM ns_enum3 = enum_test::NS_ENUM_TEST;
      |          ^~~~~~~~~
      |          ;
=============================================================
enums.cpp:19:10: warning: unused variable ‘no_ns1’ [-Wunused-variable]
   19 |   NO_NS1 no_ns1 = NO_NS_TEST;
      |          ^~~~~~
enums.cpp:20:10: warning: unused variable ‘no_ns2’ [-Wunused-variable]
   20 |   NO_NS2 no_ns2 = NO_NS_TEST;
      |          ^~~~~~
enums.cpp:22:22: warning: unused variable ‘ns_enum2’ [-Wunused-variable]
   22 |   enum_test::NS_ENUM ns_enum2 = NS_ENUM_TEST;
      |                      ^~~~~~~~
enums.cpp:24:22: warning: unused variable ‘ns_enum4’ [-Wunused-variable]
   24 |   enum_test::NS_ENUM ns_enum4 = enum_test::NS_ENUM_TEST;
      |                      ^~~~~~~~
make: *** [<builtin>: enums] Error 1

*/
