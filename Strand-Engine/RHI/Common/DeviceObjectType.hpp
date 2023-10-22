// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wignored-attributes"

#pragma once

namespace Strand
{

enum class ENGINE_API DeviceObjectType
{
    UNKNOWN,
    SWAPCHAIN,
    FRAMEBUFFER,
    PIPELINE,
    SHADER,
    GRAPHICS_BUFFER,
    GRAPHICS_TEXTURE,
    GRAPHICS_SAMPLER,
    GRAPHICS_RESOURCE
};

} // Strand

#pragma clang diagnostic pop