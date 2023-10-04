cmake_minimum_required(VERSION 3.26)

include(FetchContent)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw
        GIT_TAG 3.3.8)

FetchContent_Declare(
        stbi
        GIT_REPOSITORY https://github.com/nothings/stb
)

FetchContent_MakeAvailable(glfw)
FetchContent_MakeAvailable(stbi)

add_executable(${PROJECT_NAME} main.cpp
        Window/Window.cpp Window/Window.hpp
        Common/Common.hpp Common/Log.hpp
        Graphics/Command/CommandList.hpp Graphics/Command/CommandList.cpp
        Graphics/Framebuffer/FramebufferDesc.hpp Graphics/Framebuffer/Framebuffer.hpp Graphics/Framebuffer/Framebuffer.cpp
        Graphics/GraphicsDevice/GraphicsDevice.hpp Graphics/GraphicsDevice/GraphicsDevice.cpp
        Graphics/GraphicsDevice/DeviceObject.hpp Graphics/GraphicsDevice/DeviceObject.cpp Graphics/GraphicsDevice/DeviceObjectDesc.hpp
        Graphics/Swapchain/Swapchain.hpp Graphics/Swapchain/Swapchain.cpp Graphics/Swapchain/SwapchainDesc.hpp
        Graphics/Pipeline/Pipeline.hpp
        Graphics/Pipeline/Pipeline.cpp
        Graphics/Resources/GraphicsTextureView/GraphicsTextureView.cpp
        Graphics/Resources/GraphicsTextureView/GraphicsTextureView.hpp
        Graphics/Resources/GraphicsTextureView/GraphicsTextureViewDesc.hpp
        Graphics/Resources/ResourceUtils.hpp
        Graphics/Utils/DxgiUtils.hpp
        Graphics/Shader/Shader.cpp
        Graphics/Shader/Shader.hpp
        Graphics/Shader/ShaderDesc.hpp
        FileReader/FileReader.hpp
        Graphics/Pipeline/PipelineDesc.hpp
        Graphics/Pipeline/InputLayout/InputLayout.hpp
        Graphics/Pipeline/DepthStencil/DepthStencil.hpp
        Graphics/Pipeline/Blend/Blend.hpp
        Graphics/Pipeline/Rasterizer/Rasterizer.hpp
        Graphics/Resources/GraphicsBuffer/GraphicsBuffer.cpp
        Graphics/Resources/GraphicsBuffer/GraphicsBuffer.hpp
        Graphics/Resources/GraphicsBuffer/GraphicsBufferDesc.hpp
        Graphics/Resources/SamplerState/SamplerState.cpp
        Graphics/Resources/SamplerState/SamplerState.hpp
        Graphics/Resources/SamplerState/SamplerStateDesc.hpp
)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(${PROJECT_NAME} PUBLIC ENGINE_DEBUG)
endif ()

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/Strand-Engine")
target_include_directories(${PROJECT_NAME} PUBLIC ${stbi_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} "d3d11.lib")
target_link_libraries(${PROJECT_NAME} "dxgi.lib")
target_link_libraries(${PROJECT_NAME} "d3dcompiler.lib")

add_compile_definitions("RENDER_ROOT=${CMAKE_SOURCE_DIR}")
add_compile_definitions("SHADER_ROOT=${CMAKE_SOURCE_DIR}/Shaders")