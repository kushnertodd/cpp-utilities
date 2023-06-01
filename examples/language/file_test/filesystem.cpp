#include <iostream>
#include <iomanip>
#include <iterator>
#include <string>
#include <vector>
using namespace std;

vector<string> tokenize(string str, string delims) {
  vector<string> tokens;
  size_t beg, pos = 0;
  while ((beg = str.find_first_not_of(delims, pos)) != string::npos) {
    pos = str.find_first_of(delims, beg + 1);
    tokens.push_back(str.substr(beg, pos - beg));
  }
  return tokens;
}

// general filesystem definitions
typedef string FileSystemPath;
typedef string FileSystemDirname;
typedef vector<FileSystemDirname> FileSystemParentPath;
typedef string FileSystemParentPathName;
typedef string FileSystemFilename;
typedef string FileSystemStem;
typedef string FileSystemExtension;

// application specific definitions
typedef string Prefix;
typedef string TypeSpecific;
typedef string LinearFeatures;
typedef string LinearFeature;

class FileSystem {
public:
  friend ostream &operator<<(ostream &os, const FileSystem &fileSystem);
  FileSystemPath path;
  FileSystemParentPath parentPath;
  FileSystemParentPathName parentPathName;
  FileSystemFilename filename;
  FileSystemStem stem;
  FileSystemExtension ext;
  bool debug;

  FileSystem(FileSystemPath m_path,
             bool m_debug = false) :
    path(m_path),
    debug(m_debug) {
    // extract parent path and filename
    extractFileSystemComponents();
  }

  /**
   * extract file system components from path
   */
  void extractFileSystemComponents() {
    vector<string> pathParts = tokenize(path, "/");
    int nPathParts = pathParts.size();
    if (nPathParts == 1) {
      filename = pathParts[0];
    } else {
      parentPathName = "";
      for (int i = 0; i < nPathParts - 1; i++) {
        parentPath.push_back(pathParts[i]);
        parentPathName += (i == 0 ? pathParts[i] : "/" + pathParts[i]);
      }
      filename = pathParts[nPathParts - 1];
    }
    // extract stem and extension
    vector<string> filenameParts = tokenize(filename, ".");
    int nFilenameParts = filenameParts.size();
    stem = filenameParts[0];
    if (nFilenameParts == 1) {
      ext  = "";
    } else if (nFilenameParts == 2) {
      ext  = filenameParts[1];
    } else {
      if (debug) cout << "nFilenameParts " << nFilenameParts << endl;
      stem = "";
      for (int i = 0; i < nFilenameParts - 1; i++) {
        stem += (i > 0 ? "." + filenameParts[i] : filenameParts[i]);
        if (debug) cout << " filenameParts["<<i<<"] = " << filenameParts[i] << " stem " << stem << " ext " << ext << endl;
      }
      ext = filenameParts[nFilenameParts - 1];
      if (debug) cout << " filenameParts["<<nFilenameParts - 1<<"] = " << filenameParts[nFilenameParts - 1] << " ext " << ext << endl;
    }
  }
};

ostream &operator<<(ostream &os, const FileSystem &fileSystem) {
  os << "path '"
     << setw(20)
     << fileSystem.path
     << "' filename '"
     << setw(12)
     << fileSystem.filename
     << "' stem '"
     << setw(10)
     << fileSystem.stem
     << "' extension '"
     << setw(7)
     << fileSystem.ext
     << "' parentPathName '"
     << setw(10)
     << fileSystem.parentPathName
     << "' parent path ( ";
  for (FileSystemParentPath::const_iterator dirname = fileSystem.parentPath.begin();
       dirname != fileSystem.parentPath.end();
       dirname++) {
    os << (dirname == fileSystem.parentPath.begin() ? *dirname : "/" + *dirname);
  }
  os << " )";
  return os;
}

int main(int argc, char** argv) {
  if (argc < 2) {
    cout << "usage: filesystem filename" << endl;
    exit(0);
  }
  FileSystem fileSystem(argv[1], false);
  cout << "filesystem \"" << fileSystem << "\"" << endl;
}
