// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Containers/Math.hpp>
#include <RHI/Common/TextureFormat.hpp>

namespace Strand
{
// @brief SwapchainDesc is a struct that contains the information about the swapchain.
struct ENGINE_API SwapchainDesc
{
    TextureFormat ColorFormat_;
    TextureFormat DepthFormat_;
    Vector2i SwapchainSize_;
};

} // Strand
