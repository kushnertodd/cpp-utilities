#include <cstring>
#include <iostream>
#include <sstream>
class A {
public:
  static const int b_len = 8;
  long a;
  char b[b_len];
  double c;
  A() {}
  A(long a_, char* b_, double c_): a(a_), c(c_) {
    std::memcpy(b, b_, b_len);
  }
  std::string to_string() {
    std::ostringstream os;
    os << "a: " << a << " ";
    os << "b: " << b << " ";
    os << "c: " << c << " ";
    return os.str();
  }
};

void hexdmp(std::string message, unsigned char *buf, int buflen) {
  printf("%s: ", message.c_str());
  for (int i = 0; i < buflen; i++) {
    printf("%02x ", buf[i]);
  }
  printf("\n");
}

int main() {
  A a_obj;
  long a = 1;
  char b[A::b_len];
  double c = 2.1;
  std::strcpy(b, "hi!");
  char*p = (char*) &a_obj;
  std::memcpy(p, &a, sizeof(long));
  p+= sizeof(long);
  std::strcpy(p, b);
  p+= A::b_len;
  std::memcpy(p, &c, sizeof(double));
  std::cout << "sizeof(long) = " << sizeof(long) << std::endl;
  std::cout << "sizeof(b) = " << sizeof(b) << std::endl;
  std::cout << "sizeof(double) = " << sizeof(double) << std::endl;
  std::cout << a_obj.to_string() << std::endl;
  std::cout << "A is " << sizeof(A) << " and sizeof(double) is " << sizeof(double) << " bytes" << std::endl;
  hexdmp("a", (unsigned char*)&a, sizeof(long));
  hexdmp("b", (unsigned char*)&b, A::b_len);
  hexdmp("c", (unsigned char*)&c, sizeof(double));
  hexdmp("A",(unsigned char*)&a_obj, sizeof(A));
}
