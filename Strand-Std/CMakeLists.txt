cmake_minimum_required(VERSION 3.26)

include(${CMAKE_SOURCE_DIR}/Strand-Std/CMake/StdExport.cmake)

file(GLOB_RECURSE SUBDIRECTORIES "${CMAKE_SOURCE_DIR}/Strand-Std/*.cpp" "${CMAKE_SOURCE_DIR}/Strand-Std/*.hpp")
source_group(TREE ${CMAKE_SOURCE_DIR}/Strand-Std FILES ${SUBDIRECTORIES})
add_library(Strand-Std SHARED main.cpp ${SUBDIRECTORIES})

target_include_directories(Strand-Std PUBLIC ${CMAKE_SOURCE_DIR}/Strand-Std/Includes)

SetTargetMacroStd(Strand-Std)