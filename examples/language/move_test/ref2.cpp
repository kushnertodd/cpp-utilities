#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <sstream>
#include <vector>

class A {
public:
  int i;
  A() {
    std::cout << "A default constructor" << std::endl;
  }
  A(int i_) : i(i_) {
    std::cout << "A contructor: " << i << std::endl;
  }
  ~A() {
    std::cout << "A destructor" << std::endl;
  }
};

std::ostream& operator<<(std::ostream &os, const A& a) {
  os << "A.i: " << a.i;
  return os;
}

bool operator==(const A& lhs, const A& rhs) {
  return lhs.i == rhs.i;
}

using Int_vec = std::vector<int>;
using Int_vec_iter = Int_vec::iterator;
using Int_list = std::list<int>;
using Int_list_iter = Int_list::iterator;
using Int_map = std::map<int, int>;
using Int_map_iter = Int_map::iterator;

using A_vec = std::vector<A>;
using A_vec_iter = A_vec::iterator;
using A_list = std::list<A>;
using A_list_iter = A_list::iterator;
using A_map = std::map<int, A>;
using A_map_iter = A_map::iterator;

std::string prhex_int_vec(std::string msg, Int_vec_iter&& int_iter) {
  std::ostringstream os;
  os << msg << std::hex << std::setfill(' ') << std::setw(8) << *int_iter;
  return os.str();
}
std::string prhex_int_list(std::string msg, Int_list_iter&& int_iter) {
  std::ostringstream os;
  os << msg << std::hex << std::setfill(' ') << std::setw(8) << *int_iter;
  return os.str();
}
std::string prhex_int_map(std::string msg, Int_map_iter&& int_iter) {
  std::ostringstream os;
  os << msg << std::hex << std::setfill(' ') << std::setw(8) << int_iter->first;
  return os.str();
}

std::string prhex_A_vec(std::string msg, A_vec_iter&& A_iter) {
  std::ostringstream os;
  os << msg << std::hex << std::setfill(' ') << std::setw(8) << *A_iter;
  return os.str();
}
std::string prhex_A_list(std::string msg, A_list_iter&& A_iter) {
  std::ostringstream os;
  os << msg << std::hex << std::setfill(' ') << std::setw(8) << *A_iter;
  return os.str();
}
std::string prhex_A_map(std::string msg, A_map_iter&& A_iter) {
  std::ostringstream os;
  os << msg << std::hex << std::setfill(' ') << std::setw(8) << A_iter->first;
  return os.str();
}

A_list_iter my_find(A_list &a_list, int i) {
  for (A_list_iter it = a_list.begin(); it != a_list.end(); it++) {
    std::cout << "my_find: checking " << i << " against " << *it << std::endl;
    if (it->i == i) return it;
  }
  return a_list.end();
}

A& my_find_a(A_list &a_list, int i) {
  for (A_list_iter it = a_list.begin(); it != a_list.end(); it++)
    if (it->i == i) return *it;
  return *a_list.end();
}

Int_map_iter my_find_map(Int_map &int_map, int i) {
  for (Int_map_iter it = int_map.begin(); it != int_map.end(); it++) {
    std::cout << "my_find_map: checking " << i << " against " << it->first << std::endl;
    if (it->first == i) return it;
  }
  return int_map.end();
}


int main() {
  std::cout << "Int_vec int_vec = { 1, 2, 3 };" << std::endl;
  Int_vec int_vec = { 1, 2, 3 };
  std::cout << "Int_list int_list = { 1, 2, 3 };" << std::endl;
  Int_list int_list = { 1, 2, 3 };
  std::cout << "Int_map int_map = { {1, 1}, {2, 2}, {3, 3 }};" << std::endl;
  Int_map int_map = { {1, 1}, {2, 2}, {3, 3 }};
  std::cout << prhex_int_vec("vec  ", int_vec.begin()) << std::endl;
  std::cout << prhex_int_list("list ", int_list.begin()) << std::endl;
  std::cout << prhex_int_map("map  ", int_map.begin()) << std::endl;

  std::cout << "for (A i : { 1, 2, 3 }) A_vec.emplace_back(i);" << std::endl;
  A_vec A_vec;
  for (int i : {
         1, 2, 3
       }) A_vec.emplace_back(i);

  A_list A_list;
  std::cout << "for (int i : { 1, 2, 3 }) A_list.emplace_back(i);" << std::endl;
  for (int i : {
         1, 2, 3
       }) A_list.emplace_back(i);

  //std::cout << "A_list A_list = { 1, 2, 3 };" << std::endl;
  //A_list A_list = { 1, 2, 3 };

  A_map A_map;
  std::cout << "for (int i : { 1, 2, 3 }) A_map.emplace(std::to_string(i), i);" << std::endl;
  for (int i : {
         1, 2, 3
       }) A_map.emplace(std::to_string(i), i);

  //std::cout << "A_map A_map = { {\"1\", 1}, {\"2\", 2}, {\"3\", 3 }};" << std::endl;
  //A_map A_map = { {"1", 1}, {"2", 2}, {"3", 3 }};

  std::cout << prhex_A_vec("vec  ", A_vec.begin()) << std::endl;
  std::cout << prhex_A_list("list ", A_list.begin()) << std::endl;
  std::cout << prhex_A_map("map  ", A_map.begin()) << std::endl;

  std::cout << "Int_vec_iter it = std::find(int_vec.begin(), int_vec.end(), 3); " << std::endl;
  Int_vec_iter it_int = std::find(int_vec.begin(), int_vec.end(), 3);
  std::cout << "*it_int " << *it_int << std::endl;

  std::cout << "Int_vec_iter it = std::find(A_vec.begin(), A_vec.end(), 3); " << std::endl;
  A_vec_iter it_A = std::find(A_vec.begin(), A_vec.end(), 3);
  std::cout << "*it_A " << *it_A << std::endl;

  std::cout << "A_list_iter it_list_A = my_find(A_list, 3);" << std::endl;
  A_list_iter it_list_A = my_find(A_list, 3);
  if (it_list_A == A_list.end())
    std::cout << "nogots" << std::endl;
  else
    std::cout << "gots" << std::endl;
  std::cout << "*it_list_A " << *it_list_A << std::endl;
  std::cout << "A &a1 = *it_list_A;" << std::endl;
  A &a1 = *it_list_A;
  std::cout << "a1.i " << a1.i << std::endl;
  A_list_iter it_list_AA = my_find(A_list, 9);
  if (it_list_AA == A_list.end())
    std::cout << "nogots" << std::endl;
  else
    std::cout << "gots" << std::endl;

  Int_map_iter it_map_int = my_find_map(int_map, 9);
  if (it_map_int == int_map.end())
    std::cout << "nogots" << std::endl;
  else
    std::cout << "gots" << std::endl;
}
