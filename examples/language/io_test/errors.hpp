#pragma once

#include <json-c/json.h>
#include <db_cxx.h>
#include <vector>
#include "errors.hpp"

/**
 * Error module
 * Includes calling module, message id, and message text
 */

class Error {
 public:
  static const std::string class_name;
  std::string module{};
  std::string id{};
  std::string message{};
  int db_errno{};

  Error() = default;
  Error(std::string module, std::string id, std::string message, int db_errno = 0);
  [[nodiscard]] bool is_db_err() const;
  [[nodiscard]] json_object *to_json() const;
  [[nodiscard]] std::string to_string() const;
};

class Errors {
 public:
  static const std::string class_name;
  int error_ct = 0;
  std::vector<Error> errors;

  Errors() = default;
  void add(const std::string &module, const std::string &id, const std::string &message, int db_errno = 0);
  void check_exit(const std::string &message = "");
  [[nodiscard]] bool has() const;
  json_object *to_json();
  std::string to_string();
};
