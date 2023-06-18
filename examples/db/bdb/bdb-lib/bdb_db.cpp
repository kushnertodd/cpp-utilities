#include "bdb_db.hpp"

Bdb_db::~Bdb_db() {
  close();
}

// Class constructor. Requires a location where the database is located, and a database name
Bdb_db::Bdb_db(const std::string &db_name, Bdb_Errors &errors, bool is_secondary_, bool has_duplicates_)
    : db_(nullptr, 0),               // Instantiate Db object
      db_file_name(Bdb_env::get_db_home() + "/" + db_name), // Database file name
      is_secondary(is_secondary_),
      has_duplicates(has_duplicates_),
      c_flags(DB_CREATE)          // If the database doesn't yet exist,
{
  if (Bdb_global::debug)
    std::cout << "Bdb_db::Bdb_db: opening " << db_file_name << std::endl;
  open(errors);
}

/*
 * Private member used to close a database. Called from the class destructor.
 * - Assume close() occurs at the program end, no worries not to trap the error
 * - When called on a database that is the primary database for a secondary index,
 *   the primary database should be closed only after all secondary indices referencing
 *   it has been closed.
 * If DB->open() fails, the DB->close() method must be called to discard the DB handle.
 */
void Bdb_db::close() {
  // Close the db
  try {
    // https://docs.oracle.com/cd/E17076_05/html/api_reference/C/dbclose.html
    db_.close(0);
  }
  catch (DbException &e) {
    std::cerr << "Error closing database: " << db_file_name << " (" << e.what() << ")" << std::endl;
  }
  catch (std::exception &e) {
    std::cerr << "Error closing database: " << db_file_name << " (" << e.what() << ")" << std::endl;
  }
}

void Bdb_db::open(Bdb_Errors &errors) {
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

std::string Bdb_db::to_string() {
  return get_db_filename();
}

