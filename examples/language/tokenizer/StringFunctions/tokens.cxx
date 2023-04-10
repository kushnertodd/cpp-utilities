#include <iostream>
#include <sstream>
#include <cstring>
#include "tokens.h"

std::vector<std::string> stl_tokenize(const std::string& s, const char delim)
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

std::vector<std::string> my_tokenize(const std::string& s, const char delim)
{
  char delims[2] = { delim, '\0' };
  Tokens* tokens = new Tokens(s, delims);
  std::vector<std::string>  token_list;
  std::string token;
  while (tokens->next(token)) {
    token_list.push_back(token);
  }
  return token_list;
}

/*
 * parses tokens from string
 *
 * functions:
 *   token_init()  initializes token parser struct
 *   token_next()  returns pointer to the next token, or NULL if done
 *
 * algorithm:
 *   tokens are built by parsing the next character in a string
 *   if the character is a letter, it is added to the token
 *   if the character is a delimiter, the token is returned
 *   if the character is eos ('\0'), the token is returned or "" if the last
 *     character is a delimiter
 *
 * states:
 *   START       before parsing the first token
 *   SAW_DELIM   last parsed character was a delimiter
 *   SAW_LETTER  last parsed character was a letter
 *   DONE        last parsed character was eos ('\0')
 *
 * state diagram:
 *
 *   state       char    action           new state
 *   ----------  ------  ---------------  ---------
 *   initial             buffer = buf     START
 *   START       eos     return NULL      DONE
 *               letter  *buffer++ = c    SAW_LETTER
 *               delim   return ""        SAW_DELIM
 *   SAW_DELIM   eos     return ""        DONE
 *               letter  *buffer++ = c    SAW_LETTER
 *               delim   return ""        SAW_DELIM
 *   SAW_LETTER  eos     *buffer = '\0'   DONE
 *                       return buf
 *               letter  *buffer++ = c    SAW_LETTER
 *               delim   *buffer = '\0'   SAW_DELIM
 *                       buffer = buf
 *                       return buf
 *   DONE        eos     return NULL      DONE
 *               letter  return NULL      DONE
 *               delim   return NULL      DONE
 */

//Tokens::Tokens(const char *line, const char *delims) :
Tokens::Tokens(const std::string& line, const char* delims) :
  //ptr(line),
  ptr(line.c_str()),
  delims(delims) {
  state = START;
}

enum CHAR_TYPE Tokens::char_type(char c) {
  if (is_eos(c))
    return EOS;
  if (is_delim(c))
    return DELIM;
  return LETTER;
}

int Tokens::is_delim(char c) {
  return (strchr(delims, c) != NULL);
}

int Tokens::is_eos(char c) {
  return (c == '\0');
}

/**
 * prints line number if count >= 0
 */
//std::string Tokens::line_print(const char *str) {
std::string Tokens::line_print(int count, std::string str) {
  std::ostringstream os;
  if (count > -1)
    os << count << ": ";
  //for (const char *ptr = str, c = *ptr; c != '\0'; ptr++) {
  for (const char& c : str) {
    if (c == '\t') os << "<tab>";
    else if (c == '\n') os << "<nl>";
    else os << c;
  }
  return os.str();
}

bool Tokens::next(std::string& buffer) {
  buffer = "";
  while (true) {
    char c = *ptr++;
    switch (state) {
    case START: {
      switch (char_type(c)) {
      case EOS: {
        state = DONE;
        return false;
      }
      case LETTER: {
        buffer += c;
        state = SAW_LETTER;
        break;
      }
      case DELIM: {
        state = SAW_DELIM;
        buffer = "";
        return true;
      }
      }
      break;
    }
    case SAW_DELIM: {
      switch (char_type(c)) {
      case EOS: {
        state = DONE;
        buffer = "";
        return true;
      }
      case LETTER: {
        buffer += c;
        state = SAW_LETTER;
        break;
      }
      case DELIM: {
        buffer = "";
        return true;
      }
      }
      break;
    }
    case SAW_LETTER: {
      switch (char_type(c)) {
      case EOS: {
        state = DONE;
        return true;
      }
      case LETTER: {
        buffer += c;
        break;
      }
      case DELIM: {
        state = SAW_DELIM;
        return true;
      }
      }
      break;
    }
    case DONE: {
      return false;
    }
    }
  }
}

