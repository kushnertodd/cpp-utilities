#include <iostream>
#include <sstream>
#include <cstring>
#include "errors.h"

const std::string Errors::class_name = "Errors";

// Error methods

/**
 * adds error to error list
 * @param module
 * @param id
 * @param message
 * @param sys_errno return from Berkeley DB routine, <0 = db error, >0 = error, 0 = normal
 */
Error::Error(const std::string& module_, const std::string& id_, const std::string& message_, int sys_errno_) :
  module(module_), id(id_), message(message_), sys_errno(sys_errno_)
{}

std::string Error::to_string() {
  std::ostringstream os;
  if (module.empty() && id.empty())
    os << message;
  else if (id.empty())
    os << module + ": " + message;
  else
    os << module + "[" + id + "]: " + message;
  if (sys_errno) {
    os << " (" << sys_errno << ")";
  }
  return os.str();
}

// Errors methods

/**
 * adds error to error list
 * @param module
 * @param id
 * @param message
 */
void Errors::add(const std::string& module, const std::string& id, const std::string& message, int sys_errno) {
  error_ct++;
  Error error(module, id, message, sys_errno);
  errors.push_back(error);
}

/**
 * checks for error and exits
 * @param message
 */
void Errors::check_exit(const std::string& message) {
  if (error_ct > 0) {
    if (!message.empty())
      std::cerr << message << std::endl;
    std::cerr << to_string() << std::endl;
    exit(1);
  }
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
  for (Error error : errors) {
    os << error.to_string() << std::endl;
  }
  return os.str();
}
