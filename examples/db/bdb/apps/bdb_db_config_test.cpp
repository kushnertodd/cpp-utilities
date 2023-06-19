#include <iostream>

#include "bdb_db_config.hpp"

int main() {
  auto &bdb_db_config=Bdb_db_config("db_file.db")
      .cache_gbytes(4)
      .cache_bytes(0)
      .can_create()
      .can_exist()
      .can_write()
      .has_duplicates()
      .is_secondary()
      .truncate();
  std::cout << bdb_db_config << std::endl;
  return EXIT_SUCCESS;
}