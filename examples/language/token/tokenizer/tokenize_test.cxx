/*
  test manual tokenizer vs stl version

  my tokenizer
  cpu msecs/rec        0.0028257
  wall clock msecs/rec 0.0045069


  stl tokenizer
  cpu msecs/rec        0.0016566
  wall clock msecs/rec 0.0035960
*/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "file_io.h"
#include "errors.h"
#include "tokenize_test_config.h"
#include "timer.h"

//  Only include tokens.h if USE_MY_TOKENIZE is defined
//#ifdef USE_MY_TOKENIZE
#include "tokens.h"
//#endif

void print_token_list(int count, std::string line, std::vector<std::string>& token_list) {
	std::cout << Tokens::line_print(count, line) << std::endl;
	for (std::string token : token_list) {
		std::cout << token << "<tab>";
	}
	std::cout << "<nl>" << std::endl;
}

int main(int argc, char* argv[])
{
	if (argc < 3) {
		// report version
		std::cout << argv[0] << " Version " << tokenize_test_VERSION_MAJOR << "."
			<< tokenize_test_VERSION_MINOR << std::endl;
		std::cout << "Usage: " << argv[0] << " file count [print] " << std::endl;
		return 1;
	}

	// convert input to double
	const std::string filename(argv[1]);
	int max_count = std::stod(argv[2]);
	bool do_print = 0;
	if (argc > 3)
		do_print = std::stod(argv[3]);

#ifdef USE_MY_TOKENIZE
	std::cout << "my tokenizer" << std::endl;
#else
	std::cout << "stl tokenizer" << std::endl;
#endif
	Errors errors;
	std::ifstream in_file;
	if (File_IO::open_read(in_file, filename, errors)) {
		std::string line;
		int count;
		Timer timer;
		for (count = 0;
			std::getline(in_file, line) && count < max_count;
			count++) {
			//  Use my_tokenize() if USE_MY_TOKENIZE is defined and sqrt otherwise
#ifdef USE_MY_TOKENIZE
			std::vector<std::string> tokens = my_tokenize(line, '\t');
#else
			std::vector<std::string> tokens = stl_tokenize(line, '\t');
#endif
			if (do_print) {
				print_token_list(count, line, tokens);
			}
		}
		// cpu seconds to execute
		double cpu_seconds = timer.cpu_seconds_used();
		// wall clock milliseconds to execute
		double wall_clock_milliseconds = timer.wall_clock_milliseconds_used();
		std::cout << "cpu msecs/rec        " << std::setprecision(7) << std::fixed << cpu_seconds * 1000.0/count << std::endl;
		std::cout << "wall clock msecs/rec " << std::setprecision(7) << std::fixed << wall_clock_milliseconds / count << std::endl;
	}
	if (errors.has()) {
		std::cout << errors.to_string() << std::endl;
		return 1;
	}
	else
		return 0;
}
