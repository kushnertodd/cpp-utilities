#pragma once

#include <fstream>      // std::ifstream
#include <iostream>
#include <sstream>

#include "errors.h"

// ios::exceptions
// https://cplusplus.com/reference/ios/ios/exceptions/
// https://cplusplus.com/doc/tutorial/files/
// https://www.tutorialspoint.com/cplusplus/cpp_files_streams.htm
class File_IO {
public:
	static bool open_read(std::ifstream& ifs, const std::string& file, Errors& errors);
	static bool open_write(std::ofstream& ifs, const std::string& file, Errors& errors);
	static std::string read_file(std::string filename, Errors& errors);
};
