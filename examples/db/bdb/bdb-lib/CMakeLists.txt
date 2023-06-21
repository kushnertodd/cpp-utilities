add_library(bdb-lib STATIC
        bdb_cursor.hpp
        bdb_dao.hpp
        bdb_db.cpp
        bdb_db.hpp
        bdb_errors.cpp
        bdb_errors.hpp
        bdb_file_io.cpp
        bdb_file_io.hpp
        )
target_include_directories(bdb-lib PUBLIC .)
