#include <cerrno>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <utility>
#include <sys/stat.h>
#include "bdb_file_io.hpp"
#include "bdb_global.hpp"
#ifdef _WIN32
#include <direct.h>
#define get_current_dir _getcwd
#else
#include <unistd.h>
#define get_current_dir getcwd
#endif

std::string Bdb_file_IO::comma_format(long num, int width) {
  std::locale comma_locale(std::locale(), new comma_numpunct());
  std::ostringstream os;
  os.imbue(comma_locale);
  if (width == 0)
    os << num;
  else
    os << std::setw(width) << num;
  return os.str();
}

void Bdb_file_IO::create_directory(std::string &dirname, Bdb_errors &errors) {
  struct stat info{};
  if (stat(dirname.c_str(), &info) != 0) {
    int ret = mkdir(dirname.c_str(), 0755);
    if (ret)
      errors.add("File_IO::create_directory", "1", "create directory " + dirname + " failed", errno);
  } else if (!(info.st_mode & S_IFDIR))
    errors.add("File_IO::create_directory", "2", dirname + " failed, exists as a file", errno);
}

/*
 * get current working directory
 */
std::string Bdb_file_IO::get_current_directory() {
  char buf[FILENAME_MAX]; //create string buffer to hold path
  if (get_current_dir(buf, FILENAME_MAX) == nullptr)
    return "";
  std::string current_working_dir(buf);
  return current_working_dir;
}

void Bdb_file_IO::progress(int count) {
  if (count % 100000 == 0) {
    std::cerr << std::endl << Bdb_file_IO::comma_format(count, 12) << " ";
    std::flush(std::cerr);
  }
  if (count % 1000 == 0) {
    std::cout << ".";
    std::flush(std::cout);
  }
}

void Bdb_file_IO::strerror_safe(char *buf, int buflen, int err_code) {
  char *error = strerror_r(err_code, buf, buflen);
  if (error)
    snprintf(buf, buflen, "Error: %s", error);
}

std::string Bdb_file_IO::to_string(const std::string &filename) {
  return Bdb_file_IO::get_current_directory() + "/" + filename;
}

// File_IO_text_read methods

Bdb_File_IO_text_read::~Bdb_File_IO_text_read() {
  if (Bdb_global::debug)
    std::cout << "File_IO_text_read::~File_IO_text_read()" << std::endl;
  close();
}

Bdb_File_IO_text_read::Bdb_File_IO_text_read(std::string filename_, Bdb_errors &errors)
    : filename(std::move(filename_)) {
  if (Bdb_global::debug)
    std::cout << "File_IO_text_read::open(" << Bdb_file_IO::to_string(filename) << ")" << std::endl;
  open(errors);
}

void Bdb_File_IO_text_read::close() {
  if (Bdb_global::debug) std::cout << "File_IO_text_read::close()" << std::endl;
  in_file.close();
}

std::string Bdb_File_IO_text_read::getfile(Bdb_errors &errors) {
  std::stringstream strStream;
  // https://cplusplus.com/reference/ios/ios/rdbuf/
  strStream << in_file.rdbuf();
  return strStream.str();
}

bool Bdb_File_IO_text_read::getline(std::string &line, Bdb_errors &errors) {
  std::getline(in_file, line);
  const size_t buflen = 200;
  char buf[buflen];
  auto res = in_file.rdstate();
  if (Bdb_global::debug) std::cout << "File_IO_text_read::getline iostate " << res << std::endl;
  if (in_file.bad()) {
    Bdb_file_IO::strerror_safe(buf, buflen, errno);
    errors.add("File_IO_text_read::getline", "1", Bdb_file_IO::to_string(filename) + " (" + std::string(buf) + ")");
    return false;
  } else if (in_file.eof()) {
    return false;
  } else if (in_file.fail()) {
    if (errno) {
      Bdb_file_IO::strerror_safe(buf, buflen, errno);
      errors.add("File_IO_text_read::getline", "2", Bdb_file_IO::to_string(filename) + " (" + std::string(buf) + ")");
    }
    return false;
  }
  return true;
}

void Bdb_File_IO_text_read::open(Bdb_errors &errors) {
  if (Bdb_global::debug)
    std::cout << "File_IO_text_read::open(" << Bdb_file_IO::to_string(filename) << ")" << std::endl;
  in_file.open(filename);
  const size_t buflen = 200;
  char buf[buflen];
  if (in_file.bad()) {
    Bdb_file_IO::strerror_safe(buf, buflen, errno);
    errors.add("File_IO::open_read", "1", Bdb_file_IO::to_string(filename) + " (" + std::string(buf) + ")");
  } else if (in_file.fail()) {
    Bdb_file_IO::strerror_safe(buf, buflen, errno);
    errors.add("File_IO::open_read", "2", Bdb_file_IO::to_string(filename) + " (" + std::string(buf) + ")");
  } else if (in_file.eof()) {
    Bdb_file_IO::strerror_safe(buf, buflen, errno);
    errors.add("File_IO::open_read", "3", Bdb_file_IO::to_string(filename) + " (" + std::string(buf) + ")");
  }
}

// File_IO_text_write methods

Bdb_File_IO_text_write::~Bdb_File_IO_text_write() {
  if (Bdb_global::debug) std::cout << "File_IO_text_write::~File_IO_text_write()" << std::endl;
  close();
}

Bdb_File_IO_text_write::Bdb_File_IO_text_write(std::string filename_, Bdb_errors &errors)
    : filename(std::move(filename_)) {
  open(errors);
}

void Bdb_File_IO_text_write::close() {
  if (Bdb_global::debug)
    std::cout << "File_IO_text_write::close(" << Bdb_file_IO::to_string(filename) << ")" << std::endl;
  out_file.close();
}

void Bdb_File_IO_text_write::open(Bdb_errors &errors) {
  if (Bdb_global::debug)
    std::cout << "File_IO_text_write::open(" << Bdb_file_IO::to_string(filename) << ")" << std::endl;
  out_file.open(filename, std::ios::out);
  const size_t buflen = 200;
  char buf[buflen];
  if (out_file.bad()) {
    Bdb_file_IO::strerror_safe(buf, buflen, errno);
    errors.add("File_IO_text_write::open", "1", Bdb_file_IO::to_string(filename) + " (" + std::string(buf) + ")");
  } else if (out_file.fail()) {
    Bdb_file_IO::strerror_safe(buf, buflen, errno);
    errors.add("File_IO_text_write::open", "2", Bdb_file_IO::to_string(filename) + " (" + std::string(buf) + ")");
  } else if (out_file.eof()) {
    Bdb_file_IO::strerror_safe(buf, buflen, errno);
    errors.add("File_IO_text_write::open", "3", Bdb_file_IO::to_string(filename) + " (" + std::string(buf) + ")");
  }
}

void Bdb_File_IO_text_write::putline(const std::string &line, Bdb_errors &errors) {
  out_file << line << std::endl;
}

