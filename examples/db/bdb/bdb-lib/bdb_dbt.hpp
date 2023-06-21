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
  void *key_buf{};
  void *data_buf{};
  Dbt key_dbt;
  Dbt data_dbt;

 public:
  inline Dbt &get_key_dbt() { return key_dbt; }
  inline Dbt &get_data_dbt() { return data_dbt; }

  ~Bdb_dbt() {
    if (key_buf)
      std::free(key_buf);
    if (data_buf)
      std::free(data_buf);
  }

  Bdb_dbt() {}

  Bdb_dbt(const K &bdb_key_dto) {
    size_t key_len = bdb_key_dto.buffer_size();
    key_buf = std::malloc(key_len);
    std::memset(key_buf, '\0', key_len);
    bdb_key_dto.serialize(key_buf);
    key_dbt.set_size((u_int32_t) key_len);
    key_dbt.set_data(key_buf);
  }

  Bdb_dbt(const T &bdb_data_dto) {
    size_t data_len = bdb_data_dto.buffer_size();
    data_buf = std::malloc(data_len);
    std::memset(key_buf, '\0', data_len);
    bdb_data_dto.serialize(data_buf);
    data_dbt.set_size((u_int32_t) data_len);
    data_dbt.set_data(data_buf);
  }

  void set_key_dto(K &bdb_key_dto) {
    bdb_key_dto.deserialize(key_dbt.get_data());
  }
  void set_data_dto(T &bdb_data_dto) {
    bdb_data_dto.deserialize(data_dbt.get_data());
  }
  void set_data_dto_list(L &bdb_data_dto_list) {
    bdb_data_dto_list.emplace_back(data_dbt.get_data());
  }
};
