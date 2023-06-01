#include <cstring>
#include <string>

/*
str1 size = 72:
<----c3---> <---i1---->
61 62 00 00 78 56 34 12
<----c5------> <-pad-->
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

str1 serialized size = 60:
<-c3---> <---i1----> <-
61 62 00 78 56 34 12 63
--c5------> <----l-----
64 65 66 00 f1 de bc 9a
----------> <--c4----->
78 56 34 12 67 68 69 6a
<---d----------------->
2e ff 21 fd 4e df d6 40
<----c8--------------->
6b 6c 6d 6e 6f 70 71 00
<--i2-----> <--c12-----
f1 de bc 9a 6b 6c 6d 6e
<--------------------->
6f 70 71 72 73 74 75 00
<--i3----->
49 23 dc fe

str2 deserialized size = 72:
<----c3---> <---i1---->
61 62 00 10 78 56 34 12
<----c3---> <---i1---->
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
  static size_t size() {
    size_t len = 0;
    len += 3;
    len += sizeof(int);
    len += 5;
    len += sizeof(long);
    len += 4;
    len += sizeof(double);
    len += 8;
    len += sizeof(int);
    len += 12;
    len += sizeof(int);
    return len;
  }
  void *serialize(void* buf) {
    unsigned char* p = (unsigned char*)buf;
    std::memcpy(p, c3, 3);
    p += 3;
    std::memcpy(p, &i1, sizeof(int));
    p += sizeof(int);
    std::memcpy(p, c5, 5);
    p += 5;
    std::memcpy(p, &l, sizeof(long));
    p += sizeof(long);
    std::memcpy(p, c4, 4);
    p += 4;
    std::memcpy(p, &d, sizeof(double));
    p += sizeof(double);
    std::memcpy(p, c8, 8);
    p += 8;
    std::memcpy(p, &i2, sizeof(int));
    p += sizeof(int);
    std::memcpy(p, c12, 12);
    p += 12;
    std::memcpy(p, &i3, sizeof(int));
    p += sizeof(int);
    return p;
  }
  void* deserialize(void* buf) {
    unsigned char* p = (unsigned char*)buf;
    std::memcpy(c3, p, 3);
    p += 3;
    std::memcpy(&i1, p, sizeof(int));
    p += sizeof(int);
    std::memcpy(c5, p, 5);
    p += 5;
    std::memcpy(&l, p, sizeof(long));
    p += sizeof(long);
    std::memcpy(c4, p, 4);
    p += 4;
    std::memcpy(&d, p, sizeof(double));
    p += sizeof(double);
    std::memcpy(c8, p, 8);
    p += 8;
    std::memcpy(&i2, p, sizeof(int));
    p += sizeof(int);
    std::memcpy(c12, p, 12);
    p += 12;
    std::memcpy(&i3, p, sizeof(int));
    p += sizeof(int);
    std::memcpy(c12, p, 12);
    return p;
  }
};

void dump_mem(const char* msg, unsigned char* buf, size_t n) {
  printf("%s\n", msg);
  for (size_t i = 0; i < n; i++) {
    printf("%02x ", buf[i]);
    if (i % 8 == 7) printf("\n");
  }
  printf("\n");
}

int main() {
  Str str1;
  std::memset(&str1, '\0', sizeof(str1));
  str1.init();
  char buf[40];
  sprintf(buf, "str1 size = %ld:", sizeof(str1));
  dump_mem(buf, (unsigned char*) &str1, sizeof(str1));

  size_t mem_size  = Str::size();
  unsigned char* mem = (unsigned char*) malloc(mem_size);
  std::memset(mem, '\0', mem_size);
  str1.serialize(mem);
  sprintf(buf, "str1 serialized size = %ld:", mem_size);
  dump_mem(buf, mem, mem_size);
  printf("\n");

  Str str2;
  str2.deserialize(mem);
  sprintf(buf, "str2 deserialized size = %ld:", sizeof(str2));
  dump_mem(buf, (unsigned char*) &str2, sizeof(str2));
}
