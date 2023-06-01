#include <map>
#include <string>
using Int = int;
std::map<int, Int> foo = {{1,2},{3,4}};
using Cmdline_opt_arg = struct cmdline_opt_arg {
  int i;
  std::string s;
};
using Cmdline_opt_args = std::map<char, Cmdline_opt_arg>;
Cmdline_opt_args opt_args = {{'c', {1, "foo"}}};
int main() {
  Int i{3};
}
