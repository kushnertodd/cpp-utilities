#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <sstream>
#include <vector>

using Int_map = std::map<int, int>;
using Int_map_iter = Int_map::iterator;

std::string prhex_int_map(std::string msg, Int_map_iter&& int_iter) {
  std::ostringstream os;
  os << msg << std::hex << std::setfill(' ') << std::setw(8) << int_iter->first;
  return os.str();
}

Int_map_iter my_find_map(Int_map &int_map, int i) {
  for (Int_map_iter it = int_map.begin(); it != int_map.end(); it++) {
    std::cout << "my_find_map: checking " << i << " against " << it->first << std::endl;
    if (it->first == i) return it;
  }
  return int_map.end();
}


int main() {
  std::cout << "Int_map int_map = { {1, 1}, {2, 2}, {3, 3 }};" << std::endl;
  Int_map int_map = { {1, 1}, {2, 2}, {3, 3 }};
  std::cout << prhex_int_map("map  ", int_map.begin()) << std::endl;

  std::cout << "checking 3" << std::endl;
  Int_map_iter it_map_int3 = my_find_map(int_map, 3);
  if (it_map_int3 == int_map.end())
    std::cout << "nogots" << std::endl;
  else
    std::cout << "gots" << std::endl;

  std::cout << "checking 9" << std::endl;
  Int_map_iter it_map_int9 = my_find_map(int_map, 9);
  if (it_map_int9 == int_map.end())
    std::cout << "nogots" << std::endl;
  else
    std::cout << "gots" << std::endl;
}
