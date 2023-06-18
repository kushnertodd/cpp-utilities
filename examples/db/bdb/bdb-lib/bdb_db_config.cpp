//
// Created by kushn on 6/18/2023.
//

#include "bdb_db_config.hpp"

#include <utility>

// Bdb_db_config methods

Bdb_db_config::~Bdb_db_config() {
  close();
}

Bdb_db_config::Bdb_db_config(std::string filename)
    :
//db_(nullptr, 0),
    m_filename(std::move(filename)) {}

Bdb_db_config Bdb_db_config::create(std::string filename) {
  return Bdb_db_config{std::move(filename)};
}

std::ostream &operator<<(std::ostream &os, const Bdb_db_config &bdb_db_config) {
  return os
      << "cache_gbytes   " << bdb_db_config.m_cache_gbytes << std::endl
      << "cache_bytes    " << bdb_db_config.m_cache_bytes << std::endl
      << "can_create     " << bdb_db_config.m_can_create << std::endl
      << "can_exist      " << bdb_db_config.m_can_exist << std::endl
      << "can_write      " << bdb_db_config.m_can_write << std::endl
      << "filename       " << bdb_db_config.m_filename << std::endl
      << "has_duplicates " << bdb_db_config.m_has_duplicates << std::endl
      << "is_open        " << bdb_db_config.m_is_open << std::endl
      << "is_secondary   " << bdb_db_config.m_is_secondary << std::endl
      << "truncate       " << bdb_db_config.m_truncate << std::endl;
}

// configuration methods

Bdb_db_config &Bdb_db_config::cache_gbytes(int cache_gbytes) {
  m_cache_gbytes = cache_gbytes;
  return *this;
}
Bdb_db_config &Bdb_db_config::cache_bytes(int cache_bytes) {
  m_cache_bytes = cache_bytes;
  return *this;
}
Bdb_db_config &Bdb_db_config::can_create() {
  m_can_create = true;
  return *this;
}
Bdb_db_config &Bdb_db_config::can_exist() {
  m_can_exist = true;
  return *this;
}
Bdb_db_config &Bdb_db_config::can_write() {
  m_can_write = true;
  return *this;
}
Bdb_db_config &Bdb_db_config::has_duplicates() {
  m_has_duplicates = true;
  return *this;
}
Bdb_db_config &Bdb_db_config::is_secondary() {
  m_is_secondary = true;
  return *this;
}
Bdb_db_config &Bdb_db_config::truncate() {
  m_truncate = true;
  return *this;
}

// runtime methods

void Bdb_db_config::close() {
  try {
    // https://docs.oracle.com/cd/E17076_05/html/api_reference/C/dbclose.html
//    if (m_is_open)
//      db_.close(0);
  }
  catch (DbException &e) {
    std::cerr << "Error closing database: " << m_filename << " (" << e.what() << ")" << std::endl;
  }
  catch (std::exception &e) {
    std::cerr << "Error closing database: " << m_filename << " (" << e.what() << ")" << std::endl;
  }
}

void Bdb_db_config::open(Bdb_Errors &errors) {
/*
  try {
    // If this is a secondary database, support
    // sorted duplicates

    int cache_gbytes = Bdb_env::get_cache_gbytes();
    int cache_bytes = Bdb_env::get_cache_bytes();
    int ret = db_.set_cachesize(cache_gbytes, cache_bytes, 1);
    if (ret)
      errors.add("BDB_db::open", "1", " set_cachesize error ", ret);
    db_.set_error_stream(&std::cerr);
    int ret1;
    if (is_secondary)
      ret1 = db_.set_flags(DB_DUPSORT);
    else if (has_duplicates)
      ret1 = db_.set_flags(DB_DUP);

    // Open the database
    // https://docs.oracle.com/cd/E17076_05/html/api_reference/C/dbopen.html
    if (!errors.has()) {
      m_is_opentrue
    };
    if (Bdb_global::debug)
      std::cout << "Bdb_db::open(" << Bdb_file_IO::to_string(db_file_name) << ")" << std::endl;
    ret = db_.open(nullptr, db_file_name.c_str(), nullptr, DB_BTREE, c_flags, 0);
    if (ret)
      errors.add("BDB_db::open", "2", db_file_name + " open error ", ret);
  }
}
// DbException is not a subclass of std::exception, so we
// need to catch them both.
catch (DbException &e) {
  errors.add("BDB_db::open", "3", db_file_name + " (" + e.what() + ")", e.get_errno());
}
catch (std::exception &e) {
  errors.add("BDB_db::open", "4", db_file_name + " (" + e.what() + ")");
}
  }
*/
}