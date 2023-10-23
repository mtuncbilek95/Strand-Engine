cmake_minimum_required(VERSION 3.26)

include(${CMAKE_SOURCE_DIR}/CMake/SetApi.cmake)

FetchContent_MakeAvailable(Glfw)

file(GLOB_RECURSE SUBDIRECTORIES "${CMAKE_SOURCE_DIR}/Strand-Engine/*.cpp" "${CMAKE_SOURCE_DIR}/Strand-Engine/*.hpp")
source_group(TREE ${CMAKE_SOURCE_DIR}/Strand-Engine FILES ${SUBDIRECTORIES})
add_library(Strand-Engine SHARED main.cpp ${SUBDIRECTORIES})

if (CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(Strand-Engine PRIVATE ENGINE_DEBUG)
endif ()

target_include_directories(Strand-Engine PRIVATE "${CMAKE_SOURCE_DIR}/Strand-Engine")

target_link_libraries(Strand-Engine PRIVATE glfw)
target_link_libraries(Strand-Engine PRIVATE "d3d11.lib")
target_link_libraries(Strand-Engine PRIVATE "dxgi.lib")
target_link_libraries(Strand-Engine PRIVATE "d3dcompiler.lib")
target_link_libraries(Strand-Engine PRIVATE "dxguid.lib")

# Set_Api(SubDir EngineAPICondition EditorAPICondition)
SetApi(Strand-Engine TRUE FALSE)
