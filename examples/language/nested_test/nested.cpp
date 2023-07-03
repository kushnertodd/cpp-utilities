#include <iostream>
/*
 * Out::In::f(): o.x = 3
 * Out::f(): i.y = 4
*/
class Out {
public:
  int x;
  class In;
  void f(In &i) {
    std::cout << "Out::f(): i.y = " << i.y << std::endl;
  }
  class In {
  public:
    int y;
    void f(Out &o) {
      std::cout << "Out::In::f(): o.x = " << o.x << std::endl;
    }
  };
};

int main() {
  Out o;
  o.x = 3;
  Out::In oi;
  oi.y = 4;
  oi.f(o);
  o.f(oi);
}
