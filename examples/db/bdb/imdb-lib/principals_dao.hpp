#pragma once

#include <map>
#include <vector>
#include <db_cxx.h>
#include <json-c/json.h>
#include "bdb_databases.hpp"
#include "bdb_db.hpp"
#include "bdb_errors.hpp"
#include "principals_dto.hpp"
#include "title_dto.hpp"
#include "bdb_tokens.hpp"

class Principals_DAO {
 public:
  static int load(Bdb_db &principals_db, const std::string &text_file, Bdb_Errors &errors, char delimiter = tab);
  static void lookup(Bdb_db &principals_db,
                     const std::string &principals_id,
                     Principals_DTO &principals_dto,
                     Bdb_Errors &errors);
  static void save(Bdb_db &principals_db, Principals_DTO &principals_dto, Bdb_Errors &errors);
};

class Principals_DAO_list {
 public:
  static void select(Bdb_db &principals_db, Principals_DTO_list &principals_dto_list, Bdb_Errors &errors);
  static void search_by_name(Bdb_db &title_db,
                             Bdb_db &principals_db,
                             Bdb_db &principals_name_id_sdb,
                             const std::string &name_id,
                             Title_DTO_list &title_dto_list,
                             Bdb_Errors &errors);
  static void search_by_title(Bdb_db &name_db,
                              Bdb_db &principals_db,
                              Bdb_db &principals_title_id_sdb,
                              const std::string &title_id,
                              Name_DTO_list &name_dto_list,
                              Bdb_Errors &errors);
};