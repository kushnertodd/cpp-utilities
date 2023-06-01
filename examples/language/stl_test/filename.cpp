#include <iomanip>
#include <iostream>

using namespace std;

void print(int pos, string path, string stmt) {
  cout << "pos "
       << setw(2)
       << pos
       << " '"
       << path
       <<"' "
       << left << setw(20)
       << stmt
       << " pref '"
       << left << setw(20)
       << path.substr(0, pos)
       << "' rest '"
       << left << setw(20)
       << path.substr(pos+1)
       << "'"
       << endl;
}

int main(int argc, char **argv)
{
  string path = "dir1/dir2/perf.stem.ext";
  int pos;
  string stmt;

  pos = path.find_first_of("/");
  stmt = "find_first_of('/');";
  print(pos, path, stmt);

  pos = path.find_last_of("/");
  stmt = "find_last_of('/');";
  print(pos, path, stmt);

  pos = path.find_first_of(".");
  stmt = "find_first_of('.');";
  print(pos, path, stmt);

  pos = path.find_last_of(".");
  stmt = "find_last_of('.');";
  print(pos, path, stmt);
}

