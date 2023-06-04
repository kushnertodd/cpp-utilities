#include <iostream>
#include <sstream>
#include <utility>
#include "errors.hpp"

// Error methods

const std::string Error::class_name = "Error";

/**
 * adds error to error list
 * @param module
 * @param id
 * @param message
 * @param db_errno return from Berkeley DB routine, <0 = db error, >0 = error, 0 = normal
 */
Error::Error(std::string module_, std::string id_, std::string message_, int db_errno_) :
    module(std::move(module_)), id(std::move(id_)), message(std::move(message_)), db_errno(db_errno_) {}

bool Error::is_db_err() const {
  return db_errno < 0; // else is errno if > 0
}

json_object *Error::to_json() const {
  json_object *root = json_object_new_object();
  if (!root) {
    return nullptr;
  }
  json_object_object_add(root, "module", json_object_new_string(module.c_str()));
  json_object_object_add(root, "id", json_object_new_string(id.c_str()));
  json_object_object_add(root, "message", json_object_new_string(message.c_str()));
  if (db_errno)
    json_object_object_add(root, "db_errno", json_object_new_string(db_strerror(db_errno)));
  return root;
}

std::string Error::to_string() const {
  std::ostringstream os;
  if (module.empty() && id.empty())
    os << message;
  else if (id.empty())
    os << module + ": " + message;
  else
    os << module + "[" + id + "]: " + message;
  if (db_errno)
    os << " (" << db_strerror(db_errno) << ")";
  return os.str();
}

// Errors methods

const std::string Errors::class_name = "Errors";

/**
 * adds error to error list
 * @param module
 * @param id
 * @param message
 */
void Errors::add(const std::string &module, const std::string &id, const std::string &message, int db_errno) {
  error_ct++;
  Error error(module, id, message, db_errno);
  errors.push_back(error);
}

/**
 * checks for error and exits
 * @param message
 */
void Errors::check_exit(const std::string &message) {
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

json_object *Errors::to_json() {
  json_object *root = json_object_new_object();
  if (!root) {
    return nullptr;
  }
  if (!has()) {
    json_object_object_add(root, "class_name", json_object_new_string(Errors::class_name.c_str()));
    json_object *names_json = json_object_new_array();
    json_object_object_add(root, "errors", names_json);
    for (const Error &error: errors) {
      json_object *error_jobj = error.to_json();
      if (error_jobj != nullptr)
        json_object_array_add(names_json, error_jobj);
    }
  }
  if (!has()) {
    return root;
  } else {
    json_object_put(root);
    return nullptr;
  }
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
