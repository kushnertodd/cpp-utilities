#include <iostream>
#include <list>
#include <vector>

class A {
public:
  int i;
  A() = default;
  A(int i) : i(i) {
    std::cout << "  -> constructor A("<<i<<") " << std::endl;
  }
  A(const A& other) : i(other.i) {
    std::cout << "  -> const copy constructor A(const A& other."<<other.i<<") " << std::endl;
  }
  A(A& other) : i(other.i) {
    std::cout << "  -> copy constructor A(A& other."<<other.i<<") " << std::endl;
  }
  A(A&& other) : i(std::move(other.i)) {
    std::cout << "  -> move constructor A(A&& other."<<other.i<<") " << std::endl;
  }
  A& operator=(const A& other) {
    std::cout << "  -> const assignment operator A& operator=(const A& other."<<other.i<<") " << std::endl;
    i = other.i;
    return *this;
  }
  A& operator=(A& other) {
    std::cout << "  -> assignment operator A& operator=(A& other."<<other.i<<") " << std::endl;
    i = other.i;
    return *this;
  }
  A& operator=(A&& other) {
    std::swap(i, other.i);
    std::cout << "  -> move assignment operator A& operator=(A&& other."<<other.i<<") " << std::endl;
    return *this;
  }
};

A rval_to_rval(A a) {
  std::cout << "  -> rval_to_rval(A a."<<a.i<<") " << std::endl;
  return a;
}
A ref_to_rval(A& a) {
  std::cout << "  -> ref_to_rval(A& a."<<a.i<<") " << std::endl;
  return a;
}
A rval_ref_to_rval(A&& a) {
  std::cout << "  -> rval_ref_to_rval(A&& a."<<a.i<<") " << std::endl;
  return a;
}
A&& rval_to_rval_ref(A a) {
  std::cout << "  -> rval_to_rval_ref(A&& a."<<a.i<<") " << std::endl;
  //return std::move(a); warning
  return std::move(rval_to_rval_ref(a));
}
A&& ref_to_rval_ref(A& a) {
  std::cout << "  -> ref_to_rval(A&& a."<<a.i<<") " << std::endl;
  //return a;
  return std::move(a);
}
A&& rval_ref_to_rval_ref(A&& a) {
  std::cout << "  -> rval_ref_to_rval(A&& a."<<a.i<<") " << std::endl;
  //return a;
  return std::move(a);
}
int main() {
  std::cout << "std::vector<A> va" << std::endl;
  std::vector<A> va;
  std::cout << "A a" << std::endl;
  A a(1);
  std::cout << "va.push_back(std::move(a))" << std::endl;
  va.push_back(std::move(a));
  std::cout << "va size: " << va.size() << std::endl;
  std::cout << "va.push_back(std::move(a))" << std::endl;
  va.push_back(std::move(a));
  std::cout << "va size: " << va.size() << std::endl;

  std::cout << "std::vector<A> la" << std::endl;
  std::list<A> la;
  std::cout << "A a" << std::endl;
  std::cout << "la.push_back(std::move(a))" << std::endl;
  la.push_back(std::move(a));
  std::cout << "la size: " << va.size() << std::endl;
  std::cout << "la.push_back(std::move(a))" << std::endl;
  la.push_back(std::move(a));
  std::cout << "la size: " << va.size() << std::endl;
}
