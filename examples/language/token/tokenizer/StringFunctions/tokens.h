#pragma once
#include <vector>

std::vector<std::string> stl_tokenize(const std::string& s, const char delim);
std::vector<std::string> my_tokenize(const std::string& s, const char delim);

enum STATE {
  START,
  SAW_DELIM,
  SAW_LETTER,
  DONE
};

enum CHAR_TYPE {
  DELIM,
  EOS,
  LETTER
};

class Tokens {
private:
  enum STATE state;
  const char* ptr;
  const char* delims;

  enum CHAR_TYPE char_type(char c);
  int is_delim(char c);
  static int is_eos(char c);
public:
  //Tokens(const char *line, const char *delims);
  Tokens(const std::string& line, const char* delims);
  // static std::string line_print(int count, const char *str);
  static std::string line_print(int count, std::string str);
  bool next(std::string& token);
};
