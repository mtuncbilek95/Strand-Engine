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
    [[nodiscard]] FORCEINLINE const GraphicsPipelineDesc GetGraphicsPipelineDesc() const noexcept
    { return GraphicsPipelineDesc_; }

    [[nodiscard]] FORCEINLINE const InputLayoutDesc GetInputLayoutDesc() const noexcept
    { return GraphicsPipelineDesc_.InputLayoutDesc_; }

    [[nodiscard]] FORCEINLINE const RasterizerStateDesc GetRasterizerStateDesc() const noexcept
    { return GraphicsPipelineDesc_.RasterizerStateDesc_; }

    [[nodiscard]] FORCEINLINE const DepthStencilDesc GetDepthStencilStateDesc() const noexcept
    { return GraphicsPipelineDesc_.DepthStencilStateDesc_; }

    [[nodiscard]] FORCEINLINE const BlendStateDesc GetBlendStateDesc() const noexcept
    { return GraphicsPipelineDesc_.BlendStateDesc_; }

    [[nodiscard]] FORCEINLINE const ArrayList<SharedHeap<Shader>> GetShaders() const noexcept
    { return GraphicsPipelineDesc_.Shaders_; }

    DeviceObjectType GetDeviceObjectType() const override final
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
