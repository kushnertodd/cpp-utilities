#include <iostream>
//#include <string>

using namespace std;

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    cout << "usage: stringstl <token>" << endl;
    exit(0);
  }
  string token(argv[1]);
  /*
   * cases:   len   pos
   *  0: ""    0    ---
   *  1: "1"   1    string:npos
   *  2: "f"   1    1
   *  3: "1f"  2    2
   */
  int len = token.length();
  if (len == 0)
  {
    // case 0: empty
    cout << "empty string: len " << len << endl;
  }
  else
  {
    // case 1-3: non-empty
    int beg = 0;
    // find first non-digit
    int pos = token.find_first_not_of("0123456789", beg);
    cout << "non-empty string: token '" << token << "' len " << len << " beg " << beg << " pos " << pos;
    if (pos == string::npos)
    {
      // case 1: all digits from beg to eos
      string digits = token.substr(beg, len-beg);
      cout << " case 1: digits through eos '" << digits << "'" << endl;

    }
    else
    {
      // case 2-3: found non-digit
      if (pos > beg)
      {
        // case 3: digits
        string digits = token.substr(beg, pos-beg);
        cout << " case 3: digits through non-digit '" << digits << "'" << endl;
      }
      else
      {
        // case 2: no digits
        cout << " case 2: no digits" << endl;
      }Token
    }
  }
}
