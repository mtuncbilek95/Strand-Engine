// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#include "GraphicsDevice.hpp"

#include <Common/Log.hpp>
#include <Graphics/Swapchain/Swapchain.hpp>
#include <Graphics/Framebuffer/Framebuffer.hpp>
#include <Graphics/Command/CommandList.hpp>
#include <Graphics/Resources/GraphicsBuffer/GraphicsBuffer.hpp>
#include <Graphics/Shader/Shader.hpp>
#include <Graphics/Pipeline/Pipeline.hpp>
#include <Graphics/Resources/SamplerState/SamplerState.hpp>
#include <Graphics/Resources/GraphicsTextureView/GraphicsTextureView.hpp>

namespace Strand
{

GraphicsDevice::GraphicsDevice()
{
    DX_PRINT_LOG("Create Graphics Device", D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &Device_, nullptr, &ImmediateContext_));
}

GraphicsDevice::~GraphicsDevice()
{
    for(auto& obj : DeviceObjects_) {
        obj.reset();
    }

    DeviceObjects_.clear();

    ImmediateContext_->Release();
    Device_->Release();
}

SharedHeap<Swapchain> GraphicsDevice::CreateSwapchain(const SwapchainDesc& desc)
{
    Swapchain_ = std::make_shared<Swapchain>(shared_from_this(), desc);
    DeviceObjects_.push_back(Swapchain_);

    return Swapchain_;
}

SharedHeap<Framebuffer> GraphicsDevice::CreateFramebuffer(const FramebufferDesc& desc)
{
    auto framebuffer = std::make_shared<Framebuffer>(shared_from_this(), desc);
    DeviceObjects_.push_back(framebuffer);

    return framebuffer;
}

SharedHeap<Shader> GraphicsDevice::CreateShader(const ShaderDesc& desc)
{
    auto shader = std::make_shared<Shader>(shared_from_this(), desc);
    DeviceObjects_.push_back(shader);

    return shader;
}

SharedHeap<Pipeline> GraphicsDevice::CreatePipeline(const PipelineDesc& desc)
{
    auto pipeline = std::make_shared<Pipeline>(shared_from_this(), desc);
    DeviceObjects_.push_back(pipeline);

    return pipeline;
}

SharedHeap<SamplerState> GraphicsDevice::CreateSamplerState(const SamplerStateDesc& desc)
{
    auto samplerState = std::make_shared<SamplerState>(shared_from_this(), desc);
    DeviceObjects_.push_back(samplerState);

    return samplerState;
}

SharedHeap<CommandList> GraphicsDevice::CreateCommandList()
{
    auto commandList = std::make_shared<CommandList>(shared_from_this());
    DeviceObjects_.push_back(commandList);

    return commandList;
}

SharedHeap<GraphicsBuffer> GraphicsDevice::CreateGraphicsBuffer(const GraphicsBufferDesc& desc)
{
    auto graphicsBuffer = std::make_shared<GraphicsBuffer>(shared_from_this(), desc);
    DeviceObjects_.push_back(graphicsBuffer);

    return graphicsBuffer;
}

SharedHeap<GraphicsTextureView> GraphicsDevice::CreateGraphicsTextureView(const GraphicsTextureViewDesc& desc)
{
    auto graphicsTextureView = std::make_shared<GraphicsTextureView>(shared_from_this(), desc);
    DeviceObjects_.push_back(graphicsTextureView);

    return graphicsTextureView;
}

void GraphicsDevice::ExecuteCommandList(ArrayList<SharedHeap<CommandList>> commandList)
{
    for(auto & i : commandList) {
        i->GetDefferedContext()->FinishCommandList(false,  i->GetCommandList().GetAddressOf());
        ImmediateContext_->ExecuteCommandList(i->GetCommandList().Get(), false);
        i->ClearCommandList();
    }
}

} // Strand