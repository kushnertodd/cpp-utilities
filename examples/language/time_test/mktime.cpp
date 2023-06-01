#include <ctime>
#include <cstdio>
#include <iomanip>
#include <iostream>

int main() {
  std::string date_time_str = "2020-09-09";
  std::string format = "%Y-%m-%d";
  struct std::tm when {};
  std::stringstream s(date_time_str);
  s >> std::get_time(&when, format.c_str());
  if (s.fail())
    std::cout << "Date/time format error: '" + date_time_str + "' format '" + format + "'" << std::endl;
  else {
    time_t time = std::mktime(&when);
    std::cout << "time " << time << std::endl;
    printf("     0x%08lx\n", time);
  }
}
