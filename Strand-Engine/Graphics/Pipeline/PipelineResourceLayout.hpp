// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>
#include <Graphics/Pipeline/ShaderStage.hpp>

namespace Strand
{

struct STRAND_API PipelineShaderStageResourceLayout
{
    ShaderStage Stage_;
    uint8_t ConstantBuffersSlotCount_;
    uint8_t TextureViewsSlotCount_;
    uint8_t SamplerStatesSlotCount_;
};

struct STRAND_API PipelineResourceLayout
{
    ArrayList<PipelineShaderStageResourceLayout> ShaderStages_;
};

} // Strand
