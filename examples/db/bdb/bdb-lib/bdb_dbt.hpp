//
// Created by kushn on 6/21/2023.
//

#pragma once

#include <cstring>
#include <cstdlib>
#include <db_cxx.h>

template<typename K, typename T, typename L>
class Bdb_dbt {
 private:
  void *buffer{};
  Dbt dbt;

 public:
  inline Dbt &get_dbt() { return dbt; }

  ~Bdb_dbt() {
    if (buffer)
      std::free(buffer);
  }

  Bdb_dbt() {}

  Bdb_dbt(const K &bdb_dto) {
    size_t len = bdb_dto.buffer_size();
    buffer = std::malloc(len);
    std::memset(buffer, '\0', len);
    bdb_dto.serialize(buffer);
    dbt.set_size((u_int32_t) len);
    dbt.set_data(buffer);
  }

  void set_dto(K &bdb_dto) {
    bdb_dto.deserialize(dbt.get_data());
  }
  void set_dto_list(L &bdb_dto_list) {
    bdb_dto_list.emplace_back(dbt.get_data());
  }
};
