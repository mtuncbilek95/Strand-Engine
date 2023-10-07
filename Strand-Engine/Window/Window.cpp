// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#include "Window.hpp"

namespace Strand
{


Window::Window(const std::string& Title, const XMINT2& windowSize, bool fullScreen) : m_title(Title)
{
    m_windowSize = { static_cast<uint32_t>(windowSize.x), static_cast<uint32_t>(windowSize.y) };

    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    if(fullScreen)
        WindowInstance_ = glfwCreateWindow(glfwGetVideoMode(glfwGetPrimaryMonitor())->width, glfwGetVideoMode(glfwGetPrimaryMonitor())->height, Title.c_str(), glfwGetPrimaryMonitor(), nullptr);
    else
        WindowInstance_ = glfwCreateWindow(windowSize.x, windowSize.y, Title.c_str(), nullptr, nullptr);

    glfwSetInputMode(WindowInstance_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::ProcessMessage()
{
    glfwPollEvents();
}

} // Strand