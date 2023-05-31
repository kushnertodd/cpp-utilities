#include <iostream>
#include <map>
struct Arg { std::string name; bool required{}; bool have{}; };
enum class Arguments { DB_CONFIG_FILENAME, GBYTES };
std::map<Arguments, Arg> args = { { Arguments::DB_CONFIG_FILENAME, {"arg1", true, false}} };
//Arg(int have_) : have{have_} {}
//std::map<Args, Arg> args = { { Args::ARG1, {"arg1", true}}, { Args::ARG2, {"arg2", false}} }; */
//std::map<int, Arg> args = { { 1, {2}} };

int main() {
//  Arg arg{1};
}
