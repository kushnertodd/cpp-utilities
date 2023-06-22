#pragma once

#include <cstring>
#include <db_cxx.h>
#include <json-c/json.h>
#include <sstream>
#include <vector>
#include "bdb_cursor.hpp"
#include "bdb_db.hpp"
#include "bdb_errors.hpp"
#include "bdb_file_io.hpp"
#include "serialization.hpp"

enum class Bdb_DAO_function { read, write };

template<typename K, typename T, typename L>
class Bdb_DAO {
 public:
  /*!
   * \brief load and save data DTOs from delimited text file records
   * \param bdb_db database handle
   * \param text_file delimited file, fields match data DTO T
   * \param errors invalid text file, bdb save failure
   * \param delimiter file record separator
   * \return record count
   * \precondition data DTO T has a constructor T(int cout, std::string line, errors, delimiter)
   * \precondition key DTO K has a constructor K(data DTO T)
   */
  static int load(Bdb_db &bdb_db, const std::string &text_file, Bdb_errors &errors, char delimiter = tab) {
    int count{};
    Bdb_File_IO_text_read fread(text_file, errors);
    if (!errors.has()) {
      std::string line;
      for (count = 0; fread.getline(line, errors) && !errors.has(); count++) {
        Bdb_file_IO::progress(count);
        if (count > 0) {
          T bdb_data_dto(count, line, errors, delimiter);
          K bdb_key_dto(bdb_data_dto);
          save(bdb_db, bdb_key_dto, bdb_data_dto, errors);
        }
      }
    }
    return count;
  }

  /*!
   * \brief lookup data DTO T from key DTO K
   * \param bdb_db database handle
   * \param bdb_key_dto key DTO for data DTO record
   * \param bdb_data_dto found data DTO record
   * \param errors includes key not found, read error, or bdb exception
   */
  static void lookup(Bdb_db &bdb_db, K &bdb_key_dto, T &bdb_data_dto, Bdb_errors &errors) {
    Bdb_dbt<K, T, L> bdb_key_dbt{bdb_key_dto};
    Bdb_dbt<K, T, L> bdb_dbt_data{};
    try {
      int ret = bdb_db.get_db().get(nullptr, &bdb_key_dbt.get_key_dbt(), &bdb_dbt_data.data_dbt, 0);
      if (ret == DB_NOTFOUND)
        errors.add("Bdb_DAO::lookup", "1", "key not found in database " + bdb_db.to_string());
      else if (ret)
        errors.add("Bdb_DAO::lookup", "2", "read error in database " + bdb_db.to_string(), ret);
      else
        bdb_dbt_data.set_data_dto(bdb_data_dto);
    }
    catch (DbException &e) {
      errors.add("Bdb_DAO::lookup",
                 "3",
                 "Error writing in database " + bdb_db.to_string() + ": " + std::string(e.what()));
    }
    catch (std::exception &e) {
      errors.add("Bdb_DAO::lookup",
                 "4",
                 "Error writing in database " + bdb_db.to_string() + ": " + std::string(e.what()));
    }
  }

  static void save(Bdb_db &bdb_db, K &bdb_key_dto, T &bdb_data_dto, Bdb_errors &errors, bool no_overwrite = false, DbTxn* txnid = nullptr) {
    Bdb_dbt<K, T, L> bdb_key_dbt{bdb_key_dto};
    Bdb_dbt<K, T, L> bdb_dbt_data{bdb_data_dto};

    try {
      int ret = bdb_db.get_db().put(txnid, &bdb_key_dbt.key_dto, &bdb_dbt_data.data_dtoa, 0);
      if (ret) {
        if (ret != DB_KEYEXIST)
          errors.add("Bdb_DAO::save", "1", "write error in database " + bdb_db.to_string(), ret);
        else if (no_overwrite)
          errors.add("Bdb_DAO::save", "2", "key exists in database " + bdb_db.to_string(), ret);
      }
    }
    catch (DbException &e) {
      errors.add("Bdb_DAO::save", "3", "Error writing in database " + bdb_db.to_string() + std::string(e.what()));
    }
    catch (std::exception &e) {
      errors.add("Bdb_DAO::save", "4", "Error writing in database " + bdb_db.to_string() + std::string(e.what()));
    }
  }
};

template<typename K, typename T, typename L>
class Bdb_DAO_list {
 public:
  static void select_all(Bdb_db &bdb_db, L &bdb_data_dto_list, Bdb_errors &errors) {
    Bdb_cursor<K, T, L> bdb_cursor(bdb_db, errors);
    if (!errors.has()) {
      K bdb_key_dto;
      for (bdb_cursor.dto_list_get_first(bdb_key_dto, bdb_data_dto_list, errors);
           !bdb_cursor.is_done();
           bdb_cursor.dto_list_get_next(bdb_key_dto, bdb_data_dto_list, errors));
    }
  }

  /**
   * select all database records starting with key
   * \param bdb_db database handle
   * \param bdb_key key for first record
   * \param bdb_data_dto_list read data DTO list
   * \param errors
   */
  static void select_all_key(Bdb_db &bdb_db, K &bdb_key_dto, L &bdb_data_dto_list, Bdb_errors &errors) {
    Bdb_cursor<K, T, L> bdb_cursor(bdb_db, errors);
    if (!errors.has()) {
      for (bdb_cursor.dto_list_get_key(bdb_key_dto, bdb_data_dto_list, errors);
           !bdb_cursor.done();
           bdb_cursor.dto_list_get_next(bdb_key_dto, bdb_data_dto_list, errors));
    }
  }
};

