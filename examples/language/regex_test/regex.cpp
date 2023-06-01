#include <iostream>
#include <regex>
int main(int argc, char**argv) {
  if (argc < 3) {
    std::cout << "usage: " << argv[0] << " pattern string" << std::endl;
    return 1;
  }
  //std::string match_argv_str(argv[1]);
  const char* pat_argv_char=argv[1];
  std::string pat_argv_str(argv[1]);
  const char* match_argv_char = argv[2];
  std::string match_argv_str(argv[2]);

  std::regex pat_char (pat_argv_char,  std::regex_constants::ECMAScript | std::regex_constants::icase);
  std::regex pat_str (pat_argv_str,  std::regex_constants::ECMAScript | std::regex_constants::icase);

  if (std::regex_match(match_argv_char, pat_char))
    std::cout << "char-char regex_match succeeded" << std::endl;
  else
    std::cout << "char-char regex_match failed" << std::endl;

  if (std::regex_match(match_argv_str, pat_char))
    std::cout << "str-char regex_match succeeded" << std::endl;
  else
    std::cout << "str-char regex_match failed" << std::endl;

  if (std::regex_match(match_argv_char, pat_str))
    std::cout << "char-str regex_match succeeded" << std::endl;
  else
    std::cout << "char-str regex_match failed" << std::endl;

  if (std::regex_match(match_argv_str, pat_str))
    std::cout << "str-str regex_match succeeded" << std::endl;
  else
    std::cout << "str-str regex_match failed" << std::endl;

  if (std::regex_search(match_argv_char, pat_char))
    std::cout << "char-char regex_search succeeded" << std::endl;
  else
    std::cout << "char-char regex_search failed" << std::endl;

  if (std::regex_search(match_argv_str, pat_char))
    std::cout << "str-char regex_search succeeded" << std::endl;
  else
    std::cout << "str-char regex_search failed" << std::endl;

  if (std::regex_search(match_argv_char, pat_str))
    std::cout << "char-str regex_search succeeded" << std::endl;
  else
    std::cout << "char-str regex_search failed" << std::endl;

  if (std::regex_search(match_argv_str, pat_str))
    std::cout << "str-str regex_search succeeded" << std::endl;
  else
    std::cout << "str-str regex_search failed" << std::endl;

  std::smatch sm;
  if (std::regex_search(match_argv_str, sm, pat_str)) {
    std::cout << "str-str regex_search succeeded, size: " << sm.size() << std::endl;
    for (unsigned i = 0; i < sm.size(); i++) 
      std::cout << "  sm match " << i << ": '" << sm[i] << "'" << std::endl;
  } else
    std::cout << "str-str regex_search failed" << std::endl;

  std::cmatch cm;
  if (std::regex_search(match_argv_char, cm, pat_str)) {
    std::cout << "str-str regex_search succeeded, size: " << cm.size() << std::endl;
    for (unsigned i = 0; i < cm.size(); i++) 
      std::cout << "  cm match " << i << ": '" << cm[i] << "'" << std::endl;
  } else
    std::cout << "str-str regex_search failed" << std::endl;

  std::smatch msm;
  if (std::regex_match(match_argv_str, msm, pat_str)) {
    std::cout << "str-str regex_match succeeded, size: " << msm.size() << std::endl;
    for (unsigned i = 0; i < msm.size(); i++) 
      std::cout << "  msm match " << i << ": '" << msm[i] << "'" << std::endl;
  } else
    std::cout << "str-str regex_match failed" << std::endl;

}
