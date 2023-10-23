cmake_minimum_required(VERSION 3.26)

project("Strand-Engine")

set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_CURRENT_SOURCE_DIR}/CMake/FetchLibraries.cmake)

add_subdirectory(Strand-Engine)
add_subdirectory(Strand-Editor)
