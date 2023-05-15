
#include <iostream>
#include <cstring>

/*
output:

sizeof(n) 4
initial:
buf
    a  b  c  d  e  f  g  h
    61 62 63 64 65 66 67 68
n   -1
    ff ff ff ff

smaller:
buf
    s  h  o  r  t
    73 68 6f 72 74 00 00 00
n   -1
    ff ff ff ff

smame size:
buf
    s  a  m  e  s  i  z  e
    73 61 6d 65 73 69 7a 65
n   -1
    ff ff ff ff

longer string:
buf
    l  o  n  g  e  r     s
    6c 6f 6e 67 65 72 20 73
n   -1
    ff ff ff ff

*/
class Test {
public:
  static const int str_len{8};
  char buf[str_len] {};
  int n{0};

  Test() {
    init();
  }
  void init() {
    std::memset(buf, '\0', str_len);
    std::memcpy(buf, "abcdefgh", str_len);
    n = 0xffffffff;
  }
  void print(const char *message) {
    printf("%s:\n", message);
    printf("buf\n    ");
    for (int i = 0; i < str_len; i++)
      printf("%c  ", buf[i]);
    printf("\n    ");
    for (int i = 0; i < str_len; i++)
      printf("%02x ", buf[i]);
    printf("\nn   %d\n    ", n);
    unsigned char* p = (unsigned char*) &n;
    for (int i = 0; i < (int)sizeof(n); i++)
      printf("%02x ", p[i]);
    printf("\n\ndump *this:\n");
    p = (unsigned char*) this;
    for (int i = 0; i < (int)sizeof(n); i++)
      printf("%02x ", p[i]);
  }
  void set(const char* str) {
    std::strncpy(buf, str, str_len);
  }
};
int main()
{
  Test test;
  printf("sizeof(n) %ld\n", sizeof(int));
  test.print("initial");
  test.set("short");
  test.print("smaller");
  test.set("samesize");
  test.print("smame size");
  test.set("longer string");
  test.print("longer string");
  printf("\n\ndump test:\n");
    unsigned char *p = (unsigned char*) &test;
    for (int i = 0; i < 12; i++)
      printf("%02x ", p[i]);
    printf("\n\n");
}
