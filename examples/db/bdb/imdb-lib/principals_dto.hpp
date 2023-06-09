#pragma once

#include <json-c/json.h>
#include <list>
#include "bdb_key_extractor.hpp"
#include "bdb_errors.hpp"
#include "serializable.hpp"

/*
 * tconst     ordering  nconst     category  job  characters
 * tt0000001  1         nm1588970  self      \N   ["Self"]
 *
 * principals_DTO
 *
 * 0 title_id    tt00000011
 * 1 ordering    1
 * 1 name_id     nm1588970
 * 2 category    self
 * 3 job         \N
 * 4 characters  ["Self"]
 *
 */

class Principals_DTO { // use Imdb_DTO as pattern but do not inherit
 public:
  static const std::string class_name;
  std::string id{};
  std::string title_id{};
  std::string name_id{};
  std::string category{};
  std::string job{};
  std::string characters{};

  Principals_DTO() = default;
  Principals_DTO(const Principals_DTO &principals_) = default;
  Principals_DTO(Principals_DTO &&principals_) = default;
  Principals_DTO &operator=(const Principals_DTO &principals_) = default;
  Principals_DTO &operator=(Principals_DTO &&principals_) = default;
  explicit Principals_DTO(void *buffer);
  Principals_DTO(int count, const std::string &line, Bdb_Errors &errors, char delimiter);

  [[nodiscard]] size_t buffer_size() const;
  void *deserialize(void *buffer);
  [[nodiscard]] bool equals(const Principals_DTO &principals_DTO) const;
  void from_json(json_object *jobj, Bdb_Errors &errors);
  static int get_principals_name_id(Db *dbp, const Dbt *pkey, const Dbt *pdata, Dbt *skey);
  static int get_principals_title_id(Db *dbp, const Dbt *pkey, const Dbt *pdata, Dbt *skey);
  void parse(int count, const std::string &line, Bdb_Errors &errors, char delimiter);
  void *serialize(void *buffer) const;
  json_object *to_json(Bdb_Errors &errors) const;
  [[nodiscard]] std::string to_string() const;
};

class Principals_DTO_key {
 public:
  std::string id{};
  Principals_DTO_key() = default;
  Principals_DTO_key(const Principals_DTO_key &principals_key) = default;
  Principals_DTO_key(Principals_DTO_key &&principals_key) noexcept = default;
  explicit Principals_DTO_key(const Principals_DTO &principals_dto);
  explicit Principals_DTO_key(std::string title_id_);
  explicit Principals_DTO_key(void *buffer);
  Principals_DTO_key &operator=(const Principals_DTO_key &principals_key) = default;
  Principals_DTO_key &operator=(Principals_DTO_key &&principals_key) noexcept = default;

  [[nodiscard]] size_t buffer_size() const;
  void *deserialize(void *buffer);
  void *serialize(void *buffer) const;
  [[nodiscard]] std::string to_string() const;
};

class Principals_DTO_list {
 public:
  static const std::string class_name;
  std::list<Principals_DTO> list;
  json_object *to_json(Bdb_Errors &errors) const;
};
