#pragma once

#include <fstream>
#include <iostream>
#include "errors.hpp"

class File_IO {
public:
  std::string &filename;

  File_IO(std::string &filename_, Errors &errors);
  virtual ~File_IO();
  virtual void open(const std::string &filename, Errors &errors);
  virtual void close();
  static void strerror_safe(char *buf, int buflen, int err_code);
};

class File_IO_text_read : private File_IO {
private:
  std::ifstream in_file;

  ~File_IO_text_read();
  File_IO_text_read(const std::string &filename, Errors &errors);
  void open(const std::string &filename, Errors &errors) ;
  void close() ;
  std::string get_file(Errors &errors);
  bool getline(std::string &line, Errors &errors);
};

class File_IO_text_write : private File_IO {
public:
  std::ofstream out_file;

  ~File_IO_text_write();
  File_IO_text_write(const std::string &filename, Errors &errors);
  void open(const std::string &filename, Errors &errors) ;
  void close() ;
  void put_line(const std::string &line, Errors &errors);
};
