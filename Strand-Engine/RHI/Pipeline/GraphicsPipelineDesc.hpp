// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Containers/Memory.hpp>
#include <Containers/ArrayList.hpp>

#include <RHI/Pipeline/InputLayout/InputLayoutDesc.hpp>
#include <RHI/Pipeline/Rasterizer/RasterizerStateDesc.hpp>
#include <RHI/Pipeline/DepthStencil/DepthStencilDesc.hpp>
#include <RHI/Pipeline/Blend/BlendStateDesc.hpp>

namespace Strand
{

class Shader;

// @brief Graphics pipeline description
struct ENGINE_API GraphicsPipelineDesc
{
    // @brief Input layout description for vertex shader to use in input assembler stage
    InputLayoutDesc InputLayoutDesc_;
    // @brief Rasterizer state description for rasterizer stage
    RasterizerStateDesc RasterizerStateDesc_;
    // @brief Depth stencil state description for depth stencil stage
    DepthStencilDesc DepthStencilStateDesc_;
    // @brief Blend state description for output merger stage
    BlendStateDesc BlendStateDesc_;
    // @brief Shaders to use in the current pipeline
    ArrayList<SharedHeap<Shader>> Shaders_;
};

} // Strand
