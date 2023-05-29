//
// Created by kushn on 5/3/2023.
//

#include <json-c/json.h>
#include "bdb_databases.hpp"
#include "bdb_env.hpp"
#include "errors.hpp"
#include "file_io.hpp"
#include "misc_utils.hpp"
#include "bdb_init.hpp"

Bdb_init::Bdb_init(int argc,
                   const char **argv,
                   Errors &errors,
                   int required_arguments) :
    required_etf_historical_data_filename(required_arguments & Bdb_init::Required_arguments::ETF_HISTORICAL_DATA),
    required_imdb_request_json_filename(required_arguments & Bdb_init::Required_arguments::IMDB_REQUEST) {

  std::string current_directory = File_IO::get_current_directory();

  // https://man7.org/linux/man-pages/man3/getopt.3.html
  int ch;
  while ((ch = getopt(argc, (char **) argv, "b:d:e:f:g:h:t:")) != EOF)
    switch (ch) {
      case 'b': {
        cache_bytes = Misc_utils::str_to_int(optarg, errors);
        break;
      }
      case 'd': {
        if (optarg != nullptr) {
          db_config_filename = optarg;
          have_db_config_filename = true;
        }
        break;
      }
      case 'e': {
        if (optarg != nullptr) {
          env_home = optarg;
          have_env_home = true;
        }
        break;
      }
      case 'f': {
        if (optarg != nullptr) {
          imdb_request_json_filename = optarg;
          have_imdb_request_json_filename = true;
        }
        break;
      }
      case 'g': {
        cache_gbytes = Misc_utils::str_to_int(optarg, errors);
        break;
      }
      case 'h': {
        if (optarg != nullptr) {
          db_home = optarg;
          have_db_home = true;
        }
        break;
      }
      case 't': {
        if (optarg != nullptr) {
          etf_historical_data_filename = optarg;
          have_etf_historical_data_filename = true;
        }
        break;
      }
      case '?':
      default: {
        const char c = (char) optopt;
        errors.add("Bdb_init::init", "1", "invalid option -" + std::string(1, c));
      }
    }
  if (!have_db_config_filename)
    errors.add("Bdb_init::init", "2", "-d required");
  if (!have_db_home)
    errors.add("Bdb_init::init", "5", "-h required");
  if (!have_env_home)
    errors.add("Bdb_init::init", "3", "-e required");
  if (!have_etf_historical_data_filename && required_etf_historical_data_filename)
    errors.add("Bdb_init::init", "3", "-t required");
  if (!have_imdb_request_json_filename && required_imdb_request_json_filename)
    errors.add("Bdb_init::init", "4", "-f required");
  if (!errors.has())
    initDbenv(env_home, db_home, cache_gbytes, cache_bytes, errors);
}

void Bdb_init::closeDbEnv(Errors &errors) {
  Bdb_env::close(errors);
}

// https://cpp.hotexamples.com/examples/-/DbEnv/-/cpp-dbenv-class-examples.html
void Bdb_init::initDbenv(const std::string &env_home,
                         const std::string &db_home,
                         int cache_gbytes,
                         int cache_bytes,
                         Errors &errors) {
  Bdb_env::init(db_home, cache_gbytes, cache_bytes);
  Bdb_env::set_error_log(env_home + "/bdb_lookup.log", errors);
  if (!errors.has())
    Bdb_env::open(env_home, errors);
}

void Bdb_init::usage(const std::string &message) {
  std::cout << (message == "" ? app_name + " usage: " : message) << std::endl
            << " -b <cache bytes> (default: 0)" << std::endl
            << " -d <request db config json file> (required)" << std::endl
            << " -e <environment home directory> (required)" << std::endl
            << (required_imdb_request_json_filename ? " -f <request json file>" : "") << std::endl
            << " -g <cache gbytes> (default: 4)" << std::endl
            << " -h <database home directory> (required)" << std::endl
            << (required_etf_historical_data_filename ? " -t <etf historical data file>" : "") << std::endl
            << std::endl;
}
