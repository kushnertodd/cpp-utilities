#pragma once

#include <cstring>
#include <db_cxx.h>
#include "bdb_db.hpp"
#include "bdb_dbt.hpp"
#include "bdb_errors.hpp"

template<typename T, typename K, typename L>
class Bdb_cursor {
 public:
  Dbc *cursorp{};
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

  void dto_get_first(K &bdb_key_dto, T &bdb_data_dto, Bdb_errors &errors) {
    Bdb_dbt<K, T, L> bdb_dbt_key{};
    Bdb_dbt<K, T, L> bdb_dbt_data{};
    try {
      int ret = cursorp->get(&bdb_dbt_key.key_dto, &bdb_dbt_data.data_dto, DB_FIRST);
      if (ret == DB_NOTFOUND) {
        done = true;
        eof = true;
      } else if (ret) {
        done = true;
        errors.add("Bdb_cursor::get_first", "2", " select error", ret);
      } else {
        bdb_dbt_data.set_data(bdb_data_dto);
        bdb_dbt_key.set_key(bdb_key_dto);
      }
    }
    catch (DbException &e) {
      errors.add("Imdb_DAO::lookup", "3", "Error writing file " + std::string(e.what()));
    }
    catch (std::exception &e) {
      errors.add("Imdb_DAO::lookup", "4", "Error writing file " + std::string(e.what()));
    }
  }

  void dto_list_get_first(K &bdb_key_dto, L &bdb_data_dto_list, Bdb_errors &errors) {
    Bdb_dbt<K, T, L> bdb_dbt_key{};
    Bdb_dbt<K, T, L> bdb_dbt_data_list{};
    try {
      int ret = cursorp->get(&bdb_dbt_key.key_dto, &bdb_dbt_data_list.data_dto, DB_FIRST);
      if (ret == DB_NOTFOUND) {
        done = true;
        eof = true;
      } else if (ret) {
        done = true;
        errors.add("Bdb_cursor::get_first", "2", " select error", ret);
      } else {
        bdb_dbt_data_list.set_data(bdb_dbt_data_list);
        bdb_dbt_key.set_key(bdb_key_dto);
      }
    }
    catch (DbException &e) {
      errors.add("Imdb_DAO::lookup", "3", "Error writing file " + std::string(e.what()));
    }
    catch (std::exception &e) {
      errors.add("Imdb_DAO::lookup", "4", "Error writing file " + std::string(e.what()));
    }
  }

  void dto_get_set(K &bdb_key_dto, T &bdb_data_dto, Bdb_errors &errors) {
    Bdb_dbt<K, T, L> bdb_dbt_key{};
    Bdb_dbt<K, T, L> bdb_dbt_data{};
    try {
      int ret = cursorp->get(&bdb_dbt_key.key_dto, &bdb_dbt_data.data_dto, DB_SET);
      if (ret == DB_NOTFOUND) {
        done = true;
        eof = true;
      } else if (ret) {
        done = true;
        errors.add("Bdb_cursor::get_first", "2", " select error", ret);
      } else {
        bdb_dbt_data.set_data(bdb_data_dto);
      }
    }
    catch (DbException &e) {
      errors.add("Imdb_DAO::lookup", "3", "Error writing file " + std::string(e.what()));
    }
    catch (std::exception &e) {
      errors.add("Imdb_DAO::lookup", "4", "Error writing file " + std::string(e.what()));
    }
  }

  void dto_list_get_set(K &bdb_key_dto, L &bdb_data_dto_list, Bdb_errors &errors) {
    Bdb_dbt<K, T, L> bdb_dbt_key{};
    Bdb_dbt<K, T, L> bdb_dbt_data_list{};
    try {
      int ret = cursorp->get(&bdb_dbt_key.key_dto, &bdb_dbt_data_list.data_dto, DB_FIRST);
      if (ret == DB_NOTFOUND) {
        done = true;
        eof = true;
      } else if (ret) {
        done = true;
        errors.add("Bdb_cursor::get_first", "2", " select error", ret);
      } else {
        bdb_dbt_data_list.set_data(bdb_dbt_data_list);
      }
    }
    catch (DbException &e) {
      errors.add("Imdb_DAO::lookup", "3", "Error writing file " + std::string(e.what()));
    }
    catch (std::exception &e) {
      errors.add("Imdb_DAO::lookup", "4", "Error writing file " + std::string(e.what()));
    }
  }
};
