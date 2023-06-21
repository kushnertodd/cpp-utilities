#pragma once

#include <cstring>
#include <db_cxx.h>
#include "bdb_db.hpp"
#include "bdb_dbt.hpp"
#include "bdb_errors.hpp"

template<typename K, typename T, typename L>
class Bdb_cursor {
 private:
  Bdb_db &bdb_db;
  Dbc *cursorp{};
  bool done{};
  bool eof{};

 public:
  inline bool is_done() { return done; }
  inline bool is_eof() { return done; }

  Bdb_cursor() = delete;
  ~Bdb_cursor() {
    cursorp->close();
  }

  Bdb_cursor(Bdb_db &cursor_db, Bdb_errors &errors, DbTxn *txnid = nullptr) :
      bdb_db(cursor_db) {
    // https://web.mit.edu/ghudson/dev/nokrb/third/db/docs/api_c/db_cursor.html
    try {
      int ret = cursor_db.get_db().cursor(txnid, &cursorp, 0);
      if (ret)
        errors.add("Bdb_cursor::Bdb_cursor", "1", "error opening cursor in database " + bdb_db.to_string(), ret);
    }
    catch (DbException &e) {
      errors.add("Imdb_DAO::lookup", "3", "Error writing in database " + bdb_db.to_string() + std::string(e.what()));
    }
    catch (std::exception &e) {
      errors.add("Imdb_DAO::lookup", "4", "Error writing in database " + bdb_db.to_string() + std::string(e.what()));
    }
  }

  void dto_get(K &bdb_key_dto, T &bdb_data_dto, Bdb_errors &errors, int flags) {
    Bdb_dbt<K, T, L> bdb_dbt{};
    try {
      int ret = cursorp->get(&bdb_dbt.get_key_dbt(), &bdb_dbt.get_data_dbt(), flags);
      if (ret == DB_NOTFOUND) {
        done = true;
        eof = true;
      } else if (ret) {
        done = true;
        errors.add("Bdb_cursor::get_first", "2", " select error in database " + bdb_db.to_string(), ret);
      } else {
        bdb_dbt.set_key_dto(bdb_key_dto);
        bdb_dbt.set_data_dto(bdb_data_dto);
      }
    }
    catch (DbException &e) {
      errors.add("Imdb_DAO::lookup", "3", "Error writing in database " + bdb_db.to_string() + std::string(e.what()));
    }
    catch (std::exception &e) {
      errors.add("Imdb_DAO::lookup", "4", "Error writing in database " + bdb_db.to_string() + std::string(e.what()));
    }
  }

  void dto_get_first(K &bdb_key_dto, T &bdb_data_dto, Bdb_errors &errors) {
    dto_get(bdb_key_dto, bdb_data_dto, errors, DB_FIRST);
  }

  void dto_get_next(K &bdb_key_dto, T &bdb_data_dto, Bdb_errors &errors) {
    dto_get(bdb_key_dto, bdb_data_dto, errors, DB_NEXT);
  }

  void dto_list_get(K &bdb_key_dto, L &bdb_data_dto_list, Bdb_errors &errors, int flags) {
    Bdb_dbt<K, T, L> bdb_dbt{};

    try {
      int ret = cursorp->get(&bdb_dbt.get_key_dbt(), &bdb_dbt.get_data_dbt(), flags);
      if (ret == DB_NOTFOUND) {
        done = true;
        eof = true;
      } else if (ret) {
        done = true;
        errors.add("Bdb_cursor::get_first", "2", " select error in database " + bdb_db.to_string(), ret);
      } else {
        bdb_dbt.set_key_dto(bdb_key_dto);
        bdb_dbt.set_data_dto_list(bdb_data_dto_list);
      }
    }
    catch (DbException &e) {
      errors.add("Imdb_DAO::lookup", "3", "Error writing in database " + bdb_db.to_string() + std::string(e.what()));
    }
    catch (std::exception &e) {
      errors.add("Imdb_DAO::lookup", "4", "Error writing in database " + bdb_db.to_string() + std::string(e.what()));
    }
  }

  void dto_list_get_first(K &bdb_key_dto, L &bdb_data_dto_list, Bdb_errors &errors) {
    dto_list_get(bdb_key_dto, bdb_data_dto_list, errors, DB_FIRST);
  }

  void dto_list_get_next(K &bdb_key_dto, L &bdb_data_dto_list, Bdb_errors &errors) {
    dto_list_get(bdb_key_dto, bdb_data_dto_list, errors, DB_NEXT);
  }

  void dto_get_set(K &bdb_key_dto, T &bdb_data_dto, Bdb_errors &errors) {
    Bdb_dbt<K, T, L> bdb_dbt{};
    try {
      int ret = cursorp->get(&bdb_dbt.bdb_key_dbt, &bdb_dbt.bdb_data_dbt, DB_SET);
      if (ret == DB_NOTFOUND) {
        done = true;
        eof = true;
      } else if (ret) {
        done = true;
        errors.add("Bdb_cursor::get_first", "2", " select error in database " + bdb_db.to_string(), ret);
      } else
        bdb_dbt.set_data_dto(bdb_data_dto);
    }
    catch (DbException &e) {
      errors.add("Imdb_DAO::lookup", "3", "Error writing in database " + bdb_db.to_string() + std::string(e.what()));
    }
    catch (std::exception &e) {
      errors.add("Imdb_DAO::lookup", "4", "Error writing in database " + bdb_db.to_string() + std::string(e.what()));
    }
  }

  void dto_list_get_set(K &bdb_key_dto, L &bdb_data_dto_list, Bdb_errors &errors) {
    Bdb_dbt<K, T, L> bdb_dbt{};
    try {
      int ret = cursorp->get(&bdb_dbt.key_dto, &bdb_dbt.data_dto, DB_SET);
      if (ret == DB_NOTFOUND) {
        done = true;
        eof = true;
      } else if (ret) {
        done = true;
        errors.add("Bdb_cursor::dto_list_get_set", "2", " select error in database " + bdb_db.to_string(), ret);
      } else {
        bdb_dbt.set_data_dto_list(bdb_data_dto_list);
      }
    }
    catch (DbException &e) {
      errors.add("Bdb_cursor::dto_list_get_set",
                 "3",
                 "Error writing in database " + bdb_db.to_string() + std::string(e.what()));
    }
    catch (std::exception &e) {
      errors.add("Bdb_cursor::dto_list_get_set",
                 "4",
                 "Error writing in database " + bdb_db.to_string() + std::string(e.what()));
    }
  }
};
