cmake_minimum_required(VERSION 3.26)

include(FetchContent)

FetchContent_MakeAvailable(imgui)

file(GLOB IMGUI_FILES ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_dx11.cpp)

add_library(imgui-source STATIC ${IMGUI_FILES})