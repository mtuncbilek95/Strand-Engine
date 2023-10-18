// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>

namespace Strand
{

enum class WindowStyle
{
    None = 0,
    Titlebar = 1 << 0,
    Resize = 1 << 1,
    Close = 1 << 2,
    Fullscreen = 1 << 3,
    Default = Titlebar | Resize | Close
};

enum class WindowState
{
    None = 0,
    Maximized = 1 << 0,
    Minimized = 1 << 1,
    Fullscreen = 1 << 2,
    Default = None
};

struct WindowDesc
{
    XMINT2 WindowSize;
    String WindowName;
    WindowStyle WindowStyle;
    WindowState WindowState;
};

}
