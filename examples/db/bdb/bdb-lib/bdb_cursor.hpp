#pragma once

#include <string>
#include <db_cxx.h>
#include "bdb_db.hpp"
#include "bdb_errors.hpp"

template<typename T, typename K, typename L>
class Bdb_cursor {
 public:
  Dbc *cursorp;
  bool done{};
  bool eof{};

  Bdb_cursor() = default;
  ~Bdb_cursor() {
    cursorp->close();
  }

  Bdb_cursor(Bdb_db &cursor_db, Bdb_errors &errors, DbTxn *txnid = nullptr) {
    // https://web.mit.edu/ghudson/dev/nokrb/third/db/docs/api_c/db_cursor.html
    int ret = cursor_db.get_db().cursor(txnid, &cursorp, 0);
    if (ret)
      errors.add("Bdb_cursor::Bdb_cursor", "1", "error opening cursor", ret);
  }

  void dto_get_first(K &bdb_key, T &bdb_dto, Bdb_errors &errors) {
    Dbt key;
    Dbt data;
    int ret = cursorp->get(&key, &data, DB_FIRST;
    if (ret == DB_NOTFOUND) {
      done = true;
      eof = true;
    } else if (ret) {
      done = true;
      errors.add("Bdb_cursor::get_first", "2", " select error", ret);
    } else {
      bdb_dto.deserialize(data.get_data());
      bdb_key.deserialize(key.get_data());
    }
  }

  void dto_list_get_first(L &bdb_dto_list, K &bdb_key, Bdb_errors &errors) {
    Dbt data;
    Dbt key;
    int ret = cursorp->get(&key, &data, DB_FIRST;
    if (ret == DB_NOTFOUND) {
      done = true;
      eof = true;
    } else if (ret) {
      done = true;
      errors.add("Bdb_cursor::get_first", "2", " select error", ret);
    } else {
      bdb_dto_list.emplace_back(data.get_data());
      bdb_key.deserialize(key.get_data());
    }
  }

  void dto_get_set(K &bdb_key, T &bdb_dto, Bdb_errors &errors) {
    size_t key_len = bdb_key.buffer_size();
    void *key_buf = std::malloc(key_len);
    std::memset(key_buf, '\0', key_len);
    bdb_key.serialize(key_buf);

    Dbt key(key_buf, (u_int32_t) key_len);
    Dbt data;
    try {
      int ret = cursorp->get(&key, &data, DB_SET);
      if (ret == DB_NOTFOUND) {
        done = true;
        eof = true;
      } else if (ret) {
        done = true;
        errors.add("Bdb_cursor::get_first", "2", " select error", ret);
      } else {
        bdb_dto.deserialize(data.get_data());
      }
    }
    catch (DbException &e) {
      errors.add("Imdb_DAO::lookup", "3", "Error writing file " + std::string(e.what()));
    }
    catch (std::exception &e) {
      errors.add("Imdb_DAO::lookup", "4", "Error writing file " + std::string(e.what()));
    }
    free(key_buf);
  }

  void dto_list_get_set(L &bdb_dto_list, K &bdb_key, Bdb_errors &errors) {
    size_t key_len = imdb_key.buffer_size();
    void *key_buf = std::malloc(key_len);
    std::memset(key_buf, '\0', key_len);
    imdb_key.serialize(key_buf);

    Dbt key(key_buf, (u_int32_t) key_len);
    Dbt data;
    try {
      int ret = cursorp->get(&key, &data, DB_FIRST;
      if (ret == DB_NOTFOUND) {
        done = true;
        eof = true;
      } else if (ret) {
        done = true;
        errors.add("Bdb_cursor::get_first", "2", " select error", ret);
      } else {
        bdb_dto_list.emplace_back(data.get_data());
      }
    }
  }
};
