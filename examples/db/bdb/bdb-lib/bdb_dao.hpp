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

template<typename T, typename K>
class Bdb_DAO {
 public:
  static int load(Bdb_db &bdb_db, const std::string &text_file, Bdb_errors &errors, char delimiter = tab) {
    int count{};
    Bdb_File_IO_text_read fread(text_file, errors);
    if (!errors.has()) {
      std::string line;
      for (count = 0; fread.getline(line, errors) && !errors.has(); count++) {
        Bdb_file_IO::progress(count);
        if (count > 0) {
          T dto(count, line, errors, delimiter);
          save(bdb_db, dto, errors);
        }
      }
    }
    return count;
  }

  static void lookup(Bdb_db &bdb_db, K &bdb_key, T &bdb_dto, Bdb_errors &errors) {
    size_t key_len = bdb_key.buffer_size();
    void *key_buf = std::malloc(key_len);
    std::memset(key_buf, '\0', key_len);
    bdb_key.serialize(key_buf);

    Dbt key(key_buf, (u_int32_t) key_len);
    Dbt data;
    try {
      int ret = bdb_db.get_db().get(nullptr, &key, &data, 0);
      if (ret == DB_NOTFOUND)
        errors.add("Bdb_DAO::lookup", "1", "key not found");
      else if (ret)
        errors.add("Bdb_DAO::lookup", "2", "read error", ret);
      else
        bdb_dto.deserialize(data.get_data());
    }
    catch (DbException &e) {
      errors.add("Bdb_DAO::lookup", "3", "Error writing file " + std::string(e.what()));
    }
    catch (std::exception &e) {
      errors.add("Bdb_DAO::lookup", "4", "Error writing file " + std::string(e.what()));
    }
    free(key_buf);
  }

  static void save(Bdb_db &bdb_db, K &bdb_key, T &bdb_dto, Bdb_errors &errors, bool no_overwrite = false) {
    size_t key_len = bdb_key.buffer_size();
    void *key_buf = std::malloc(key_len);
    std::memset(key_buf, '\0', key_len);
    bdb_key.serialize(key_buf);

    size_t buffer_len = bdb_dto.buffer_size();
    void *buffer = std::malloc(buffer_len);
    std::memset(buffer, '\0', buffer_len);
    bdb_dto.serialize(buffer);

    Dbt key(key_buf, (u_int32_t) key_len);
    Dbt data(buffer, (u_int32_t) buffer_len);

    try {
      int ret = bdb_db.get_db().put(nullptr, &key, &data, 0);
      if (ret) {
        if (ret == DB_KEYEXIST && no_overwrite)
          errors.add("Bdb_DAO::save", "1", "key exists", ret);
        else errors.add("Bdb_DAO::save", "1", "write error", ret);
      }
    }
    catch (DbException &e) {
      errors.add("Bdb_DAO::save", "3", "Error writing file " + std::string(e.what()));
    }
    catch (std::exception &e) {
      errors.add("Bdb_DAO::save", "4", "Error writing file " + std::string(e.what()));
    }
    free(key_buf);
    free(buffer);
  }
};

template<typename K, typename L>
class Bdb_DAO_list {
 public:
  static void select_all(Bdb_db &bdb_db, L &bdb_dto_list, Bdb_errors &errors) {
    Bdb_cursor bdb_cursor(bdb_db, errors);
    if (!errors.has()) {
      K bdb_key;
      L bdb_dto_list;
      for (bdb_cursor.dto_list_get_first(bdb_key, bdb_dto_list, errors);
           !bdb_cursor.done();
           bdb_cursor.dto_list_get_next(bdb_key, bdb_dto_list, errors));
    }
  }
  static void select_all_key(Bdb_db &bdb_db, K &bdb_key, L &bdb_dto_list, Bdb_errors &errors) {
    Bdb_cursor bdb_cursor(bdb_db, errors);
    if (!errors.has()) {
      for (bdb_cursor.dto_list_get_key(bdb_key, bdb_dto_list, errors);
           !bdb_cursor.done();
           bdb_cursor.dto_list_get_next(bdb_key, bdb_dto_list, errors));
    }
  }
};

