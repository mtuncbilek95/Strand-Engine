cmake_minimum_required (VERSION 3.26)

include(FetchContent)

# GLFW Library
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.3.9
)

# STBI Library
FetchContent_Declare(
        stbi
        GIT_REPOSITORY https://github.com/nothings/stb.git
)

# JSON Library
FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
)

# GLM Library
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG master
)