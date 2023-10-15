// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>
#include <Graphics/GraphicsDevice/DeviceObject.hpp>
#include <Graphics/Pipeline/PipelineDesc.hpp>
#include <Graphics/Shader/ShaderDesc.hpp>
#include <Graphics/Pipeline/PipelineResourceLayout.hpp>

namespace Strand
{
// @brief Pipeline class to create and manage pipeline states.
class STRAND_API Pipeline : public DeviceObject
{
public:
    Pipeline(GraphicsDevice* device, const PipelineDesc& desc);
    Pipeline(const Pipeline&) = delete;
    Pipeline& operator=(const Pipeline&) = delete;
    ~Pipeline() override = default;

    DXHEAP<ID3D11InputLayout>& GetInputLayout()
    { return InputLayout_; }

    DXHEAP<ID3D11DepthStencilState>& GetDepthStencilState()
    { return DepthState_; }

    DXHEAP<ID3D11RasterizerState>& GetRasterizerState()
    { return RasterizerState_; }

    DXHEAP<ID3D11BlendState>& GetBlendState()
    { return BlendState_; }

    DXHEAP<ID3D11SamplerState>& GetSamplerState()
    { return SamplerState_; }

    [[nodiscard]] Shader* GetShader(ShaderType stage);

    [[nodiscard]] const PipelineDesc& GetDesc() const
    { return Desc_; }

    [[nodiscard]] const PipelineResourceLayout& GetObjectStageDesc() const
    { return ObjectStageDesc_; }

    DeviceObjectType GetDeviceObjectType() override
    { return DeviceObjectType::PIPELINE; }

private:
    void CreateDepthStencilState();
    void CreateRasterizerState();
    void CreateBlendState();

private:
    PipelineDesc Desc_;
    PipelineResourceLayout ObjectStageDesc_;

    DXHEAP<ID3D11InputLayout> InputLayout_;
    DXHEAP<ID3D11DepthStencilState> DepthState_;
    DXHEAP<ID3D11RasterizerState> RasterizerState_;
    DXHEAP<ID3D11BlendState> BlendState_;
    DXHEAP<ID3D11SamplerState> SamplerState_;
};

} // Strand
