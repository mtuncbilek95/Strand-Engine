// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>

namespace Strand
{

struct RasterizerStateDesc;
struct DepthStencilStateDesc;
struct BlendStateDesc;
struct InputLayoutDesc;
class SamplerState;
class Shader;


enum class ShaderStage
{
    VERTEX_SHADER,
    PIXEL_SHADER,
    GEOMETRY_SHADER,
    HULL_SHADER,
    DOMAIN_SHADER,
    COMPUTE_SHADER
};

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

struct PipelineDesc
{
    std::vector<Shader*> Shaders_;
    InputLayoutDesc* InputAssemblerDesc_;
    RasterizerStateDesc* RasterizerStateDesc_;
    DepthStencilStateDesc* DepthStencilStateDesc_;
    BlendStateDesc* BlendStateDesc_;
    SamplerState* SamplerStateDesc_;
};

} // Strand
