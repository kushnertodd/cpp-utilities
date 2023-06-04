#include <iostream>
#include <sstream>
//#include <utility>
#include "errors.hpp"

// Error methods

/**
 * adds error to error list
 * @param module
 * @param id
 * @param message
 */
Error::Error(std::string module_, std::string id_, std::string message_) :
  module(std::move(module_)), id(std::move(id_)), message(std::move(message_)) {}

std::string Error::to_string() const {
  std::ostringstream os;
  if (module.empty() && id.empty())
    os << message;
  else if (id.empty())
    os << module + ": " + message;
  else
    os << module + "[" + id + "]: " + message;
  return os.str();
}

// Errors methods

/**
 * adds error to error list
 * @param module
 * @param id
 * @param message
 */
void Errors::add(const std::string &module, const std::string &id, const std::string &message) {
  error_ct++;
  Error error(module, id, message);
  errors.push_back(error);
}

/**
 * checks if error seen
 * @return
 */
bool Errors::has() const {
  return error_ct != 0;
}

/**
 * convert to error list
 * @return
 */
std::string Errors::to_string() {
  std::ostringstream os;
  for (const Error &error: errors) {
    os << error.to_string() << std::endl;
  }
  return os.str();
}
