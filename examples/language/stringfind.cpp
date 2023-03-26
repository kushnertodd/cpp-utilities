#include <iostream>

using namespace std;

void stringSplitFindLast(string text, string& first, string& second, string pat) {
  size_t pos = text.find_last_of(pat);
  if (pos != string::npos) {
    first = text.substr(0, pos);
    second = text.substr(pos + 1);
  } else {
    first = "";
    second = text;
  }
}

void stringSplitFindFirst(string text, string& first, string& second, string pat) {
  size_t pos = text.find_first_of(pat);
  if (pos != string::npos) {
    first = text.substr(0, pos);
    second = text.substr(pos + 1);
  } else {
    first = "";
    second = text;
  }
}

int main() {
  string first, second;

  string text = "foo/bar/baz.faz.txt";
  stringSplitFindLast(text, first, second, "/");
  cout <<
       "stringSplitFindLast("<<text<<", first, second, '/'); first '" << first << "' second '" << second << "'" << endl;

  stringSplitFindLast(text, first, second, ".");
  cout <<
       "stringSplitFindLast("<<text<<", first, second, '.'); first '" << first << "' second '" << second << "'" << endl;

  stringSplitFindFirst(text, first, second, "/");
  cout <<
       "stringSplitFindFirst("<<text<<", first, second, '/'); first '" << first << "' second '" << second << "'" << endl;

  stringSplitFindFirst(text, first, second, ".");
  cout <<
       "stringSplitFindFirst("<<text<<", first, second, '.'); first '" << first << "' second '" << second << "'" << endl;

  stringSplitFindLast(text, first, second, "az");
  cout <<
       "stringSplitFindLast("<<text<<", first, second, 'az'); first '" << first << "' second '" << second << "'" << endl;

  stringSplitFindFirst(text, first, second, "az");
  cout <<
       "stringSplitFindFirst("<<text<<", first, second, 'az'); first '" << first << "' second '" << second << "'" << endl;

}
