cmake_minimum_required(VERSION 3.26)

include(FetchContent)

project("Strand-Engine")

#[[set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "Assimp build tests" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "Assimp install" FORCE)
set(ASSIMP_INSTALL_PDB OFF CACHE BOOL "Assimp install PDB" FORCE)]]


set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Strand-Engine)
add_subdirectory(Strand-Editor)
