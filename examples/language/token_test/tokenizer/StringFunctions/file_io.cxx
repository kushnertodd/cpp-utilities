#define __STDC_WANT_LIB_EXT1__ 1
#include <cstring>
#include <errno.h>
#include "file_io.h"

bool File_IO::open_read(std::ifstream& io_file, const std::string& file, Errors& errors) {
	io_file.open(file);
	if (io_file.bad()) {
		errors.add("File_IO::open_read", "1", file + " (" +std::to_string(errno) + ")");
		return false;
	}
	else if (io_file.fail()) {
		errors.add("File_IO::open_read", "2", file + " (" +std::to_string(errno) + ")");
		return false;
	}
	else if (io_file.eof()) {
		errors.add("File_IO::open_read", "3", file + " (" +std::to_string(errno) + ")");
		return false;
	}
	else {
		return true;
	}
}

bool File_IO::open_write(std::ofstream& io_file, const std::string& file, Errors& errors) {
	io_file.open(file);
	if (io_file.bad()) {
		errors.add("File_IO::open_write", "1", file + " (" +std::to_string(errno) + ")");
		return false;
	}
	else if (io_file.fail()) {
		errors.add("File_IO::open_write", "2", file + " (" +std::to_string(errno) + ")");
		return false;
	}
	else if (io_file.eof()) {
		errors.add("File_IO::open_write", "3", file + " (" +std::to_string(errno) + ")");
		return false;
	}
	else {
		return true;
	}
}

std::string File_IO::read_file(std::string filename, Errors& errors) {
	std::ifstream in_file;
	File_IO::open_read(in_file, filename, errors);
	if (!errors.has()) {
		std::stringstream strStream;
		// https://cplusplus.com/reference/ios/ios/rdbuf/
		strStream << in_file.rdbuf();
		return strStream.str();
	}
	else
		return "";
}
