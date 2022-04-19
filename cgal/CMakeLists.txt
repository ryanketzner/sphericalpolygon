# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.

cmake_minimum_required(VERSION 3.1...3.22)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
project(Nef_S2_Examples)

find_package(CGAL REQUIRED)

include_directories(BEFORE "include")
include_directories(../lib/extern/gmatutil/util)
include_directories(../lib/extern/gmatutil/include)

find_library(LIBGMATUTIL gmatutil ../lib/extern/gmatutil)
find_library(LIBPOLY poly ../build)



create_single_source_cgal_program("NefPolygons.cpp")
target_link_libraries(NefPolygons PUBLIC ${LIBGMATUTIL})
target_link_libraries(NefPolygons PUBLIC ${LIBPOLY})