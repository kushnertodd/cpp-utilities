#include <json-c/json.h>
#include "bdb_databases_config.hpp"
#include "bdb_errors.hpp"
#include "bdb_global.hpp"
#include "misc_utils.hpp"
#include "imdb_app_init.hpp"

std::string Imdb_app_init::app_name{"etf_app"};

Imdb_app_init::Imdb_app_init(int argc,
                             const char **argv,
                             Bdb_databases_config &bdb_databases_config,
                             Bdb_errors &errors) {
  // https://man7.org/linux/man-pages/man3/getopt.3.html
  int ch;
  while ((ch = getopt(argc, (char **) argv, ":b:d:e:f:g:h:z")) != EOF)
    switch (ch) {
      case 'b': {
        cache_bytes = Misc_utils::string_to_int(optarg, errors);
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
          etf_request_json_filename = optarg;
          have_etf_request_json_filename = true;
        }
        break;
      }
      case 'g': {
        cache_gbytes = Misc_utils::string_to_int(optarg, errors);
        break;
      }
      case 'h': {
        if (optarg != nullptr) {
          db_home = optarg;
          have_db_home = true;
        }
        break;
      }
      case 'z': {
        Bdb_global::debug = true;
        break;
      }
      case ':':
        errors.add("Imdb_app_init::Imdb_app_init",
                   "1",
                   "Option -" + Misc_utils::char_to_string((char) ch) + " requires an argument");
        break;
      case '?':
        errors.add("Imdb_app_init::Imdb_app_init", "1", "Invalid option -" + Misc_utils::char_to_string((char) ch));
        break;
      default: {
        errors.add("Imdb_app_init::init", "1", "Invalid option '-" + Misc_utils::char_to_string((char) ch));
      }
    }
  if (!have_db_config_filename)
    errors.add("Imdb_app_init::init", "2", "-d required");
  if (!have_env_home)
    errors.add("Imdb_app_init::init", "3", "-e required");
  if (!have_db_home)
    errors.add("Imdb_app_init::init", "5", "-h required");
  if (!have_etf_request_json_filename)
    errors.add("Imdb_app_init::init", "3", "-t required");
  if (!errors.has())
    init(bdb_databases_config, errors);
  else
    usage(errors.to_string());
}

// https://cpp.hotexamples.com/examples/-/DbEnv/-/cpp-dbenv-class-examples.html
void Imdb_app_init::init(Bdb_databases_config &bdb_databases_config,
                         Bdb_errors &errors) {
  std::string error_file = env_home + "/" + app_name + ".log";
  bdb_env.init(db_home, cache_gbytes, cache_bytes, error_file, errors);
  if (!errors.has())
    bdb_env.open(env_home, errors);
  json_object *bdb_json{};
  if (!errors.has())
    bdb_json = json_object_from_file(db_config_filename.c_str());
  if (bdb_json != nullptr)
    bdb_databases_config.from_json(bdb_json, errors);
  else
    errors.add("Imdb_app_init::init", "1", "invalid json file " + db_config_filename);
}

void Imdb_app_init::usage(const std::string &message) {
  std::cout << (message.empty() ? app_name + " usage: " : message) << std::endl
            << " -b <cache bytes> (default: 0)" << std::endl
            << " -d <request db config json file>" << std::endl
            << " -e <environment home directory>" << std::endl
            << " -g <cache gbytes> (default: 4)" << std::endl
            << " -h <database home directory>" << std::endl
            << " -r <etf json request file>" << std::endl
            << " -z (debug on)" << std::endl
            << std::endl;
}
