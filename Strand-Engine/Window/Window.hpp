// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>


using namespace DirectX;

namespace Strand
{

class Window
{
public:
    Window(std::string const& Title,const XMINT2& windowSize, bool fullScreen);
    Window(const Window&) = delete;
    Window(Window&&) = delete;
    Window& operator=(const Window&) = delete;
    Window& operator=(Window&&) = delete;
    ~Window() = default;

    void ProcessMessage();

    [[nodiscard]] bool ShouldClose() const
    { return glfwWindowShouldClose(WindowInstance_); }

    void SetShouldClose(const bool shouldClose)
    { glfwSetWindowShouldClose(WindowInstance_, shouldClose); }

    XMUINT2& GetWindowSize()
    { return m_windowSize; }

    HWND GetWindowHandle()
    { return glfwGetWin32Window(WindowInstance_); }

    [[nodiscard]] GLFWwindow* GetWindow() const
    { return WindowInstance_; }

private:
    std::string m_title;
    GLFWwindow* WindowInstance_;
    XMUINT2 m_windowSize;

};

} // Strand
