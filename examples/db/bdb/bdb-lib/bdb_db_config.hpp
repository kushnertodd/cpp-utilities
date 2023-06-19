//
// Created by kushn on 6/18/2023.
//

#pragma once

#include <db_cxx.h>
#include <iostream>
//#include <ostream>
#include <utility>
#include <memory>
#include "bdb_errors.hpp"

// https://platis.solutions/blog/2023/01/03/builder-pattern-cpp/

class Bdb_db {
 public:
  class Bdb_db_config {
   public:
   private:
    friend class Bdb_db;

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
    ~Bdb_db_config();
    explicit Bdb_db_config(std::string filename);
    inline Db &get_db() { return db_; }

    // https://learn.microsoft.com/en-us/cpp/standard-library/overloading-the-output-operator-for-your-own-classes?view=msvc-170
friend std::ostream &operator<<(std::ostream &os, const Bdb_db::Bdb_db_config &bdb_db_config);;=
  };

  std::unique_ptr<Bdb_db_config> open(Bdb_Errors &errors);
  Bdb_db& cache_gbytes(int m_cache_gbytes);
  Bdb_db& cache_bytes(int cache_bytes);
  Bdb_db& can_create();
  Bdb_db& can_exist();
  Bdb_db& can_write();
  Bdb_db& has_duplicates();
  Bdb_db& is_secondary();
  Bdb_db& truncate();
 private:
  std::unique_ptr<Bdb_db_config> m_bdb_db_config{};
};

std::ostream &operator<<(std::ostream &os, const Bdb_db::Bdb_db_config &bdb_db_config);
