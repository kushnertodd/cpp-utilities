add_library(bdb-lib STATIC
        bdb_dao.cpp
        bdb_db.cpp
        bdb_db.hpp
        bdb_errors.cpp
        bdb_errors.hpp
        )
target_include_directories(bdb-lib PUBLIC .)
