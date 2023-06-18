cmake_minimum_required(VERSION 3.20.0)
project(bdb-tools CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)

if (PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR "In-source builds are not allowed")
endif ()

#list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/module/")


include_directories(bdb-lib)
#include_directories(imdb-lib)
include_directories(util-lib)

add_subdirectory(bdb-lib)
#add_subdirectory(imdb-lib)
add_subdirectory(util-lib)

## link libs

#find_package(oatpp 1.3.0 REQUIRED)

#set(THREADS_PREFER_PTHREAD_FLAG ON)
#find_package(Threads REQUIRED)
#message("FOUND: ${Threads}")

# OpenSSL::SSL
# https://cmake.org/cmake/help/v3.6/module/FindOpenSSL.html
#set(OPENSSL_USE_STATIC_LIBS TRUE)
#find_package(OpenSSL REQUIRED)

# https://github.com/cloudshark/cshark/blob/master/build/modules/FindJSON-C.cmake
#find_package(JSON-C REQUIRED)

#https://github.com/sum01/FindBerkeleyDB
find_package(BerkeleyDB REQUIRED)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/FindBerkeleyDB")

# bdb-tools
#add_executable(bdb_tools apps/bdb_tools.cpp)
add_executable(bdb_db_config_test apps/bdb_db_config_test.cpp)
target_link_libraries(bdb_db_config_test
        PRIVATE bdb-lib util-lib
        PUBLIC Oracle::BerkeleyDB
        #PUBLIC ${JSON-C_LIBRARIES}
        #PUBLIC OpenSSL::SSL
        #PUBLIC OpenSSL::Crypto
        #PUBLIC Threads::Threads
        )

#include(Doxygen)
#Doxygen(src docs)
