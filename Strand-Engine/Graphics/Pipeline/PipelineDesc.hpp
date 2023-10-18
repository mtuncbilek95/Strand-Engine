// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>

#include <Graphics/Shader/Shader.hpp>
#include <Graphics/Pipeline/InputLayout/InputLayout.hpp>
#include <Graphics/Pipeline/Rasterizer/Rasterizer.hpp>
#include <Graphics/Pipeline/DepthStencil/DepthStencil.hpp>
#include <Graphics/Pipeline/Blend/Blend.hpp>
#include <Graphics/Resources/SamplerState/SamplerState.hpp>

namespace Strand
{

struct PipelineDesc
{
    std::vector<std::shared_ptr<Shader>> Shaders_;
    InputLayoutDesc InputAssemblerDesc_;
    RasterizerStateDesc RasterizerStateDesc_;
    DepthStencilStateDesc DepthStencilStateDesc_;
    BlendStateDesc BlendStateDesc_;
    std::shared_ptr<SamplerState> SamplerStateDesc_;
};

} // Strand
