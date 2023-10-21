// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>
#include <Graphics/Utils/DxgiUtils.hpp>
#include <Graphics/Resources/ResourceUtils.hpp>

namespace Strand
{

struct STRAND_API GraphicsTextureViewDesc
{
    XMINT2 TextureImageSize_;
    uint32_t MipLevels_;
    uint32_t MostDetailedMip;
    uint32_t ArraySize_;
    DxgiFormat Format_;
    uint32_t SampleCount_;
    uint32_t SampleQuality_;
    ShaderResourceViewDimension SRVDimension;
    ResourceUsage Usage_;
    ResourceBindFlags BindFlags_;
    ResourceCPUAccessFlags CPUAccessFlags_;
    uint32_t MiscFlags_;

    const void* CPUData;
    int32_t CPUDataPitch;
    int32_t CPUDataSlicePitch;
};

} // Strand
