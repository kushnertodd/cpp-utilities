#include "static_member.hpp"
int A::b = 0;
const std::map<A::C, std::string> A::to_exts =
{
  {A::C::D,"D"},
  {A::C::E,"E"}
};

void A::a_b() {
  std::cout << "A::b " << b << std::endl;
}
