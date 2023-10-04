// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <cstdint>

namespace Strand
{

enum class DeviceObjectType : uint8_t
{
    NONE,
    SWAPCHAIN,
    FRAMEBUFFER,
    SHADER,
    PIPELINE,
    SAMPLER_STATE,
    COMMAND,
    BUFFER,
    TEXTURE_VIEW,
};

} // Strand
