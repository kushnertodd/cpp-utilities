//
// Created by kushn on 6/21/2023.
//

#pragma once

#include <cstring>
#include <cstdlib>
#include <db_cxx.h>

template<typename K, typename T, typename L>
class Bdb_dbt {
 public:
  void *key_buf{};
  void *data_buf{};
  Dbt key_dto;
  Dbt data_dto;

  ~Bdb_dbt() {
    if (key_buf)
      std::free(key_buf);
    if (data_buf)
      std::free(data_buf);
  }

  Bdb_dbt() {}

  Bdb_dbt(const K &bdb_dto_key) {
    size_t key_len = bdb_dto_key.buffer_size();
    key_buf = std::malloc(key_len);
    std::memset(key_buf, '\0', key_len);
    bdb_dto_key.serialize(key_buf);
    key_dto.set_size((u_int32_t) key_len);
    key_dto.set_data(key_buf);
  }

  Bdb_dbt(const T &bdb_dto_data) {
    size_t data_len = bdb_dto_data.buffer_size();
    data_buf = std::malloc(data_len);
    std::memset(key_buf, '\0', data_len);
    bdb_dto_data.serialize(data_buf);
    key_dto.set_size((u_int32_t) data_len);
    key_dto.set_data(data_buf);
  }

  void set_key(K &bdb_dto_key) {
    bdb_dto_key.deserialize(key_dto.get_data());
  }
  void set_data(T &bdb_dto_data) {
    bdb_dto_data.deserialize(data_dto.get_data());
  }
  void set_data_list(L &bdb_dto_list) {
    bdb_dto_list.emplace_back(data_dto.get_data());
  }
};
