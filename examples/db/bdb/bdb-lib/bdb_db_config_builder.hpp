//
// Created by kushn on 6/18/2023.
//

#pragma once

#include <iostream>
#include <ostream>

// https://hackernoon.com/design-patterns-builder-pattern-in-modern-c-x1283uy3
// https://platis.solutions/blog/2023/01/03/builder-pattern-cpp/

class Bdb_db_config_builder;

class Bdb_db_config {
 private:
  bool can_create{false};
  bool can_exist{false};
  bool can_write{false};
  bool can_truncate{false};

Bdb_db_config() = default;
//  Bdb_db_config(bool can_create_, bool can_exist_, bool can_write_, bool do_not_truncate_)
//      : can_create(can_create_), can_exist(can_exist_), can_write(can_write_), can_truncate(can_truncate) {}

 public:
  friend class Bdb_db_config_builder;
  friend std::ostream &operator<<(std::ostream &os, const Bdb_db_config &bdb_db_config);
  static Bdb_db_config create();
};

class Bdb_db_config_builder {
  Bdb_db_config bdb_db_config;

 public:
  Bdb_db_config_builder() = default;
  explicit operator Bdb_db_config() const {
    return bdb_db_config;
  }

  Bdb_db_config_builder &can_create();
  Bdb_db_config_builder &can_exist();
  Bdb_db_config_builder &can_write();
  Bdb_db_config_builder &can_truncate();

};