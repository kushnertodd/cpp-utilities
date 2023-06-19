#include <iostream>

#include "bdb_errors.hpp"
#include "bdb_db_config.hpp"

int main() {
  Bdb_errors errors;
  auto bdb_db = Bdb_db("db_file.db")
      .cache_gbytes(4)
      .cache_bytes(0)
      .can_create()
      .must_exist()
      .read_only()
      .has_duplicates()
      .is_secondary()
      .truncate()
      .open(errors);
  std::cout << bdb_db->to_string() << std::endl;
  return EXIT_SUCCESS;
}