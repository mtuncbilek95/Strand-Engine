// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>

namespace Strand
{

class DeviceObject;
class Swapchain;
class Framebuffer;
class Shader;
class Pipeline;
class SamplerState;
class CommandList;
class GraphicsBuffer;
class GraphicsTextureView;

struct SwapchainDesc;
struct FramebufferDesc;
struct ShaderDesc;
struct PipelineDesc;
struct SamplerStateDesc;
struct GraphicsBufferDesc;
struct GraphicsTextureViewDesc;

// @brief GraphicsDevice is the main class for creating and managing graphics resources.
class STRAND_API GraphicsDevice : public std::enable_shared_from_this<GraphicsDevice>
{
public:
    GraphicsDevice();
    GraphicsDevice(const GraphicsDevice&) = delete;
    GraphicsDevice& operator=(const GraphicsDevice&) = delete;
    ~GraphicsDevice();

    [[nodiscard]] std::shared_ptr<Swapchain> CreateSwapchain(const SwapchainDesc& desc);
    [[nodiscard]] std::shared_ptr<Framebuffer> CreateFramebuffer(const FramebufferDesc& desc);
    [[nodiscard]] std::shared_ptr<Shader> CreateShader(const ShaderDesc& desc);
    [[nodiscard]] std::shared_ptr<Pipeline> CreatePipeline(const PipelineDesc& desc);
    [[nodiscard]] std::shared_ptr<SamplerState> CreateSamplerState(const SamplerStateDesc& desc);
    [[nodiscard]] std::shared_ptr<CommandList> CreateCommandList();
    [[nodiscard]] std::shared_ptr<GraphicsBuffer> CreateGraphicsBuffer(const GraphicsBufferDesc& desc);
    [[nodiscard]] std::shared_ptr<GraphicsTextureView> CreateGraphicsTextureView(const GraphicsTextureViewDesc& desc);

    void ExecuteCommandList(std::vector<std::shared_ptr<CommandList>> commandList);

    DXHEAP<ID3D11Device>& GetDevice() { return Device_; }
    DXHEAP<ID3D11DeviceContext>& GetImmediateContext() { return ImmediateContext_; }

private:
    std::vector<std::shared_ptr<DeviceObject>> DeviceObjects_;

private:
    DXHEAP<ID3D11Device> Device_;
    DXHEAP<ID3D11DeviceContext> ImmediateContext_;
};

} // Strand
