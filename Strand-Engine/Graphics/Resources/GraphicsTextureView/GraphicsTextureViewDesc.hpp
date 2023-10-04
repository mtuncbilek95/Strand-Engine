// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>
#include <Graphics/Utils/DxgiUtils.hpp>
#include <Graphics/Resources/ResourceUtils.hpp>

namespace Strand
{

struct GraphicsTextureViewDesc
{
    XMINT2 TextureImageSize;
    uint32_t MipLevels;
    uint32_t MostDetailedMip;
    uint32_t ArraySize;
    DxgiFormat Format;
    uint32_t SampleCount;
    uint32_t SampleQuality;
    ShaderResourceViewDimension SRVDimension;
    ResourceUsage Usage;
    ResourceBindFlags BindFlags;
    ResourceCPUAccessFlags CPUAccessFlags;
    uint32_t MiscFlags;

    const void* CPUData;
    int32_t CPUDataPitch;
    int32_t CPUDataSlicePitch;
};

} // Strand
