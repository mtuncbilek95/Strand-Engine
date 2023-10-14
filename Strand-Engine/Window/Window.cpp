// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#include "Window.hpp"

namespace Strand
{


Window::Window(const std::string& Title, const XMINT2& windowSize, bool fullScreen) : m_title(Title)
{
    m_windowSize = windowSize;

    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    if(fullScreen)
        WindowInstance_ = glfwCreateWindow(windowSize.x, windowSize.y, Title.c_str(), glfwGetPrimaryMonitor(), nullptr);
    else
        WindowInstance_ = glfwCreateWindow(windowSize.x, windowSize.y, Title.c_str(), nullptr, nullptr);

    if(fullScreen)
        glfwSetInputMode(WindowInstance_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    else
        glfwSetInputMode(WindowInstance_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

}

void Window::ProcessMessage()
{
    glfwSwapBuffers(WindowInstance_);
    glfwPollEvents();
}

} // Strand