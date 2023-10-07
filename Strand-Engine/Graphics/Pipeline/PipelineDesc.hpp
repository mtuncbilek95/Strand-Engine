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
