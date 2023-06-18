add_library(bdb-lib STATIC
        #bdb_db.cpp
        #bdb_db.hpp
        bdb_db_config.cpp
        bdb_db_config.hpp
        #bdb_env_config.cpp
        #bdb_env_config.hpp
        bdb_errors.cpp
        bdb_errors.hpp
        )
target_include_directories(bdb-lib PUBLIC .)
