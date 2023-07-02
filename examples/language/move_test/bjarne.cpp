#include <iostream>
#include <vector>

void f(const std::string &str) {
  std::cout << str << std::endl;
}

class A {
public:
  int i{1};
  std::string s{"A"};
  std::string t;

  std::string to_string() {
    return ": i=" + std::to_string(i) + " s='" + s + "' t='" + t + "'";
  }
  ~A() {
    f("  ~A()" + to_string());
  }
  A() {
    f("  A()" + to_string());
  }
  A(const A &a) : i{a.i}, s{a.s}, t{a.t} {
    f("  A(const A &a)" + to_string());
  }
  A(A &&a) : i{a.i}, s{std::move(a.s)}, t{std::move(a.t)} {
    f("  A(A &&a)" + to_string());
  }
  A& operator=(const A &a) {
    i = a.i;
    s = a.s;
    t = a.t;
    return *this;
  }
  A& operator=(A &&a) {
    i = a.i;
    s = a.s;
    t = a.t;
    return *this;
  }
  A(int i_) : i{i_} {
    f("  A(int i_)" + to_string());
  }
};

int main() {
  if (true) {
    f("--initialization--");
    f("A a1;");
    A a1;
    f("A a2(2);");
    A a2(2);
    f("A a3(a2);");
    A a3(a2);
    f("A a4(std::move(a3));");
    A a4(std::move(a3));
  }
  if (true) {
    if (true) {
      f("--vector--");
      f("std::vector<A> v1{1,2};");
      std::vector<A> v1{1,2};
      /*
      std::vector<A> v1{1,2};
        A(int i_): i=1 s='A' t=''
        A(int i_): i=2 s='A' t=''
        A(const A &a): i=1 s='A' t=''
        A(const A &a): i=2 s='A' t=''
        ~A(): i=2 s='A' t=''
        ~A(): i=1 s='A' t=''
        ~A(): i=1 s='A' t=''
        ~A(): i=2 s='A' t=''
       */
    }
    if (true) {
      f("std::vector<A> v2 = {1,2};");
      std::vector<A> v2 = {1,2};
      /*
      std::vector<A> v2 = {1,2};
        A(int i_): i=1 s='A' t=''
        A(int i_): i=2 s='A' t=''
        A(const A &a): i=1 s='A' t=''
        A(const A &a): i=2 s='A' t=''
        ~A(): i=2 s='A' t=''
        ~A(): i=1 s='A' t=''
        ~A(): i=1 s='A' t=''
        ~A(): i=2 s='A' t=''
       */
    }
    std::vector<A> v11;
    if (true) {
      f("std::vector<A> v3(v11);");
      std::vector<A> v3(v11);
      /*
      std::vector<A> v23{v11};
       */
    }
    if (true) {
      f("std::vector<A> v23{v11};");
      std::vector<A> v23{v11};
      /*
      std::vector<A> v23{v11};
       */
    }
    if (true) {
      f("std::vector<A> v12(std::move(v11));");
      std::vector<A> v12(std::move(v11));
      /*
      std::vector<A> v12(std::move(v11));
       */
    }
    if (true) {
      f("std::vector<A> v9{1,2};");
      std::vector<A> v9{1,2};
      f("std::vector<A> v4;");
      std::vector<A> v4;
      f("for (const A& a: v9) v4.push_back (a);");
      for (const A& a: v9) v4.push_back (a);
      f("for (const A& a: v9) v4.push_back (std::move(a));");
      for (const A& a: v9) v4.push_back (std::move(a));
      f("for (const A& a: v9) v4.emplace_back (a);");
      for (const A& a: v9) v4.emplace_back (a);
      f("for (const A& a: v9) v4.emplace_back (std::move(a));");
      for (const A& a: v9) v4.emplace_back (std::move(a));
      /*
      std::vector<A> v9{1,2};
        A(int i_): i=1 s='A' t=''
        A(int i_): i=2 s='A' t=''
        A(const A &a): i=1 s='A' t=''
        A(const A &a): i=2 s='A' t=''
        ~A(): i=2 s='A' t=''
        ~A(): i=1 s='A' t=''
      std::vector<A> v4;
      for (const A& a: v9) v4.push_back (a);
        A(const A &a): i=1 s='A' t=''
        A(const A &a): i=2 s='A' t=''
        A(const A &a): i=1 s='A' t=''
        ~A(): i=1 s='A' t=''
      for (const A& a: v9) v4.push_back (std::move(a));
        A(const A &a): i=1 s='A' t=''
        A(const A &a): i=1 s='A' t=''
        A(const A &a): i=2 s='A' t=''
        ~A(): i=1 s='A' t=''
        ~A(): i=2 s='A' t=''
        A(const A &a): i=2 s='A' t=''
      for (const A& a: v9) v4.emplace_back (a);
        A(const A &a): i=1 s='A' t=''
        A(const A &a): i=1 s='A' t=''
        A(const A &a): i=2 s='A' t=''
        A(const A &a): i=1 s='A' t=''
        A(const A &a): i=2 s='A' t=''
        ~A(): i=1 s='A' t=''
        ~A(): i=2 s='A' t=''
        ~A(): i=1 s='A' t=''
        ~A(): i=2 s='A' t=''
        A(const A &a): i=2 s='A' t=''
      for (const A& a: v9) v4.emplace_back (std::move(a));
        A(const A &a): i=1 s='A' t=''
        A(const A &a): i=2 s='A' t=''
        ~A(): i=1 s='A' t=''
        ~A(): i=2 s='A' t=''
        ~A(): i=1 s='A' t=''
        ~A(): i=2 s='A' t=''
        ~A(): i=1 s='A' t=''
        ~A(): i=2 s='A' t=''
        ~A(): i=1 s='A' t=''
        ~A(): i=2 s='A' t=''
        ~A(): i=1 s='A' t=''
        ~A(): i=2 s='A' t=''
       */
    }
    if (true) {
      std::vector<A> v5;
      f("for (j : {5, 6}) v5.emplace_back (j);");
      for (int j : {
             5, 6
           }) v5.emplace_back (j);
      /*
      for (j : {5, 6}) v5.emplace_back (j);
        A(int i_): i=5 s='A' t=''
        A(int i_): i=6 s='A' t=''
        A(const A &a): i=5 s='A' t=''
        ~A(): i=5 s='A' t=''
        ~A(): i=5 s='A' t=''
        ~A(): i=6 s='A' t=''
       */
    }
    if (true) {
      std::vector<A> v14;
      f("for (j : {7, 8}) v14.push_back (A(j));");
      for (int j : {
             7, 8
           }) v14.push_back (A(j));
      /*
      for (j : {7, 8}) v14.push_back (A(j));
        A(int i_): i=7 s='A' t=''
        A(A &&a): i=7 s='A' t=''
        ~A(): i=7 s='' t=''
        A(int i_): i=8 s='A' t=''
        A(A &&a): i=8 s='A' t=''
        A(const A &a): i=7 s='A' t=''
        ~A(): i=7 s='A' t=''
        ~A(): i=8 s='' t=''
        ~A(): i=7 s='A' t=''
        ~A(): i=8 s='A' t=''
       */
    }
  }
}
