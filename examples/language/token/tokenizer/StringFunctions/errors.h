#pragma once

#include <vector>

/**
 * Error module
 * Includes calling module, message id, and message text
 */

class Error {
public:
	std::string module;
	std::string id;
	std::string message;
	int sys_errno;
	Error() = default;
	Error(const std::string& module, const std::string& id, const std::string& message, int sys_errno = 0);
	std::string to_string();
};
class Errors {
public:
	static const std::string class_name;
	int error_ct = 0;
	std::vector<Error> errors;

	Errors() = default;
	void add(const std::string& module, const std::string& id, const std::string& message, int sys_errno = 0);
	void check_exit(const std::string& message = "");
	bool has() const;
	std::string to_string();
};
