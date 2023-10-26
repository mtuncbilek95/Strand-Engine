cmake_minimum_required(VERSION 3.26)

include(${CMAKE_SOURCE_DIR}/Cmake/SetExportMacro.cmake)

file(GLOB_RECURSE SUBDIRECTORIES "${CMAKE_SOURCE_DIR}/Strand-Editor/*.cpp" "${CMAKE_SOURCE_DIR}/Strand-Editor/*.hpp")
source_group(TREE ${CMAKE_SOURCE_DIR}/Strand-Editor FILES ${SUBDIRECTORIES})
add_executable(Strand-Editor main.cpp ${SUBDIRECTORIES})

target_include_directories(Strand-Editor PRIVATE ${CMAKE_SOURCE_DIR}/Strand-Editor)
target_include_directories(Strand-Editor PRIVATE ${CMAKE_SOURCE_DIR}/Strand-Engine)
target_include_directories(Strand-Editor PRIVATE ${CMAKE_SOURCE_DIR}/Strand-Std/Includes)

target_link_libraries(Strand-Editor PRIVATE Strand-Engine)
target_link_libraries(Strand-Editor PRIVATE Strand-Std)

# SetExportMacro(TARGET API_NAME EXPORT=TRUE || IMPORT=FALSE)
SetExportMacro(Strand-Editor ENGINE_API FALSE)
SetExportMacro(Strand-Editor EDITOR_API TRUE)
SetExportMacro(Strand-Editor EXPORT_STRAND_STD FALSE)
