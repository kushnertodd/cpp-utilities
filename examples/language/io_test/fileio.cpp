#include <cstring>
#include <sstream>
#include "fileio.hpp"

File_IO::File_IO(const std::string &filename_, Errors &errors) : filename(filename_) {
  std::cout << "File_IO(" << filename << ")" << std::endl;
  //open(filename, errors);
}

File_IO::~File_IO() {
  std::cout << "~File_IO()" << std::endl;
}

void File_IO::close() {
  std::cout << "File_IO::close()" << std::endl;
}

void File_IO::open(const std::string &filename, Errors &errors) {
  std::cout << "File_IO::open("<<filename<<")" << std::endl;
}

void File_IO::strerror_safe(char *buf, int buflen, int err_code) {
  if (strerror_r(err_code, buf, buflen) != nullptr)
    snprintf(buf, buflen, "Unknown error %d", err_code);
}

// File_IO_text_read methods

File_IO_text_read::~File_IO_text_read() {
  std::cout << "File_IO_text_read::~File_IO_text_read()" << std::endl;
  close();
}

File_IO_text_read::File_IO_text_read(const std::string &filename, Errors &errors) : File_IO(filename, errors) {
  std::cout << "File_IO_text_read::File_IO_text_read(" << filename << ")" << std::endl;
  open(filename, errors);
}

void File_IO_text_read::close()  {
  std::cout << "File_IO_text_read::close()" << std::endl;
  in_file.close();
}

std::string File_IO_text_read::getfile(Errors &errors) {
  std::stringstream strStream;
  // https://cplusplus.com/reference/ios/ios/rdbuf/
  strStream << in_file.rdbuf();
  return strStream.str();
}

bool File_IO_text_read::getline(std::string &line, Errors &errors) {
  std::getline(in_file, line);
  const size_t buflen = 200;
  char buf[buflen];
  if (in_file.bad()) {
    File_IO::strerror_safe(buf, buflen, errno);
    errors.add("File_IO_text_write::getline", "1", filename + " (" + std::string(buf) + ")");
    return false;
  } else if (in_file.fail()) {
    if (errno) {
      File_IO::strerror_safe(buf, buflen, errno);
      errors.add("File_IO_text_write::getline", "2", filename + " (" + std::string(buf) + ")");
    }
    return false;
  } else if (in_file.eof()) {
    return false;
  }
  return true;
}

void File_IO_text_read::open(const std::string &filename, Errors &errors)  {
  std::cout << "File_IO_text_read::open(" << filename << ")" << std::endl;
  File_IO::open(filename, errors);
  in_file.open(filename);
  const size_t buflen = 200;
  char buf[buflen];
  if (in_file.bad()) {
    File_IO::strerror_safe(buf, buflen, errno);
    errors.add("File_IO::open_read", "1", filename + " (" + std::string(buf) + ")");
  } else if (in_file.fail()) {
    File_IO::strerror_safe(buf, buflen, errno);
    errors.add("File_IO::open_read", "2", filename + " (" + std::string(buf) + ")");
  } else if (in_file.eof()) {
    File_IO::strerror_safe(buf, buflen, errno);
    errors.add("File_IO::open_read", "3", filename + " (" + std::string(buf) + ")");
  }
}

// File_IO_text_write methods

File_IO_text_write::~File_IO_text_write() {
  std::cout << "File_IO_text_write::~File_IO_text_write()" << std::endl;
  close();
}

File_IO_text_write::File_IO_text_write(const std::string &filename, Errors &errors) : File_IO(filename, errors) {
  std::cout << "File_IO_text_write::File_IO_text_write(" << filename << ")" << std::endl;
  open(filename, errors);
}

void File_IO_text_write::close()  {
  std::cout << "File_IO_text_write::close(" << filename << ")" << std::endl;
  File_IO::close();
  out_file.close();
}

void File_IO_text_write::open(const std::string &filename, Errors &errors) {
  std::cout << "File_IO_text_write::open(" << filename << ")" << std::endl;
  out_file.open(filename, std::ios::out);
  const size_t buflen = 200;
  char buf[buflen];
  if (out_file.bad()) {
    File_IO::strerror_safe(buf, buflen, errno);
    errors.add("File_IO_text_write::open", "1", filename + " (" + std::string(buf) + ")");
  } else if (out_file.fail()) {
    File_IO::strerror_safe(buf, buflen, errno);
    errors.add("File_IO_text_write::open", "2", filename + " (" + std::string(buf) + ")");
  } else if (out_file.eof()) {
    File_IO::strerror_safe(buf, buflen, errno);
    errors.add("File_IO_text_write::open", "3", filename + " (" + std::string(buf) + ")");
  }
}

void File_IO_text_write::putline(const std::string &line, Errors &errors) {
  out_file << line << std::endl;
}
