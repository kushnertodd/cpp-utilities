add_library(imdb-lib STATIC
        imdb_app_init.cpp
        imdb_app_init.hpp
        imdb_bdb_keys.cpp
        imdb_bdb_keys.hpp
        imdb_dao.hpp
        imdb_dto.hpp
        imdb_request.cpp
        imdb_request.hpp
        name_dao.cpp
        name_dao.hpp
        name_dto.cpp
        name_dto.hpp
        principals_dao.cpp
        principals_dao.hpp
        principals_dto.cpp
        principals_dto.hpp
        ratings_dao.cpp
        ratings_dao.hpp
        ratings_dto.cpp
        ratings_dto.hpp
        title_dao.cpp
        title_dao.hpp
        title_dto.cpp
        title_dto.hpp
        title_tripthongs_dao.cpp
        title_tripthongs_dao.hpp
        title_tripthongs_dto.cpp
        title_tripthongs_dto.hpp
        )
target_include_directories(imdb-lib PUBLIC .)
