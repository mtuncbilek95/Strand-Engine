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
    Window(const String& Title,const XMINT2& windowSize, bool fullScreen);
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

    XMINT2& GetWindowSize()
    { return WindowSize_; }

    HWND GetWindowHandle()
    { return glfwGetWin32Window(WindowInstance_); }

    [[nodiscard]] GLFWwindow* GetWindow() const
    { return WindowInstance_; }

private:
    String Title_;
    GLFWwindow* WindowInstance_;
    XMINT2 WindowSize_;

};

} // Strand
