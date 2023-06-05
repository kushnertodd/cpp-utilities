#include "fileio.hpp"

enum class Test { TEST1, TEST2, TEST3 };
std::string test_to_string(Test test) {
  switch (test) {
    case Test::TEST1:
      return "TEST1";
    case Test::TEST2:
      return "TEST2";
    case Test::TEST3:
      return "TEST3";
  }
  return "unknown test: " + std::to_string(static_cast<int>(test));
}

int main(int argc, char **argv) {
  Errors errors;
  std::string filename;
  Test test = Test::TEST3;
  std::cout << "test " << test_to_string(test) << std::endl;
  // test1: invalid file
  if (test == Test::TEST1)
    filename = "fileiox.txt";
  else
    // test2...: valid file
    filename = "fileio_out.txt";

  std::cout << "fileio_test_write: opening " << filename << std::endl;
  File_IO_text_write fwrite(filename, errors);
  if (errors.has())
    std::cout << errors.to_string() << std::endl;
  else {
    // test3: write file line
    std::string line = "line 1";
    fwrite.putline(line, errors);
    if (errors.has())
      std::cout << errors.to_string() << std::endl;
  }
}

