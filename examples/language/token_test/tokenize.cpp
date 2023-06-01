#include <vector>
#include <iostream>

std::vector<std::string> tokenize(const std::string& s, const char delim)
{
  std::vector<std::string> result;

  std::string::size_type from = 0;
  std::string::size_type stop = s.find(delim);

  while (stop != std::string::npos)
  {
    result.push_back(s.substr(from, stop - from));
    from = stop + 1;
    stop = s.find(delim, from);
  }

  result.push_back(s.substr(from));

  return result;
}

int main(int argc, char**argv) {
  if (argc < 3) {
    std::cout << "usage: " << argv[0] << " delim line" << std::endl;
  } else {
    char delim = *argv[1];
    std::string line(argv[2]);
    std::vector<std::string> tokens = tokenize(line, delim);
    for (std::string token : tokens) {
      std::cout << "'" << token << "'" << std::endl;
    }
  }
}
