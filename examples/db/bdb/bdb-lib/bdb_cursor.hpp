#pragma once

#include <cstring>
#include <db_cxx.h>
#include "bdb_db.hpp"
#include "bdb_errors.hpp"

class Bdb_cursor {
 public:
  Dbc *cursorp;
  bool done{};
  bool eof{};

  Bdb_cursor() = delete;
  ~Bdb_cursor() {
    cursorp->close();
  }

  Bdb_cursor(Bdb_db &cursor_db, Bdb_errors &errors, DbTxn *txnid = nullptr) {
    // https://web.mit.edu/ghudson/dev/nokrb/third/db/docs/api_c/db_cursor.html
    try {
      int ret = cursor_db.get_db().cursor(txnid, &cursorp, 0);
      if (ret)
        errors.add("Bdb_cursor::Bdb_cursor", "1", "error opening cursor", ret);
    }
    catch (DbException &e) {
      errors.add("Bdb_DAO::select_all", "3", " error: " + std::string(e.what()));
    }
    catch (std::exception &e) {
      errors.add("Bdb_DAO::select_all", "4", " error: " + std::string(e.what()));
    }
  }

  template<typename K, typename T>
  void dto_get(K &bdb_key, T &bdb_dto, Bdb_errors &errors, int flags) {
    Dbt key;
    Dbt data;
    try {
      int ret = cursorp->get(&key, &data, flags);
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
    catch (DbException &e) {
      errors.add("Bdb_DAO::select_all", "3", " error: " + std::string(e.what()));
    }
    catch (std::exception &e) {
      errors.add("Bdb_DAO::select_all", "4", " error: " + std::string(e.what()));
    }
  }

  template<typename K, typename T>
  void dto_get_first(K &bdb_key, T &bdb_dto, Bdb_errors &errors) {
    dto_get(bdb_key, bdb_dto, errors, DB_FIRST);
  }

  template<typename K, typename T>
  void dto_get_next(K &bdb_key, T &bdb_dto, Bdb_errors &errors) {
    dto_get(bdb_key, bdb_dto, errors, DB_NEXT);
  }

  template<typename K, typename T>
  void dto_get_next_dup(K &bdb_key, T &bdb_dto, Bdb_errors &errors) {
    dto_get(bdb_key, bdb_dto, errors, DB_NEXT_DUP);
  }

  template<typename K, typename T>
  void dto_get_key(K &bdb_key, T &bdb_dto, Bdb_errors &errors) {
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
      errors.add("Bdb_DAO::lookup", "3", "Error writing file " + std::string(e.what()));
    }
    catch (std::exception &e) {
      errors.add("Bdb_DAO::lookup", "4", "Error writing file " + std::string(e.what()));
    }
    free(key_buf);
  }

  template<typename K, typename L>
  void dto_list_get(K &bdb_key, L &bdb_dto_list, Bdb_errors &errors, int flags) {
    Dbt data;
    Dbt key;
    try {
      int ret = cursorp->get(&key, &data, flags);
      if (ret == DB_NOTFOUND) {
        done = true;
        eof = true;
      } else if (ret) {
        done = true;
        errors.add("Bdb_cursor::get_first", "2", " select error", ret);
      } else {
        bdb_key.deserialize(key.get_data());
        bdb_dto_list.emplace_back(data.get_data());
      }
    }
    catch (DbException &e) {
      errors.add("Bdb_DAO::select_all", "3", " error: " + std::string(e.what()));
    }
    catch (std::exception &e) {
      errors.add("Bdb_DAO::select_all", "4", " error: " + std::string(e.what()));
    }
  }

  template<typename K, typename L>
  void dto_list_get_first(K &bdb_key, L &bdb_dto_list, Bdb_errors &errors) {
    dto_list_get(bdb_dto_list, bdb_key, errors, DB_FIRST);
  }
  template<typename K, typename L>
  void dto_list_get_next(K &bdb_key, L &bdb_dto_list, Bdb_errors &errors) {
    dto_list_get(bdb_dto_list, bdb_key, errors, DB_NEXT);
  }
  template<typename K, typename L>
  void dto_list_get_next_dup(K &bdb_key, L &bdb_dto_list, Bdb_errors &errors) {
    dto_list_get(bdb_dto_list, bdb_key, errors, DB_NEXT_DUP);
  }

  template<typename K, typename L>
  void dto_list_get_key(K &bdb_key, L &bdb_dto_list, Bdb_errors &errors) {
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
        errors.add("Bdb_DAO::lookup", "1", "key not found");
      } else if (ret) {
        done = true;
        errors.add("Bdb_cursor::get_first", "2", " select error", ret);
      } else
        bdb_dto_list.emplace_back(data.get_data());
    }
    catch (DbException &e) {
      errors.add("Bdb_DAO::lookup", "3", "Error writing file " + std::string(e.what()));
    }
    catch (std::exception &e) {
      errors.add("Bdb_DAO::lookup", "4", "Error writing file " + std::string(e.what()));
    }
    free(key_buf);
  }
};
