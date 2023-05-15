#include <cstring>
#include <iostream>

/*
    A() c3: 'ghi'
     67 68 69 00
    A() c4: 'jkl'
     6a 6b 6c 00 00
    A() i2:     4    5    6
     0004 0005 0006
    A() i5:    13   14   15    0
     000d 000e 000f 0000

    main c1: 'abc'
     61 62 63 00
    main c3: 'ghi'
     67 68 69 00
    main c4: 'jkl'
     6a 6b 6c 00 00
    main i1:     1    2    3
     0001 0002 0003
    main i2:     4    5    6
     0004 0005 0006
    main i5:    13   14   15    0
     000d 000e 000f 0000
    */
class A {
public:
  // ok in main -- error: flexible array member ‘A::c1’ not at end of ‘class A’
  // char c1[] = "abc";

  // error: initializer-string for ‘char [3]’ is too long [-fpermissive]
  // char c2[3] = "def";
  unsigned char c3[4] = "ghi";
  unsigned char c4[5] = "jkl";
  // ok in main -- error: initializer for flexible array member ‘int A::i1 []’
  // int i1[] = { 1, 2, 3 };
  int i2[3] = { 4, 5, 6 };
  // error: cannot convert ‘<brace-enclosed initializer list>’ to ‘int*’ in initialization
  // int *i3 = { 7, 8, 9 };

  // error: too many initializers for 'int [2]'
  // int i4[2] = { 10, 11, 12 };
  int i5[4] = { 13, 14, 15 };

  // int[] invalid
  // void print_arr(const char* msg, int n, int[] arr) {
  static void print_arr(const char* msg, int n, int* arr) {
    printf("%s: ", msg);
    for (int i = 0; i < n; i++)
      printf(" %4d", arr[i]);
    printf("\n");
    for (int i = 0; i < n; i++)
      printf(" %04x", arr[i]);
    printf("\n");
  }
  static void print_str(const char* msg, int n, unsigned char* str) {
    printf("%s: '%s'\n", msg, str);
    for (int i = 0; i < n; i++)
      printf(" %02x", str[i]);
    printf("\n");
  }

  A() {
    print_str("A() c3", sizeof(c3), c3);
    print_str("A() c4", sizeof(c4), c4);
    print_arr("A() i2", sizeof(i2)/sizeof(int), i2);
    print_arr("A() i5", sizeof(i5)/sizeof(int), i5);
  }
};

class B {
public:
  unsigned char c[4] = "mno";

  // error: array used as initializer
  // B(const B& b) : c(b.c) { }
  B(const B& b) {
    std::strcpy((char*) c, (const char*) b.c);
  }
  // error: array used as initializer
  // B(B&& b) : c(std::move(b.c)) { }
  B(B&& b) {
    std::strcpy((char*) c, (const char*) b.c);
  }
  // error: incompatible types in assignment of ‘unsigned char*’ to ‘unsigned char [4]’
  // B(unsigned char* c_) : c(c_) { }
  B(unsigned char* c_) {
    std::strcpy((char*) c, (const char*) c_);
  }
  B &operator=(const B &b) {
    // error: invalid conversion from ‘const unsigned char*’ to ‘const char*’ [-fpermissive]
    // std::strcpy(c, b.c);
    std::strcpy((char*) c, (const char*) b.c);
    return *this;
  }
  B &operator=(const B &&b) {
    // error: invalid array assignment
    //c = std::move(b.c);

    // error: invalid array assignment
    // c = b.c;

    // error (c): invalid conversion from ‘unsigned char*’ to ‘char*’ [-fpermissive]
    // std::strcpy(c, b.c);

    // error (b.c): invalid conversion from ‘const unsigned char*’ to ‘const char*’ [-fpermissive]
    // std::strcpy((char*) c, b.c);
    std::strcpy((char*) c, (const char*) b.c);
    return *this;
  }
};
class C {
public:
  int i[4] = { 1, 2, 3, 4 };
  // error: initializer for flexible array member ‘int C::j []’
  // int j[] = { 1, 2, 3, 4 };

  // error: array used as initializer
  // C(const C& b) : i(b.i) { }
  C(const C& b) {
    std::memcpy(i, b.i, 4);
  }
  // error: array used as initializer
  // C(C&& b) : i(std::move(b.i)) { }
  C(C&& b) {
    std::memcpy(i, b.i, 4);
  }
  // error: incompatible types in assignment of ‘int*’ to ‘int [4]’
  // C(int i_[4]) : i(i_) { }
  // error: incompatible types in assignment of ‘int*’ to ‘int [4]’
  // C(int* i_) : i(i_) { }
  C(int* i_) {
    std::memcpy(i, i_, 4);
  }
  // C(unsigned char* c_) { std::memcpy((char*) c, (const char*) c_, 4); }
  C &operator=(const C &b) {
    std::memcpy(i, b.i, 4);
    return *this;
  }
  C &operator=(const C &&b) {
    // error: invalid array assignment
    // i = std::move(b.i);
    // error: invalid array assignment
    // i = b.i;
    std::memcpy(i, b.i, 4);
    return *this;
  }
};
int main() {
  A a1;
  printf("\n");
  unsigned char c1[] = "abc";
  // error: initializer-string for ‘char [3]’ is too long [-fpermissive]
  // char c2[3] = "def";
  unsigned char c3[4] = "ghi";
  unsigned char c4[5] = "jkl";
  int i1[] = { 1, 2, 3 };
  int i2[3] = { 4, 5, 6 };
  // error: scalar object ‘i3’ requires one element in initializer
  // int *i3 = { 7, 8, 9 };
  // error: too many initializers for ‘int [2]’
  // int i4[2] = { 10, 11, 12 };
  int i5[4] = { 13, 14, 15 };

  A::print_str("main c1", sizeof(c1), c1);
  A::print_str("main c3", sizeof(c3), c3);
  A::print_str("main c4", sizeof(c4), c4);
  A::print_arr("main i1", sizeof(i1)/sizeof(int), i1);
  A::print_arr("main i2", sizeof(i2)/sizeof(int), i2);
  A::print_arr("main i5", sizeof(i5)/sizeof(int), i5);
}
