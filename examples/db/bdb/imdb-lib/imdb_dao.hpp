#pragma once

#include <cstring>
#include <db_cxx.h>
#include <json-c/json.h>
#include <sstream>
#include <vector>
#include "bdb_databases.hpp"
#include "bdb_db.hpp"
#include "bdb_errors.hpp"
#include "bdb_file_io.hpp"
#include "bdb_global.hpp"
#include "bdb_json_utils.hpp"
#include "name_dao.hpp"
#include "principals_dto.hpp"
#include "serialization.hpp"
#include "bdb_tokens.hpp"

enum class Imdb_DAO_function { read, write };

template<typename T, typename K>
class Imdb_DAO {
 public:
  static int load(Bdb_db &imdb_db, const std::string &text_file, Bdb_errors &errors, char delimiter = tab) {
    int count{};
    Bdb_File_IO_text_read fread(text_file, errors);
    if (!errors.has()) {
      std::string line;
      for (count = 0; fread.getline(line, errors) && !errors.has(); count++) {
        Bdb_file_IO::progress(count);
        if (count > 0) {
          T dto(count, line, errors, delimiter);
          save(imdb_db, dto, errors);
        }
      }
    }
    return count;
  }

  static void lookup(Bdb_db &imdb_db, T &imdb_dto, K &imdb_key, Bdb_errors &errors) {
    void *key_buf;
    try {
      size_t key_len = imdb_key.buffer_size();
      key_buf = std::malloc(key_len);
      std::memset(key_buf, '\0', key_len);
      imdb_key.serialize(key_buf);

      Dbt key(key_buf, (u_int32_t) key_len);
      Dbt data;
      int ret = imdb_db.get_db().get(nullptr, &key, &data, 0);
      if (ret == DB_NOTFOUND)
        errors.add("Imdb_DAO::lookup", "1", "key not found");
      else if (ret)
        errors.add("Imdb_DAO::lookup", "2", "read error", ret);
      else
        imdb_dto.deserialize(data.get_data());
    }
    catch (DbException &e) {
      errors.add("Imdb_DAO::lookup", "3", "Error writing file " + std::string(e.what()));
    }
    catch (std::exception &e) {
      errors.add("Imdb_DAO::lookup", "4", "Error writing file " + std::string(e.what()));
    }
    free(key_buf);
  }

  static void save(Bdb_db &imdb_db, T &imdb_dto, Bdb_errors &errors) {
    void *key_buf;
    void *buffer;
    try {
      K imdb_key(imdb_dto);
      size_t key_len = imdb_key.buffer_size();
      key_buf = std::malloc(key_len);
      std::memset(key_buf, '\0', key_len);
      imdb_key.serialize(key_buf);

      size_t buffer_len = imdb_dto.buffer_size();
      buffer = std::malloc(buffer_len);
      std::memset(buffer, '\0', buffer_len);
      imdb_dto.serialize(buffer);

      Dbt key(key_buf, (u_int32_t) key_len);
      Dbt data(buffer, (u_int32_t) buffer_len);

      int ret = imdb_db.get_db().put(nullptr, &key, &data, 0);
      if (ret && ret != DB_KEYEXIST)
        errors.add("Imdb_DAO::save", "1", "write error", ret);
      else if (ret)
        ret = ret + 0;
    }
    catch (DbException &e) {
      errors.add("Imdb_DAO::save", "3", "Error writing file " + std::string(e.what()));
    }
    catch (std::exception &e) {
      errors.add("Imdb_DAO::save", "4", "Error writing file " + std::string(e.what()));
    }
    free(key_buf);
    free(buffer);
  }
};

template<typename K, typename L>
class Imdb_DAO_list {
 public:
  static void select(Bdb_db &imdb_db, L &imdb_dto_list, Bdb_errors &errors) {
    Dbc *cursorp;

    try {
      int ret = imdb_db.get_db().cursor(nullptr, &cursorp, 0);
      if (ret)
        errors.add("Imdb_DAO::select", "1", "error creating cursor", ret);
      else {
        // Position the cursor to the first record in the secondary database that has the appropriate key.
        Dbt data;
        Dbt key;
        for (ret = cursorp->get(&key, &data, DB_FIRST);
             !ret && !errors.has();
             ret = cursorp->get(&key, &data, DB_NEXT)) {
          imdb_dto_list.list.emplace_back(data.get_data());
        }
        if (ret && ret != DB_NOTFOUND) {
          errors.add("Imdb_DAO::select", "2", " select error", ret);
        }
        cursorp->close();
      }
    }
    catch (DbException &e) {
      errors.add("Imdb_DAO::select", "3", " error: " + std::string(e.what()));
    }
    catch (std::exception &e) {
      errors.add("Imdb_DAO::select", "4", " error: " + std::string(e.what()));
    }
  }
};

template<
    typename K,
    typename R,
    typename S,
    typename L>
class Imdb_DAO_search {
 public:
  static void search(Bdb_db &imdb_db,
                     Bdb_db &principals_db,
                     Bdb_db &imdb_sdb,
                     K &imdb_key,
                     L &imdb_dto_list,
                     Bdb_errors &errors) {
    Dbc *cursorp;
    void *key_buf;
    try {
      int ret = imdb_sdb.get_db().cursor(nullptr, &cursorp, 0);
      if (ret)
        errors.add("Imdbs::select_all_by_datetime", "1", "error creating cursor", ret);
      if (!errors.has()) {
        // Position the cursor to the first record in the secondary database that has the appropriate key.
        size_t key_len = imdb_key.buffer_size();
        key_buf = std::malloc(key_len);
        std::memset(key_buf, '\0', key_len);
        imdb_key.serialize(key_buf);

        Dbt key(key_buf, (u_int32_t) key_len);
        Dbt data;
        for (ret = cursorp->get(&key, &data, DB_SET);
             !ret && !errors.has();
             ret = cursorp->get(&key, &data, DB_NEXT_DUP)) {
          Principals_DTO principals_lookup_dto;
          Principals_DTO_key principals_lookup_key(data.get_data());
          Imdb_DAO<Principals_DTO, Principals_DTO_key>::lookup(principals_db,
                                                               principals_lookup_dto,
                                                               principals_lookup_key,
                                                               errors);
          if (!errors.has()) {
            R imdb_lookup_dto;
            S imdb_lookup_key(principals_lookup_dto);
            Imdb_DAO<R, S>::lookup(imdb_db,
                                   imdb_lookup_dto,
                                   imdb_lookup_key,
                                   errors);
            if (!errors.has())
              imdb_dto_list.list.emplace_back(imdb_lookup_dto);
          }
        }
        if (ret && ret != DB_NOTFOUND) {
          errors.add("Imdb_DAO<T, K>::search", "2", imdb_key.to_string() + " search error: ", ret);
        }
        cursorp->close();
      }
    }
    catch (DbException &e) {
      errors.add("Imdb_DAO<T, K>::search", "3", imdb_key.to_string() + " search error: " + std::string(e.what()));
    }
    catch (std::exception &e) {
      errors.add("Imdb_DAO<T, K>::search", "4", imdb_key.to_string() + " search error: " + std::string(e.what()));
    }
    free(key_buf);
  }
};
