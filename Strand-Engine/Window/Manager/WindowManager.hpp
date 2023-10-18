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

    void InitializeWindow(String title, XMINT2 size, bool fullScreen)
    {
        if(Window_ == nullptr)
            Window_ = std::make_shared<Window>(title, size, fullScreen);
    }

    SharedHeap<Window> GetWindow() const { return Window_; }
private:
    SharedHeap<Window> Window_;
};

} // Strand
