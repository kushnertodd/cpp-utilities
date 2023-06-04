#include "fileio.hpp"

enum class Test { TEST1, TEST2, TEST3, TEST4 };
std::string test_to_string(Test test) {
  switch(test) {
  case Test::TEST1:
    return "TEST1";
  case Test::TEST2:
    return "TEST2";
  case Test::TEST3:
    return "TEST3";
  case Test::TEST4:
    return "TEST4";
  }
  return "unknown test: " + std::to_string(static_cast<int>(test));
}

int main(int argc, char** argv) {
  Errors errors;
  std::string filename;
  Test test = Test::TEST4;
  std::cout << "test " << test_to_string(test) << std::endl;
  // test1: invalid file
  if (test == Test::TEST1)
    filename = "fileiox.txt";
  else
    // test2...: valid file
    filename = "fileio.txt";

  std::cout << "fileio_test_read: opening " << filename << std::endl;
  File_IO_text_read fread(filename, errors);
  if (errors.has())
    std::cout << errors.to_string() << std::endl;
  else {
    // test3: read whole file
    if (test == Test::TEST3) {
      std::string file = fread.getfile(errors);
      if (errors.has())
        std::cout << errors.to_string() << std::endl;
      else
        std::cout << filename << ":" << std::endl;
      std::cout << file << std::endl;
    } else if (test == Test::TEST4) {
      // test4: read file line by line
      std::string line;
      std::cout << filename << ":" << std::endl;
      for (int count = 1; fread.getline(line, errors) && !errors.has(); count++)
        std::cout << line << std::endl;
      if (errors.has())
        std::cout << errors.to_string() << std::endl;
    }
  }
}

