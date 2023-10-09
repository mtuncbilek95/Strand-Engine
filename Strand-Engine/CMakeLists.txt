cmake_minimum_required(VERSION 3.26)

include(FetchContent)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.3.8)

FetchContent_Declare(
        stbi
        GIT_REPOSITORY https://github.com/nothings/stb.git
)

FetchContent_Declare(
        assimp
        GIT_REPOSITORY https://github.com/assimp/assimp.git
)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "Assimp build tests" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "Assimp install" FORCE)
set(ASSIMP_INSTALL_PDB OFF CACHE BOOL "Assimp install PDB" FORCE)

FetchContent_MakeAvailable(assimp)
FetchContent_MakeAvailable(glfw)
FetchContent_MakeAvailable(stbi)

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

add_executable(${PROJECT_NAME} main.cpp ${SOURCES})

if (CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(${PROJECT_NAME} PUBLIC ENGINE_DEBUG)
endif ()

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/Strand-Engine")
target_include_directories(${PROJECT_NAME} PUBLIC ${stbi_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} assimp)
target_link_libraries(${PROJECT_NAME} "d3d11.lib")
target_link_libraries(${PROJECT_NAME} "dxgi.lib")
target_link_libraries(${PROJECT_NAME} "d3dcompiler.lib")

add_compile_definitions("RENDER_ROOT=${CMAKE_SOURCE_DIR}")
add_compile_definitions("SHADER_ROOT=${CMAKE_SOURCE_DIR}/Shaders")