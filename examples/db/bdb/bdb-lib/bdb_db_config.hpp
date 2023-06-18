//
// Created by kushn on 6/18/2023.
//

#pragma once

#include <db_cxx.h>
#include <iostream>
#include <ostream>
#include <utility>
#include "bdb_errors.hpp"

// https://hackernoon.com/design-patterns-builder-pattern-in-modern-c-x1283uy3
// https://platis.solutions/blog/2023/01/03/builder-pattern-cpp/

class Bdb_db_config {
 private:
  Db db_;
  u_int32_t m_c_flags{};
  int m_cache_gbytes{4};
  int m_cache_bytes{};
  bool m_can_create{false};
  bool m_can_exist{false};
  bool m_can_write{false};
  std::string m_filename{};
  bool m_has_duplicates{false};
  bool m_is_open{false};
  bool m_is_secondary{false};
  bool m_truncate{false};

  void close();

 public:
  ~Bdb_db_config();
  Bdb_db_config() = delete;
  explicit Bdb_db_config(std::string filename);

  friend std::ostream &operator<<(std::ostream &os, const Bdb_db_config &bdb_db_config);
  static Bdb_db_config create(std::string filename);

  Bdb_db_config &cache_gbytes(int m_cache_gbytes);
  Bdb_db_config &cache_bytes(int cache_bytes);
  Bdb_db_config &can_create();
  Bdb_db_config &can_exist();
  Bdb_db_config &can_write();
  Bdb_db_config &has_duplicates();
  Bdb_db_config &is_secondary();
  Bdb_db_config &truncate();

  inline Db &get_db() { return db_; }
  void open(Bdb_Errors &errors);
};
