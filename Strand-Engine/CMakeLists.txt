cmake_minimum_required(VERSION 3.26)

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

add_library(Strand-Engine SHARED main.cpp ${SOURCES})

if (CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(Strand-Engine PRIVATE ENGINE_DEBUG)
endif ()

set(DLL_EXPORT TRUE)

if (MSVC)
    if (DLL_EXPORT)
        target_compile_definitions(Strand-Engine PRIVATE ENGINE_API=__declspec\(dllexport\))
    else ()
        target_compile_definitions(Strand-Engine PRIVATE ENGINE_API=__declspec\(dllimport\))
    endif ()
elseif (GNU)
    if (DLL_EXPORT)
        target_compile_definitions(Strand-Engine PRIVATE ENGINE_API=__attribute__\((dllexport\)))
    else ()
        target_compile_definitions(Strand-Engine PRIVATE ENGINE_API=__attribute__\((dllimport\)))
    endif ()
endif ()

if (MSVC)
    target_compile_definitions(Strand-Engine PRIVATE FORCEINLINE=__forceinline)
elseif (GNU)
    target_compile_definitions(Strand-Engine PRIVATE FORCEINLINE=__attribute__\((always_inline\)))
endif ()

target_include_directories(Strand-Engine PRIVATE "${CMAKE_SOURCE_DIR}/Strand-Engine")

target_link_libraries(Strand-Engine PRIVATE "d3d11.lib")
target_link_libraries(Strand-Engine PRIVATE "dxgi.lib")
target_link_libraries(Strand-Engine PRIVATE "d3dcompiler.lib")
target_link_libraries(Strand-Engine PRIVATE "dxguid.lib")


add_compile_definitions("RENDER_ROOT=${CMAKE_SOURCE_DIR}")
add_compile_definitions("SHADER_ROOT=${CMAKE_SOURCE_DIR}/Shaders")