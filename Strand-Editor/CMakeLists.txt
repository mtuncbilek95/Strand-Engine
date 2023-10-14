cmake_minimum_required(VERSION 3.26)

include(FetchContent)

FetchContent_MakeAvailable(imgui)
FetchContent_MakeAvailable(glfw)
FetchContent_MakeAvailable(stbi)
FetchContent_MakeAvailable(json)

file(GLOB SUBDIRECTORIES "${CMAKE_SOURCE_DIR}/Strand-Editor/*")

foreach (SUBDIRECTORY ${SUBDIRECTORIES})
    if (IS_DIRECTORY ${SUBDIRECTORY})
        file(GLOB_RECURSE SRC_FILES "${SUBDIRECTORY}/*.cpp" "${SUBDIRECTORY}/*.hpp" "${SUBDIRECTORY}/*.h")
        foreach (SRC_FILE ${SRC_FILES})
            message(STATUS "Adding source file: ${SRC_FILE}")
            list(APPEND SOURCES ${SRC_FILE})
        endforeach ()
    endif ()
endforeach ()

file(GLOB IMGUI_FILES ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_dx11.cpp)

add_executable(Strand-Editor main.cpp ${SOURCES} ${IMGUI_FILES})

target_include_directories(Strand-Editor PRIVATE ${CMAKE_SOURCE_DIR}/Strand-Editor)
target_include_directories(Strand-Editor PRIVATE ${CMAKE_SOURCE_DIR}/Strand-Engine)
target_include_directories(Strand-Editor PRIVATE ${imgui_SOURCE_DIR})
target_include_directories(Strand-Editor PRIVATE ${stbi_SOURCE_DIR})

target_link_libraries(Strand-Editor PRIVATE Strand-Engine)
target_link_libraries(Strand-Editor PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(Strand-Editor PRIVATE glfw)

add_compile_definitions("RENDER_ROOT=${CMAKE_SOURCE_DIR}")
add_compile_definitions("SHADER_ROOT=${CMAKE_SOURCE_DIR}/Shaders")