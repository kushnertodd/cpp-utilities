#pragma once

#include <db_cxx.h>
#include <fstream>
#include "bdb_errors.hpp"

class Bdb_env {
 public:
  // default constructor is not used.
  ~Bdb_env();
  Bdb_env();

  void close(u_int32_t flags = 0);
  void init(const std::string &db_home,
            int cache_gbytes,
            int cache_bytes,
            std::string &error_file,
            Bdb_Errors &errors);
  void open(const std::string &env_home, Bdb_Errors &errors);
  void set_error_log(const std::string &error_file, Bdb_Errors &errors);

  static inline std::string get_db_home() { return db_home; }
  static inline int get_cache_gbytes() { return cache_gbytes; }
  static inline int get_cache_bytes() { return cache_bytes; }

 private:
  DbEnv dbenv;
  std::ofstream err_file;
  static std::string db_home;
  static int cache_gbytes;
  static int cache_bytes;
};
