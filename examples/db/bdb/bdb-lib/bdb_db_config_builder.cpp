//
// Created by kushn on 6/18/2023.
//

#include "bdb_db_config.hpp"

// Bdb_db_config methods

Bdb_db_config_builder Bdb_db_config::create() {
  return Bdb_db_config_builder{};
}

std::ostream &operator<<(std::ostream &os, const Bdb_db_config &bdb_db_config) {
  return os
      << "can_create" << bdb_db_config.can_create << std::endl
      << "can_exist" << bdb_db_config.can_exist << std::endl
      << "can_write" << bdb_db_config.can_write << std::endl
      << "can_truncate" << bdb_db_config.can_truncate << std::endl;
}

// Bdb_db_config_builder methods

Bdb_db_config_builder &Bdb_db_config_builder::can_create() {
  bdb_db_config.can_create = true;
  return *this;
}
Bdb_db_config_builder &Bdb_db_config_builder::can_exist() {
  bdb_db_config.can_exist = true;
  return *this;
}
Bdb_db_config_builder &Bdb_db_config_builder::can_write() {
  bdb_db_config.can_write = true;
  return *this;
}
Bdb_db_config_builder &Bdb_db_config_builder::can_truncate() {
  bdb_db_config.can_truncate = true;
  return *this;
}

