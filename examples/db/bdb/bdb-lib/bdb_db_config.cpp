//
// Created by kushn on 6/18/2023.
//

#include "bdb_db_config.hpp"
#include "bdb_db_config_builder.hpp"

#include <utility>

// Bdb_db_config methods

Bdb_db::Bdb_db_config::~Bdb_db_config() {
  close();
}

Bdb_db::Bdb_db_config::Bdb_db_config(std::string filename) :
    db_(nullptr, 0),
    m_filename(std::move(filename)) {}

std::ostream &operator<<(std::ostream &os, const Bdb_db::Bdb_db_config &bdb_db_config) {
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

Bdb_db &Bdb_db::cache_gbytes(int cache_gbytes) {
  m_bdb_db_config->m_cache_gbytes = cache_gbytes;
  return *this;
}
Bdb_db &Bdb_db::cache_bytes(int cache_bytes) {
  m_bdb_db_config->m_cache_bytes = cache_bytes;
  return *this;
}
Bdb_db &Bdb_db::can_create() {
  m_bdb_db_config->m_can_create = true;
  return *this;
}
Bdb_db &Bdb_db::can_exist() {
  m_bdb_db_config->m_can_exist = true;
  return *this;
}
Bdb_db &Bdb_db::can_write() {
  m_bdb_db_config->m_can_write = true;
  return *this;
}
Bdb_db &Bdb_db::has_duplicates() {
  m_bdb_db_config->m_has_duplicates = true;
  return *this;
}
Bdb_db &Bdb_db::is_secondary() {
  m_bdb_db_config->m_is_secondary = true;
  return *this;
}
Bdb_db &Bdb_db::truncate() {
  m_bdb_db_config->m_truncate = true;
  return *this;
}

// runtime methods

void Bdb_db::Bdb_db_config::close() {
  try {
    // https://docs.oracle.com/cd/E17076_05/html/api_reference/C/dbclose.html
    if (m_is_open)
      db_.close(0);
  }
  catch (DbException &e) {
    std::cerr << "Bdb_db::Bdb_db_config::close: Error closing database: " << m_filename << " (" << e.what() << ")"
              << std::endl;
  }
  catch (std::exception &e) {
    std::cerr << "Bdb_db::Bdb_db_config::close: Error closing database: " << m_filename << " (" << e.what() << ")"
              << std::endl;
  }
}

std::unique_ptr<Bdb_db_config> Bdb_db::open(Bdb_Errors &errors) {
  try {
    // If this is a secondary database, support
    // sorted duplicates

    if (m_can_create)
      m_c_flags = DB_CREATE;
    int ret = db_.set_cachesize(m_cache_gbytes, m_cache_bytes, 1);
    if (ret)
      errors.add("BDB_db::open", "1", " set_cachesize error ", ret);
    if (!errors.has()) {
      db_.set_error_stream(&std::cerr);
      if (m_is_secondary)
        ret = db_.set_flags(DB_DUPSORT);
      else if (m_has_duplicates)
        ret = db_.set_flags(DB_DUP);

      // Open the database
      // https://docs.oracle.com/cd/E17076_05/html/api_reference/C/dbopen.html
      ret = db_.open(nullptr, m_filename.c_str(), nullptr, DB_BTREE, m_c_flags, 0);
      if (ret)
        errors.add("BDB_db::open", "2", "Error opening database: " + m_filename, ret);
      else
        m_is_open = true;
    }
  }
    // DbException is not a subclass of std::exception, so we need to catch them both.
  catch (DbException &e) {
    errors.add("BDB_db::open", "3", "Error opening database: " + m_filename + " (" + e.what() + ")", e.get_errno());
  }
  catch (std::exception &e) {
    errors.add("BDB_db::open", "4", "Error opening database: " + m_filename + " (" + e.what() + ")");
  }
  return std::move(m_bdb_db_config);
}