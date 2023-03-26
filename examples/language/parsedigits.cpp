#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

enum  TokType {
  DIGIT,
  ALPHA
};

string tokTypeToString(TokType tokType)
{
  if (tokType == DIGIT) return "DIGIT";
  else return "ALPHA";
}

class Token
{
public:
  TokType tokType;
  string text;
  Token(TokType m_tokType, string m_text) : tokType(m_tokType), text(m_text) {}
  string toString() {
    if (tokType == DIGIT)
      return "digits: " + text;
    else
      return "alphas: " + text;
  }
};

int main(int argc, char **argv)
{
  string digits("0123456789");
  if (argc < 2)
  {
    cout << "usage: parsedigits input" << endl;
    exit(0);
  }
  string input(argv[1]);
  int len = input.length();
  if (len == 0)
  {
    // case 0: empty
    cout << "empty string: len " << len << endl;
  }
  else
  {
    vector<Token*> tokens;
    TokType nextTokenType;

    // find first token type
    string first = input.substr(0, 1);
    int pos = digits.find(first);
    if (pos == string::npos)
    {
      // first character is non-digit
      nextTokenType = ALPHA;
    }
    else
    {
      // first character is digit
      nextTokenType = DIGIT;
    }
    cout << "input '" << input << "' first token type " << tokTypeToString(nextTokenType) << endl;

    bool done = false;
    int beg = 0;
    pos = 0;
    while (!done)
    {
      if (nextTokenType == ALPHA)
      {
        cout << " find first digit or eos " << endl;
        pos = input.find_first_of("0123456789", beg);
        cout << "next token type " << tokTypeToString(nextTokenType) << " beg " << beg << " pos " << pos;
        if (pos == string::npos)
        {
          string alphas = input.substr(beg);
          cout << "  rest of the string are alphas '" << alphas << "'" << endl;
          tokens.push_back(new Token(ALPHA, alphas));
          done = true;
        }
        else
        {
          string alphas = input.substr(beg, pos-beg);
          cout << "  next token is alpha '" << alphas << "' input '" << input << "'" << endl;
          tokens.push_back(new Token(ALPHA, alphas));
          nextTokenType = DIGIT;
          beg = pos;
        }
      }
      else // next token type DIGIT
      {
        cout << " find first alpha or eos " << endl;
        pos = input.find_first_not_of("0123456789", beg);
        cout << "next token type " << tokTypeToString(nextTokenType) << " beg " << beg << " pos " << pos;
        if (pos == string::npos)
        {
          string number = input.substr(beg);
          cout << "  rest of the string are digits '" << number << "'" << endl;
          tokens.push_back(new Token(DIGIT, number));
          done = true;
        }
        else
        {
          string number = input.substr(beg, pos-beg);
          cout << "  next token is digits '" << number << "' input '" << input << "'" << endl;
          tokens.push_back(new Token(DIGIT, number));
          nextTokenType = ALPHA;
          beg = pos;
        }
      }
    }
    cout << "tokens:" << endl;
    for (vector<Token*>::iterator it = tokens.begin(); it != tokens.end(); it++)
    {
      Token* token = *it;
      cout << "  token " << token->toString();
    }
    cout << endl;
  }
}
