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
        delete obj;
    }

    DeviceObjects_.clear();

    ImmediateContext_->Release();
    Device_->Release();
}

Swapchain* GraphicsDevice::CreateSwapchain(const SwapchainDesc& desc)
{
    DeviceObject* obj = new Swapchain(this, desc);
    DeviceObjects_.push_back(obj);

    return dynamic_cast<Swapchain*>(obj);
}

Framebuffer* GraphicsDevice::CreateFramebuffer(const FramebufferDesc& desc)
{
    DeviceObject* obj = new Framebuffer(this, desc);
    DeviceObjects_.push_back(obj);

    return dynamic_cast<Framebuffer*>(obj);
}

Shader* GraphicsDevice::CreateShader(const ShaderDesc& desc)
{
    DeviceObject* obj = new Shader(this, desc);
    DeviceObjects_.push_back(obj);

    return dynamic_cast<Shader*>(obj);
}

Pipeline* GraphicsDevice::CreatePipeline(const PipelineDesc& desc)
{
    DeviceObject* obj = new Pipeline(this, desc);
    DeviceObjects_.push_back(obj);

    return dynamic_cast<Pipeline*>(obj);
}

SamplerState* GraphicsDevice::CreateSamplerState(const SamplerStateDesc& desc)
{
    DeviceObject* obj = new SamplerState(this, desc);
    DeviceObjects_.push_back(obj);

    return dynamic_cast<SamplerState*>(obj);
}

CommandList* GraphicsDevice::CreateCommandList()
{
    DeviceObject* obj = new CommandList(this);
    DeviceObjects_.push_back(obj);

    return dynamic_cast<CommandList*>(obj);
}

GraphicsBuffer* GraphicsDevice::CreateGraphicsBuffer(const GraphicsBufferDesc& desc)
{
    DeviceObject* obj = new GraphicsBuffer(this, desc);
    DeviceObjects_.push_back(obj);

    return dynamic_cast<GraphicsBuffer*>(obj);
}

GraphicsTextureView* GraphicsDevice::CreateGraphicsTextureView(const GraphicsTextureViewDesc& desc)
{
    DeviceObject* obj = new GraphicsTextureView(this, desc);
    DeviceObjects_.push_back(obj);

    return dynamic_cast<GraphicsTextureView*>(obj);
}

void GraphicsDevice::ExecuteCommandList(std::vector<CommandList*> commandList)
{
    for(auto & i : commandList) {
        i->GetDefferedContext()->FinishCommandList(false,  i->GetCommandList().GetAddressOf());
        ImmediateContext_->ExecuteCommandList(i->GetCommandList().Get(), false);
    }
}

} // Strand