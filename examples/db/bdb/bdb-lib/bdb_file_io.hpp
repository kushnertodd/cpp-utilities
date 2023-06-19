#pragma once

#include <fstream>      // std::ifstream
#include <iostream>
#include <sstream>
#include "bdb_errors.hpp"

class comma_numpunct : public std::numpunct<char> {
 protected:
  char do_thousands_sep() const override {
    return ',';
  }

  std::string do_grouping() const override {
    return "\03";
  }
};

// ios::exceptions
// https://cplusplus.com/reference/ios/ios/exceptions/
// https://cplusplus.com/doc/tutorial/files/
// https://www.tutorialspoint.com/cplusplus/cpp_files_streams.htm
class Bdb_file_IO {
 public:
  static std::string comma_format(long num, int width = 0);
  static void create_directory(std::string &dirname, Bdb_Errors &errors);
  static std::string get_current_directory();
  static void progress(int count);
  static void strerror_safe(char *buf, int buflen, int err_code);
  static std::string to_string(const std::string &filename);
};

class Bdb_File_IO_text_read {
 private:
  std::string filename;
  std::ifstream in_file;
 public:
  ~Bdb_File_IO_text_read();
  Bdb_File_IO_text_read(std::string filename_, Bdb_Errors &errors);
  void open(Bdb_Errors &errors);
  void close();
  std::string getfile(Bdb_Errors &errors);
  bool getline(std::string &line, Bdb_Errors &errors);
};

class Bdb_File_IO_text_write {
 public:
  std::string filename;
  std::ofstream out_file;
 public:
  ~Bdb_File_IO_text_write();
  Bdb_File_IO_text_write(std::string filename_, Bdb_Errors &errors);
  void open(Bdb_Errors &errors);
  void close();
  void putline(const std::string &line, Bdb_Errors &errors);
};
