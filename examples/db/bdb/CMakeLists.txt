cmake_minimum_required(VERSION 3.20.0)
project(bdb-tools CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)

include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

if (PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR "In-source builds are not allowed")
endif ()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/module/")


include_directories(bdb-lib)
#include_directories(imdb-lib)
include_directories(util-lib)

include(UseDoxygenDoc)

add_subdirectory(bdb-lib)
#add_subdirectory(imdb-lib)
add_subdirectory(util-lib)

add_doxygen_doc(
        BUILD_DIR
        ${CMAKE_CURRENT_BINARY_DIR}/_build
        DOXY_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in
        TARGET_NAME
        docs
        COMMENT
        "HTML documentation"
)


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
find_package(JSON-C REQUIRED)

#https://github.com/sum01/FindBerkeleyDB
find_package(BerkeleyDB REQUIRED)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/FindBerkeleyDB")

# bdb-tools
#add_executable(bdb_tools apps/bdb_tools.cpp)
add_executable(bdb_db_config_test apps/bdb_db_config_test.cpp)
target_link_libraries(bdb_db_config_test
        PRIVATE bdb-lib util-lib
        PUBLIC Oracle::BerkeleyDB
        #PUBLIC OpenSSL::SSL
        #PUBLIC OpenSSL::Crypto
        #PUBLIC Threads::Threads
        PUBLIC ${JSON-C_LIBRARIES}
        )


#add_custom_target(${DOXY_DOC_TARGET_NAME}
#  COMMAND
#    ${DOXYGEN_EXECUTABLE} Doxyfile
#  WORKING_DIRECTORY
#    ${DOXY_DOC_BUILD_DIR}
#  COMMENT
#    "Building ${DOXY_DOC_COMMENT} with Doxygen"
#VERBATIM
#  )
#message(STATUS "Added ${DOXY_DOC_TARGET_NAME} [Doxygen] target to build documentation")
