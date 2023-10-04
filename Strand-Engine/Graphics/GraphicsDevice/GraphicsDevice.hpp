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
class STRAND_API GraphicsDevice
{
public:
    GraphicsDevice();
    GraphicsDevice(const GraphicsDevice&) = delete;
    GraphicsDevice& operator=(const GraphicsDevice&) = delete;
    ~GraphicsDevice();

    [[nodiscard]] Swapchain* CreateSwapchain(const SwapchainDesc& desc);
    [[nodiscard]] Framebuffer* CreateFramebuffer(const FramebufferDesc& desc);
    [[nodiscard]] Shader* CreateShader(const ShaderDesc& desc);
    [[nodiscard]] Pipeline* CreatePipeline(const PipelineDesc& desc);
    [[nodiscard]] SamplerState* CreateSamplerState(const SamplerStateDesc& desc);
    [[nodiscard]] CommandList* CreateCommandList();
    [[nodiscard]] GraphicsBuffer* CreateGraphicsBuffer(const GraphicsBufferDesc& desc);
    [[nodiscard]] GraphicsTextureView* CreateGraphicsTextureView(const GraphicsTextureViewDesc& desc);

    void ExecuteCommandList(std::vector<CommandList*> commandList);

    DXHEAP<ID3D11Device>& GetDevice() { return Device_; }
    DXHEAP<ID3D11DeviceContext>& GetImmediateContext() { return ImmediateContext_; }

private:
    std::vector<DeviceObject*> DeviceObjects_;

private:
    DXHEAP<ID3D11Device> Device_;
    DXHEAP<ID3D11DeviceContext> ImmediateContext_;
};

} // Strand
