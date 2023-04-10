cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(tokenize_test VERSION 1.0)
 
# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#  Create a variable USE_MY_TOKENIZE using option and set default to ON
option(USE_MY_TOKENIZE "Use my tokenize implementation" ON)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file(tokenize_test_config.h.in tokenize_test_config.h)

#  Use list() and APPEND to create a list of optional libraries
# called  EXTRA_LIBS and a list of optional include directories called
# EXTRA_INCLUDES. Add the StringFunctions library and source directory to
# the appropriate lists.
#
# Only call add_subdirectory and only add StringFunctions specific values
# to EXTRA_LIBS and EXTRA_INCLUDES if USE_MY_TOKENIZE is true.
#if(USE_MY_TOKENIZE)
  add_subdirectory(StringFunctions)
  list(APPEND EXTRA_LIBS StringFunctions)
  list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/StringFunctions")
#endif()

#  Use add_subdirectory() to add StringFunctions to this project
#add_subdirectory(StringFunctions)

# add the executable
add_executable(tokenize_test tokenize_test.cxx)

#  Use EXTRA_LIBS instead of the StringFunctions specific values
# in target_link_libraries.
target_link_libraries(tokenize_test PUBLIC ${EXTRA_LIBS})

#  Use target_link_libraries to link the library to our executable
#target_link_libraries(tokenize_test PUBLIC StringFunctions)

#  Add StringFunctions to tokenize_test's target_include_directories()
# Hint: ${PROJECT_SOURCE_DIR} is a path to the project source. AKA This folder!
#  Use EXTRA_INCLUDES instead of the StringFunctions specific values
# in target_include_directories.
target_include_directories(tokenize_test PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           ${EXTRA_INCLUDES}
                           )
