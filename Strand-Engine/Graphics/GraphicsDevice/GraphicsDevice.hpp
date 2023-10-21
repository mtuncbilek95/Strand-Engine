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
class PipelineResource;

struct SwapchainDesc;
struct FramebufferDesc;
struct ShaderDesc;
struct PipelineDesc;
struct SamplerStateDesc;
struct GraphicsBufferDesc;
struct GraphicsTextureViewDesc;
struct PipelineResourceDesc;

// @brief GraphicsDevice is the main class for creating and managing graphics resources.
class STRAND_API GraphicsDevice : public std::enable_shared_from_this<GraphicsDevice>
{
public:
    GraphicsDevice();
    GraphicsDevice(const GraphicsDevice&) = delete;
    GraphicsDevice& operator=(const GraphicsDevice&) = delete;
    ~GraphicsDevice();

    [[nodiscard]] SharedHeap<Swapchain> CreateSwapchain(const SwapchainDesc& desc);
    [[nodiscard]] SharedHeap<Framebuffer> CreateFramebuffer(const FramebufferDesc& desc);
    [[nodiscard]] SharedHeap<Shader> CreateShader(const ShaderDesc& desc);
    [[nodiscard]] SharedHeap<Pipeline> CreatePipeline(const PipelineDesc& desc);
    [[nodiscard]] SharedHeap<SamplerState> CreateSamplerState(const SamplerStateDesc& desc);
    [[nodiscard]] SharedHeap<CommandList> CreateCommandList();
    [[nodiscard]] SharedHeap<GraphicsBuffer> CreateGraphicsBuffer(const GraphicsBufferDesc& desc);
    [[nodiscard]] SharedHeap<GraphicsTextureView> CreateGraphicsTextureView(const GraphicsTextureViewDesc& desc);
    [[nodiscard]] SharedHeap<PipelineResource> CreatePipelineResource(const PipelineResourceDesc& desc);

    void ExecuteCommandList(ArrayList<SharedHeap<CommandList>> commandList);

    [[nodiscard]] DXHEAP<ID3D11Device>& GetDevice() { return Device_; }
    [[nodiscard]] DXHEAP<ID3D11DeviceContext>& GetImmediateContext() { return ImmediateContext_; }

    [[nodiscard]] SharedHeap<Swapchain> GetSwapchain() { return Swapchain_; }

private:
    ArrayList<SharedHeap<DeviceObject>> DeviceObjects_;
    SharedHeap<Swapchain> Swapchain_;

private:
    DXHEAP<ID3D11Device> Device_;
    DXHEAP<ID3D11DeviceContext> ImmediateContext_;
};

} // Strand
