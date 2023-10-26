// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <RHI/GraphicsDevice/DeviceObject.hpp>
#include <RHI/Pipeline/GraphicsPipelineDesc.hpp>

namespace Strand
{
// @brief Pipeline is a DeviceObject that contains all the information needed to render a specific type of object.
class ENGINE_API Pipeline : public DeviceObject
{
public:
    NODISCARD FORCEINLINE const GraphicsPipelineDesc GetGraphicsPipelineDesc() const noexcept
    { return GraphicsPipelineDesc_; }

    NODISCARD FORCEINLINE const InputLayoutDesc GetInputLayoutDesc() const noexcept
    { return GraphicsPipelineDesc_.InputLayoutDesc_; }

    NODISCARD FORCEINLINE const RasterizerStateDesc GetRasterizerStateDesc() const noexcept
    { return GraphicsPipelineDesc_.RasterizerStateDesc_; }

    NODISCARD FORCEINLINE const DepthStencilDesc GetDepthStencilStateDesc() const noexcept
    { return GraphicsPipelineDesc_.DepthStencilStateDesc_; }

    NODISCARD FORCEINLINE const BlendStateDesc GetBlendStateDesc() const noexcept
    { return GraphicsPipelineDesc_.BlendStateDesc_; }

    NODISCARD FORCEINLINE const ArrayList<Shader*>& GetShaders() const noexcept
    { return GraphicsPipelineDesc_.Shaders_; }

    NODISCARD FORCEINLINE DeviceObjectType GetDeviceObjectType() const override final
    { return DeviceObjectType::PIPELINE; }

protected:
    Pipeline(const GraphicsPipelineDesc& desc)
    { GraphicsPipelineDesc_ = desc; }

    Pipeline(const Pipeline& other) noexcept = delete;
    Pipeline(Pipeline&& other) noexcept = delete;
    Pipeline& operator=(const Pipeline& other) = delete;
    Pipeline& operator=(Pipeline&& other) noexcept = delete;
    ~Pipeline() override = default;

private:
    GraphicsPipelineDesc GraphicsPipelineDesc_;
};

} // Strand
