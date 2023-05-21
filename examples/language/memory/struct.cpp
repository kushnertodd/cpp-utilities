#include <cstring>
#include <string>

/*
Str:
<--c[3]---> <---i1---->
61 62 00 00 78 56 34 12 
<--c[5]------> <-pad-->
63 64 65 66 00 00 00 00 
<----------l---------->
f1 de bc 9a 78 56 34 12
<--c4-----> <---pad--->
67 68 69 6a 00 00 00 00 
<---------d----------->
2e ff 21 fd 4e df d6 40
<---------c8---------->
6b 6c 6d 6e 6f 70 71 00 
<--i2-----> <---c12----
f1 de bc 9a 6b 6c 6d 6e 
---c12---------------->
6f 70 71 72 73 74 75 00 
<--i3-----> <---pad----
49 23 dc fe 00 00 00 00 
1. 8 byte field causes 8 byte alignment before
2. struct always 8 byte aligned
*/
class Str {
public:
  char c3[3];
  int i1;
  char c5[5];
  long l;
  char c4[4];
  double d;
  char c8[8];
  int i2;
  char c12[12];
  int i3;

  Str() {}
  void init() {
    strcpy(c3, "ab");
    i1 = 0x12345678;
    strcpy(c5, "cdef");
    l = 0x123456789ABCDEF1;
    strncpy(c4, "ghij", 4);
    d = 23421.2342;
    strcpy(c8, "klmnopq");
    i2 = 0x9abcdef1;
    strcpy(c12, "klmnopqrstu");
    i3 = 0xfedc2349;
  }
};

void dump_struct(std::string msg, unsigned char* buf, size_t n) {
  printf("%s\n", msg.c_str());
  for (size_t i = 0; i < n; i++) {
    printf("%02x ", buf[i]);
    if (i % 8 == 7) printf("\n");
  }
  printf("\n");
}

int main() {
  Str s;
  std::memset(&s, '\0', sizeof(s));
  s.init();
  char buf[40];
  sprintf(buf, "Str size = %ld:", sizeof(s));
  dump_struct(buf, (unsigned char*) &s, sizeof(s));
}
