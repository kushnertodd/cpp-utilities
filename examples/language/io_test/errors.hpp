#pragma once

#include <vector>
#include "errors.hpp"

/**
 * Error module
 * Includes calling module, message id, and message text
 */

class Error {
public:
  std::string module {};
  std::string id{};
  std::string message{};

  Error() = default;
  Error(std::string module, std::string id, std::string message);
  std::string to_string() const;
};

class Errors {
public:
  int error_ct = 0;
  std::vector<Error> errors;

  Errors() = default;
  void add(const std::string &module, const std::string &id, const std::string &message);
  bool has() const;
  std::string to_string();
};
