cmake_minimum_required(VERSION 3.26)

include(FetchContent)

FetchContent_MakeAvailable(assimp)
FetchContent_MakeAvailable(glfw)
FetchContent_MakeAvailable(stbi)
FetchContent_MakeAvailable(json)

file(GLOB SUBDIRECTORIES "${CMAKE_SOURCE_DIR}/Strand-Engine/*")

foreach (SUBDIRECTORY ${SUBDIRECTORIES})
    if (IS_DIRECTORY ${SUBDIRECTORY})
        file(GLOB_RECURSE SRC_FILES "${SUBDIRECTORY}/*.cpp" "${SUBDIRECTORY}/*.hpp" "${SUBDIRECTORY}/*.h")
        foreach (SRC_FILE ${SRC_FILES})
            message(STATUS "Adding source file: ${SRC_FILE}")
            list(APPEND SOURCES ${SRC_FILE})
        endforeach ()
    endif ()
endforeach ()

add_library(Strand-Engine STATIC main.cpp ${SOURCES})

if (CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(Strand-Engine PUBLIC ENGINE_DEBUG)
endif ()

target_include_directories(Strand-Engine PRIVATE "${CMAKE_SOURCE_DIR}/Strand-Engine")
target_include_directories(Strand-Engine PRIVATE ${stbi_SOURCE_DIR})

target_link_libraries(Strand-Engine PRIVATE glfw)
target_link_libraries(Strand-Engine PRIVATE assimp)
target_link_libraries(Strand-Engine PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(Strand-Engine PRIVATE "d3d11.lib")
target_link_libraries(Strand-Engine PRIVATE "dxgi.lib")
target_link_libraries(Strand-Engine PRIVATE "d3dcompiler.lib")
target_link_libraries(Strand-Engine PRIVATE "dxguid.lib")


add_compile_definitions("RENDER_ROOT=${CMAKE_SOURCE_DIR}")
add_compile_definitions("SHADER_ROOT=${CMAKE_SOURCE_DIR}/Shaders")