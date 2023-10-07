// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>
#include <Graphics/Pipeline/ShaderStage.hpp>

namespace Strand
{

struct PipelineShaderStageResourceLayout
{
    ShaderStage Stage_;
    uint8_t ConstantBuffersSlotCount_;
    uint8_t TextureViewsSlotCount_;
    uint8_t SamplerStatesSlotCount_;
};

struct PipelineResourceLayout
{
    std::vector<PipelineShaderStageResourceLayout> ShaderStages_;
};

} // Strand
