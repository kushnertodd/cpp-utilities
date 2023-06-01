#include <cstring>
#include <string>
#include "serializable.hpp"

class Str : public Serializable {
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
    unsigned char* p = (unsigned char*) (unsigned char*)buf;
    p = (unsigned char*) Serializable::serialize_char_string(c3, p);
    p = (unsigned char*) Serializable::serialize_int(i1, p);
    p = (unsigned char*) Serializable::serialize_char_string(c5, p);
    p = (unsigned char*) Serializable::serialize_long(l, p);
    p = (unsigned char*) Serializable::serialize_chars(c4, 4, p);
    p = (unsigned char*) Serializable::serialize_double(d, p);
    p = (unsigned char*) Serializable::serialize_char_string(c8, p);
    p = (unsigned char*) Serializable::serialize_int(i2, p);
    p = (unsigned char*) Serializable::serialize_char_string(c12, p);
    p = (unsigned char*) Serializable::serialize_int(i3, p);
    return p;
  }
  void* deserialize(void* buf) {
    unsigned char* p = (unsigned char*) (unsigned char*)buf;
    p = (unsigned char*) Serializable::deserialize_char_string(c3, p);
    p = (unsigned char*) Serializable::deserialize_int(i1, p);
    p = (unsigned char*) Serializable::deserialize_char_string(c5, p);
    p = (unsigned char*) Serializable::deserialize_long(l, p);

    p = (unsigned char*) Serializable::deserialize_chars(c4, 4, p);

    p = (unsigned char*) Serializable::deserialize_double(d, p);
    p = (unsigned char*) Serializable::deserialize_char_string(c8, p);
    p = (unsigned char*) Serializable::deserialize_int(i2, p);
    p = (unsigned char*) Serializable::deserialize_char_string(c12, p);
    p = (unsigned char*) Serializable::deserialize_int(i3, p);
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
