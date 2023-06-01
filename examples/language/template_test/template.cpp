#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdio>

using namespace std;

template<typename T>
class A {
public:
  string s;
  T a;
  T *b;
  A(string m_s, T m_a, T* m_b) : s(m_s), a(m_a), b(m_b) {}
  string toString() {
    ostringstream os;
    os << setw(20) << left << "A: " + s << " sizeof(T) " << sizeof(T) << " a " << a + 0;
    return os.str();
  }
};

typedef unsigned char pixel_8U;
typedef int pixel_32S;
typedef float pixel_32F;

int main(int argc, char** argv) {
  if (argc < 2) {
    cout << "usage: " << argv[0] << " n " << endl;
  } else {
    cout << "sizeof(pixel_8U) " << sizeof(pixel_8U) << endl;
    int n;
    n = atoi(argv[1]);
    cout << "n " << n << endl;
    A<unsigned char> a_unsigned_char("unsigned char", n, new unsigned char[3]);
    cout <<  a_unsigned_char.toString() << endl;

    A<char> a_char("char", n, new char[3]);
    cout <<  a_char.toString() << endl;

    A<pixel_8U> a_8U("a_8U", 2, new pixel_8U[3]);
    cout <<  a_8U.toString() << endl;
    pixel_8U* p8U = a_8U.b;
    printf("pixel_8U &a_8U[0] %p\n", (void *)p8U);
    p8U++; 
    printf("pixel_8U &a_8U[1] %p\n", (void *)p8U);

    A<int> a_int("int", 3, new int[3]);
    cout <<  a_int.toString() << endl;

    A<pixel_32S> a_pixel_32S("a_32S", 4, new pixel_32S[3]);
    cout <<  a_pixel_32S.toString() << endl;
    pixel_32S* p32S = a_pixel_32S.b;
    printf("pixel_32S &a_32S[0] %p\n", (void *)p32S);
    p32S++; 
    printf("pixel_32S &a_32S[1] %p\n", (void *)p32S);

    A<float> a_float("float", 5, new float[3]);
    cout << a_float.toString() << endl;

    A<pixel_32F> a_pixel_32F("a_32F", 6, new pixel_32F[3]);
    cout << a_pixel_32F.toString() << endl;
    pixel_32F* p32F = a_pixel_32F.b;
    printf("pixel_32F &a_32F[0] %p\n", (void *)p32F);
    p32F++; 
    printf("pixel_32F &a_32F[1] %p\n", (void *)p32F);

    A<byte> a_byte("a_byte", 6, new byte[3]);
    cout << a_byte.toString() << endl;
    byte* pbyte = a_byte.b;
    printf("byte &a_byte[0] %p\n", (void *)pbyte);
    pbyte++; 
    printf("byte &a_byte[1] %p\n", (void *)pbyte);

    A<unsigned byte> a_byte("a_byte", 6, new byte[3]);
    cout << a_byte.toString() << endl;
    byte* pbyte = a_byte.b;
    printf("byte &a_byte[0] %p\n", (void *)pbyte);
    pbyte++; 
    printf("byte &a_byte[1] %p\n", (void *)pbyte);
  }
}
