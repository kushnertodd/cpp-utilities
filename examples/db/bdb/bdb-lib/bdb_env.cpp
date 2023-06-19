#include "bdb_file_io.hpp"
#include "bdb_env.hpp"

std::string Bdb_env::db_home{};
int Bdb_env::cache_gbytes{4};
int Bdb_env::cache_bytes{0};

Bdb_env::~Bdb_env() { close(); }

Bdb_env::Bdb_env() : dbenv(DB_CXX_NO_EXCEPTIONS) {}

void Bdb_env::close(u_int32_t flags) {
  int ret = 0;
  Bdb_Errors errors;
  err_file.close();
  try {
    ret = dbenv.close((u_int32_t) flags);
    if (ret != 0)
      errors.add("Bdb_env::close", "2", "DbEnv close", ret);
  } catch (DbException &e) {
    errors.add("Bdb_env::close", "3", "DbEnv close: " + std::string(e.what()), ret);
  }
  catch (std::exception &e) {
    errors.add("Bdb_env::close", "3", "DbEnv close: " + std::string(e.what()));
  }
  if (errors.has())
    std::cerr << errors.to_string() << std::endl;
}

void Bdb_env::init(const std::string &db_home_,
                   int cache_gbytes_,
                   int cache_bytes_,
                   std::string &error_file,
                   Bdb_Errors &errors) {
  db_home = db_home_;
  cache_gbytes = cache_gbytes_;
  cache_bytes = cache_bytes_;
  set_error_log(error_file, errors);
}

void Bdb_env::open(const std::string &env_home, Bdb_Errors &errors) {
  int ret = dbenv.open(env_home.c_str(), DB_CREATE | DB_INIT_MPOOL, 0);
  if (ret) {
    errors.add("Bdb_env::open", "2", "open failed", ret);
  }
}

void Bdb_env::set_error_log(const std::string &error_file, Bdb_Errors &errors) {
  dbenv.set_errpfx("DbEnv");
  Bdb_File_IO_text_write fwrite(error_file, errors);
  if (!errors.has())
    dbenv.set_error_stream(&fwrite.out_file);
}
