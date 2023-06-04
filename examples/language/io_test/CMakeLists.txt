cmake_minimum_required(VERSION 3.20.0)

project(fileio)

add_executable(fileio_test_read
               fileio_test_read.cpp)
add_executable(fileio_test_write
               fileio_test_write.cpp)
add_library(fileio
            fileio.cpp
            errors.cpp)

target_link_libraries(fileio_test_read PUBLIC fileio)
target_link_libraries(fileio_test_write PUBLIC fileio)

set_source_files_properties(fileio.cpp PROPERTIES COMPILE_OPTIONS "-g")
set_source_files_properties(fileio_test_read.cpp PROPERTIES COMPILE_OPTIONS "-g")
set_source_files_properties(fileio_test_write.cpp PROPERTIES COMPILE_OPTIONS "-g")


