cmake_minimum_required(VERSION 3.25)
project(Test)
target_include_directories(PRIVATE /opt/include/$<CXX_COMPILER_ID>)
