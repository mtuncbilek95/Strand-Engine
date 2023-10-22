// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <RHI/Common/FaceCullMode.hpp>
#include <RHI/Common/MeshMode.hpp>
#include <RHI/Common/FaceDirection.hpp>

namespace Strand
{

// @brief Rasterizer state description
struct ENGINE_API RasterizerStateDesc
{
    MeshMode MeshMode_;
    FaceCullMode FaceCullMode_;
    FaceDirection FaceDirection_;
    int DepthBias_;
    float DepthBiasClamp_;
    float SlopeScaledDepthBias_;
    bool DepthClipEnable_;
    bool ScissorEnable_;
    bool MultisampleEnable_;
    bool AntialiasedLineEnable_;
};

} // Strand
