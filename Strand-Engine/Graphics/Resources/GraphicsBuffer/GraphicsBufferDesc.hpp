// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>
#include <Graphics/Resources/ResourceUtils.hpp>

namespace Strand
{

struct GraphicsBufferDesc
{
    ResourceUsage Usage;
    ResourceCPUAccessFlags CPUAccessFlags;
    ResourceBindFlags BindFlags;
    uint8_t MiscFlags;
    uint64_t ByteWidth;
    uint64_t StructureByteStride;

    void* CPUData;
};

} // Strand
