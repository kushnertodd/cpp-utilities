#include <iostream>
#include <regex>

bool is_numeric(std::string number) {
  //std::string pat_numeric_str = "([+-])?(\\d+)\\.(\\d*)|([+-])?(\\d*)\\.(\\d+)|([+-])?(\\d+)";
  std::string pat_numeric_str = R"(([+-])?(\d+)\.(\d*)|([+-])?(\d*)\.(\d+)|([+-])?(\d+))";
  std::regex pat_numeric (pat_numeric_str,  std::regex_constants::ECMAScript | std::regex_constants::icase);
  return std::regex_match(number, pat_numeric);
}

int main(int argc, char**argv) {
  if (argc < 2) {
    std::cout << "usage: " << argv[0] << " number-string" << std::endl;
    return 1;
  }
  std::string number_string=argv[1];

  std::string pat_numeric_str = "([+-])?(\\d+)\\.(\\d*)|([+-])?(\\d*)\\.(\\d+)|([+-])?(\\d+)";
  std::regex pat_numeric (pat_numeric_str,  std::regex_constants::ECMAScript | std::regex_constants::icase);

  if (std::regex_match(number_string, pat_numeric)) {
    std::cout << "regex_match(\"" << number_string << "\") succeeded" << std::endl;
  } else
    std::cout << "regex_match(\"" << number_string << "\") failed" << std::endl;

  if (is_numeric(number_string)) 
    std::cout << "is_numeric(\"" << number_string << "\") succeeded" << std::endl;
  else
    std::cout << "is_numeric(\"" << number_string << "\") failed" << std::endl;

}
