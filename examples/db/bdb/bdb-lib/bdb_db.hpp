#pragma once

#include <db_cxx.h>
#include "bdb_errors.hpp"

class Bdb_db {
 public:
  // builds the BDB_db object
  // default constructor is not used.
  Bdb_db() = delete;

  // Constructor requires a database name.
  // builds and opens the BDB object
  Bdb_db(const std::string &db_name, Bdb_Errors &errors);

  // Our destructor just calls our private close method.
  ~Bdb_db();

  inline Db &get_db() { return db_; }
  inline std::string get_db_filename() { return db_file_name; }

  // called by the second constructor, must be called separately on using the first constructor
  void open(Bdb_Errors &errors);
  std::string to_string();

 private:
  u_int32_t c_flags{};
  Db db_;
  std::string db_file_name{};
  bool is_secondary{};
  bool has_duplicates{};

  // This is called from our destructor, private method is more appropriate
  void close();

};
