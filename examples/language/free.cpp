#include <cstdlib>
using namespace std;
class A {
public:
  int b;
  A(int m_b) : b(m_b) {}
};
int main() {
  A a(1);
  A* pa = &a;
  free(pa);
}
