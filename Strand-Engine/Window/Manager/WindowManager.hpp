// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Singleton.hpp>
#include <Window/Window.hpp>

#include <memory>

namespace Strand
{

class STRAND_API WindowManager : public Singleton<WindowManager>
{
public:
    WindowManager() = default;
    ~WindowManager() = default;

    void InitializeWindow(std::string title, XMINT2 size, bool fullScreen)
    {
        if(m_Window == nullptr)
            m_Window = std::make_shared<Window>(title, size, fullScreen);
    }

    std::shared_ptr<Window> GetWindow() const { return m_Window; }
private:
    std::shared_ptr<Window> m_Window;
};

} // Strand
