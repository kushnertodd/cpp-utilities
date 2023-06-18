#pragma once

#include "bdb_databases_config.hpp"
#include "bdb_env.hpp"
#include "bdb_errors.hpp"

class Imdb_app_init {
 public:
  static std::string app_name;

  Bdb_env bdb_env;
  int cache_bytes{0};
  int cache_gbytes{4};
  std::string db_config_filename{};
  std::string db_home{};
  std::string env_home{};
  std::string etf_request_json_filename{};

  bool have_db_config_filename{false};
  bool have_db_home{false};
  bool have_env_home{false};
  bool have_etf_request_json_filename{false};

  Imdb_app_init(int argc,
                const char **argv,
                Bdb_databases_config &bdb_databases_config,
                Bdb_Errors &errors);

  void init(Bdb_databases_config &bdb_databases_config,
            Bdb_Errors &errors);
  static void usage(const std::string &message = "");
};

