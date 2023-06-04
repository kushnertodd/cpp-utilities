#pragma once

#include <fstream>
#include <iostream>
#include "errors.hpp"

class File_IO {
public:
  std::string filename;

  File_IO(const std::string &filename_, Errors &errors);
  virtual ~File_IO();
  virtual void open(const std::string &filename, Errors &errors);
  virtual void close();
  static void strerror_safe(char *buf, int buflen, int err_code);
};

class File_IO_text_read : private File_IO {
private:
  std::ifstream in_file;
public:
  ~File_IO_text_read();
  File_IO_text_read(const std::string &filename, Errors &errors);
  void open(const std::string &filename, Errors &errors) ;
  void close() ;
  std::string getfile(Errors &errors);
  bool getline(std::string &line, Errors &errors);
};

class File_IO_text_write : private File_IO {
public:
  std::ofstream out_file;
public:
  ~File_IO_text_write();
  File_IO_text_write(const std::string &filename, Errors &errors);
  void open(const std::string &filename, Errors &errors) ;
  void close() ;
  void putline(const std::string &line, Errors &errors);
};
