// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Containers/Memory.hpp>
#include <Containers/Common.hpp>

#include "RHI/Common/GraphicsApi.hpp"
#include "RHI/Common/TextureFormat.hpp"

namespace Strand
{

class Window;

/*
 * @brief GraphicsDeviceDesc is used to create a GraphicsDevice.
 */
struct ENGINE_API GraphicsDeviceDesc
{
    GraphicsApi ChosenApi_;
    SharedHeap<Window> OwnedWindow_;
    TextureFormat ColorFormat_;
    TextureFormat DepthFormat_;
    uint8_t MultisampleCount_;
};

} // Strand
