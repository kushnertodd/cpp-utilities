#include <list>
class A {};
int main() {
  std::list<A> la;
  A a;
  la.push_back(a);
}
