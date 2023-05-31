#include <vector>
#include <iostream>


class A {
public:
  int i{};
  A(int i_) : i(i_) {}
  void pr(const char* msg) {
    std::cout << msg << ": A(" << i << ")" << std::endl;
  }
};

std::vector<A> v;
void prv(const char* msg, std::vector<A>& av) {
  std::cout << msg << ": ";
  for (const A& a : av)
    std::cout << a.i << " ";
  std::cout << std::endl;
}

int main() {
  A a1(1);
  A a2(2);
  v.push_back(a1);
  v.push_back(a2);
  a1.pr("a1 step 1");
  a2.pr("a2 step 1");
  prv("v step 1", v);
  v[0].i = 3;
  v[1].i = 4;
  v[0].pr("v[0] step 2");
  v[1].pr("v[1] step 2");
  prv("v step 2", v);
  A& a3 = v[0];
  A& a4 = v[1];
  a3.i = 5;
  a4.i = 6;
  a3.pr("a3 step 3");
  a4.pr("a4 step 3");
  prv("v step 3", v);
  A& a5 = a3;
  A& a6 = a4;
  a5.i = 7;
  a6.i = 8;
  a5.pr("a5 step 4");
  a6.pr("a6 step 4");
  prv("v step 4", v);
}
