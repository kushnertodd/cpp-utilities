//
// Created by kushn on 6/18/2023.
//

#include <sstream>
#include <utility>
#include "bdb_db_config.hpp"
#include "bdb_db_config_builder.hpp"

// Bdb_db_config methods

Bdb_db::Bdb_db_config::~Bdb_db_config() {
  close();
}

void Bdb_db::Bdb_db_config::close() noexcept {
  try {
    // https://docs.oracle.com/cd/E17076_05/html/api_reference/C/dbclose.html
    db_.close(0);
  }
  catch (DbException &e) {
    std::cerr <<Bdb_error("Bdb_db::Bdb_db_config::close", "1",
                              "Error closing database: " + m_filename + " (" + e.what() + ")").to_string();
  }
  catch (std::exception &e) {
    std::cerr <<Bdb_error("Bdb_db::Bdb_db_config::close", "1",
                              "Error closing database: " + m_filename + " (" + e.what() + ")").to_string();
  }
}

std::string Bdb_db::Bdb_db_config::to_string() {
  std::ostringstream os;
  os      << "cache_gbytes   " << m_cache_gbytes << std::endl
      << "cache_bytes    " << m_cache_bytes << std::endl
      << "can_create     " << m_can_create << std::endl
      << "can_exist      " << m_can_exist << std::endl
      << "can_write      " << m_can_write << std::endl
      << "filename       " << m_filename << std::endl
      << "has_duplicates " << m_has_duplicates << std::endl
      << "is_secondary   " << m_is_secondary << std::endl
      << "truncate       " << m_truncate << std::endl;
  return os.str();
}

// Bdb_db methods

Bdb_db::Bdb_db(std::string filename)
    : m_bdb_db_config{new Bdb_db_config{std::move(filename)}} {}

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

void Bdb_db::bdb_open(Bdb_errors &errors) {
  try {
    // If this is a secondary database, support sorted duplicates

    if (m_bdb_db_config->m_can_create)
      m_bdb_db_config->m_c_flags = DB_CREATE;
    m_bdb_db_config->db_.set_cachesize(m_bdb_db_config->m_cache_gbytes, m_bdb_db_config->m_cache_bytes, 1);
    if (!errors.has()) {
      m_bdb_db_config->db_.set_error_stream(&std::cerr);
      if (m_bdb_db_config->m_is_secondary)
        m_bdb_db_config->db_.set_flags(DB_DUPSORT);
      else if (m_bdb_db_config->m_has_duplicates)
        m_bdb_db_config->db_.set_flags(DB_DUP);

      // Open the database
      // https://docs.oracle.com/cd/E17076_05/html/api_reference/C/dbopen.html
      int ret = m_bdb_db_config->db_.open(nullptr,
                                          m_bdb_db_config->m_filename.c_str(),
                                          nullptr,
                                          DB_BTREE,
                                          m_bdb_db_config->m_c_flags,
                                          0);
      if (ret)
        errors.add("BDB_db::open", "2", "Error opening database: " + m_bdb_db_config->m_filename, ret);
    }
  }
    // DbException is not a subclass of std::exception, so we need to catch them both.
  catch (DbException &e) {
    errors.add("BDB_db::open",
               "3",
               "Error opening database: " + m_bdb_db_config->m_filename + " (" + e.what() + ")",
               e.get_errno());
  }
  catch (std::exception &e) {
    errors.add("BDB_db::open", "4", "Error opening database: " + m_bdb_db_config->m_filename + " (" + e.what() + ")");
  }
}

std::string Bdb_db::to_string() {
  return m_bdb_db_config->to_string();
}

std::unique_ptr<Bdb_db::Bdb_db_config> Bdb_db::open(Bdb_errors &errors) {
  //bdb_open(errors);
  return std::move(m_bdb_db_config);
}