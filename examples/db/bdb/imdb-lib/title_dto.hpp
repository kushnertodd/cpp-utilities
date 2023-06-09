#pragma once

#include <json-c/json.h>
#include <list>
#include "bdb_key_extractor.hpp"
#include "bdb_errors.hpp"
#include "principals_dto.hpp"
#include "serializable.hpp"

/*
 * tconst     titleType  primaryTitle  originalTitle  isAdult  startYear  endYear  runtimeMinutes  genres
 * tt0000001  short      Carmencita    Carmencita     0        1894       \N       1               Documentary,Short
 *
 * title_DTO
 *
 * 0 title_id       tt0000001
 * 1 titleType      short
 * 2 primaryTitle   Carmencita
 * 3 originalTitle  Carmencita
 * 4 isAdult        0
 * 5 startYear      1894
 * 6 endYear        \N
 * 7 runtimeMinutes 1
 * 8 genres         Documentary,Short
 *
 */

class Title_DTO { // use Imdb_DTO as pattern but do not inherit
 public:
  static const std::string class_name;
  std::string title_id{};
  std::string titleType{};
  std::string primaryTitle{};
  std::string isAdult{};
  std::string startYear{};
  std::string runtimeMinutes{};
  std::string genres{};
  std::string averageRating{};
  std::string numVotes{};

  Title_DTO() = default;
  Title_DTO(const Title_DTO &title_) = default;
  Title_DTO(Title_DTO &&title_) = default;
  Title_DTO &operator=(const Title_DTO &title_) = default;
  Title_DTO &operator=(Title_DTO &&title_) = default;
  explicit Title_DTO(void *buffer);
  Title_DTO(int count, const std::string &line, Bdb_errors &errors, char delimiter);

  [[nodiscard]] size_t buffer_size() const;
  void *deserialize(void *buffer);
  [[nodiscard]] bool equals(const Title_DTO &title) const;
  void from_json(json_object *jobj, Bdb_errors &errors);
  static int get_title_primary_name(Db *dbp, const Dbt *pkey, const Dbt *pdata, Dbt *skey);
  void parse(int count, const std::string &line, Bdb_errors &errors, char delimiter);
  void *serialize(void *buffer) const;
  json_object *to_json(Bdb_errors &errors) const;
  [[nodiscard]] std::string to_string() const;
};

class Title_DTO_key {
 public:
  std::string title_id{};
  Title_DTO_key() = default;
  Title_DTO_key(const Title_DTO_key &title_key) = default;
  Title_DTO_key(Title_DTO_key &&title_key) noexcept = default;
  explicit Title_DTO_key(const Title_DTO &title_dto);
  explicit Title_DTO_key(const Principals_DTO &principals_dto);
  explicit Title_DTO_key(std::string title_id_);
  explicit Title_DTO_key(void *buffer);
  Title_DTO_key &operator=(const Title_DTO_key &title_key) = default;
  Title_DTO_key &operator=(Title_DTO_key &&title_key) noexcept = default;

  [[nodiscard]] size_t buffer_size() const;
  void *deserialize(void *buffer);
  void *serialize(void *buffer) const;
  [[nodiscard]] std::string to_string() const;
};

class Title_DTO_list {
 public:
  static const std::string class_name;
  std::list<Title_DTO> list;
  json_object *to_json(Bdb_errors &errors) const;
};