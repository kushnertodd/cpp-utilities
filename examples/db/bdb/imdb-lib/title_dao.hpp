#pragma once

#include <map>
#include <vector>
#include <db_cxx.h>
#include <json-c/json.h>
#include "bdb_databases.hpp"
#include "bdb_db.hpp"
#include "bdb_errors.hpp"
#include "bdb_global.hpp"
#include "title_dto.hpp"
#include "bdb_tokens.hpp"

class Title_DAO {
 public:
  static int load(Bdb_db &title_db, const std::string &text_file, Bdb_errors &errors, char delimiter = tab);
  static void lookup(Bdb_db &title_db, const std::string &title_id, Title_DTO &title_dto, Bdb_errors &errors);
  static void save(Bdb_db &title_db, Title_DTO &title_dto, Bdb_errors &errors);
};

class Title_DAO_list {
 public:
  static void select(Bdb_db &title_db, Title_DTO_list &title_dto_list, Bdb_errors &errors);
};