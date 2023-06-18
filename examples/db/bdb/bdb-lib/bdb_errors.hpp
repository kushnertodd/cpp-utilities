#pragma once

#include <db_cxx.h>
#include <json-c/json.h>
#include <vector>
#include "bdb_errors.hpp"

/**
 * Error module
 * Includes calling module, message id, and message text
 */
class Bdb_error {
 public:
  static const std::string class_name;
  std::string module{};
  std::string id{};
  std::string message{};
  int db_errno{};

  Bdb_error() = default;
  Bdb_error(std::string module_, std::string id_, std::string message_, int db_errno_ = 0);
  [[nodiscard]] bool is_db_err() const;
  [[nodiscard]] json_object *to_json() const;
  [[nodiscard]] std::string to_string() const;
};

class Bdb_Errors {
 public:
  static const std::string class_name;
  int error_ct = 0;
  std::vector<Bdb_error> errors;

  Bdb_Errors() = default;
  void add(const std::string &module, const std::string &id, const std::string &message, int db_errno = 0);
  void check_exit(const std::string &message = "");
  [[nodiscard]] bool has() const;
  json_object *to_json();
  std::string to_string();
};
