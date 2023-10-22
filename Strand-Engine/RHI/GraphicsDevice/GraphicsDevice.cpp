// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#include "GraphicsDevice.hpp"

#include <Assert/Assert.hpp>

#include <RHI/GraphicsDevice/GraphicsDeviceDesc.hpp>

#include <RHI/Swapchain/Swapchain.hpp>
#include <RHI/Framebuffer/Framebuffer.hpp>
#include <RHI/Shader/Shader.hpp>
#include <RHI/Command/Command.hpp>
#include <RHI/Pipeline/Pipeline.hpp>

#include <RHI/Resources/GraphicsBuffer/GraphicsBuffer.hpp>
#include <RHI/Resources/GraphicsTexture/GraphicsTexture.hpp>
#include <RHI/Resources/GraphicsSampler/GraphicsSampler.hpp>
#include <RHI/Resources/GraphicsResource/GraphicsResource.hpp>


namespace Strand
{

SharedHeap<GraphicsDevice> GraphicsDevice::CreateGraphicsDevice(const GraphicsDeviceDesc& desc)
{
    auto graphicsDevice = MakeShared<GraphicsDevice>(desc);

    switch(desc.ChosenApi_) {
        case GraphicsApi::DIRECTX11:
            break;
        case GraphicsApi::VULKAN:
            break;
    }

    return graphicsDevice;
}

SharedHeap<Swapchain> GraphicsDevice::CreateSwapchain(const SwapchainDesc& desc)
{
    auto swapchain = MakeShared<Swapchain>(desc);
    RegisterDeviceObject(swapchain);

    return swapchain;
}

SharedHeap<Framebuffer> GraphicsDevice::CreateFramebuffer(const FramebufferDesc& desc)
{
    auto framebuffer = MakeShared<Framebuffer>(desc);
    RegisterDeviceObject(framebuffer);

    return framebuffer;
}

SharedHeap<Shader> GraphicsDevice::CreateShader(const ShaderDesc& desc)
{
    auto shader = MakeShared<Shader>(desc);
    RegisterDeviceObject(shader);

    return shader;
}

SharedHeap<Command> GraphicsDevice::CreateCommand()
{
    auto command = MakeShared<Command>();
    RegisterDeviceObject(command);

    return command;
}

SharedHeap<Pipeline> GraphicsDevice::CreateGraphicsPipeline(const GraphicsPipelineDesc& desc)
{
    auto pipeline =  MakeShared<Pipeline>(desc);
    RegisterDeviceObject(pipeline);

    return pipeline;
}

SharedHeap<GraphicsBuffer> GraphicsDevice::CreateGraphicsBuffer(const GraphicsBufferDesc& desc)
{
    auto graphicsBuffer = MakeShared<GraphicsBuffer>(desc);
    RegisterDeviceObject(graphicsBuffer);

    return graphicsBuffer;
}

SharedHeap<GraphicsTexture> GraphicsDevice::CreateGraphicsTexture(const GraphicsTextureDesc& desc)
{
    auto graphicsTexture = MakeShared<GraphicsTexture>(desc);
    RegisterDeviceObject(graphicsTexture);

    return graphicsTexture;
}

SharedHeap<GraphicsSampler> GraphicsDevice::CreateGraphicsSampler(const GraphicsSamplerDesc& desc)
{
    auto graphicsSampler = MakeShared<GraphicsSampler>(desc);
    RegisterDeviceObject(graphicsSampler);

    return graphicsSampler;
}

SharedHeap<GraphicsResource> GraphicsDevice::CreateGraphicsResource(const GraphicsResourceDesc& desc)
{
    auto graphicsResource = MakeShared<GraphicsResource>(desc);
    RegisterDeviceObject(graphicsResource);

    return graphicsResource;
}

void GraphicsDevice::RegisterCommand(ArrayList<SharedHeap<Command>> commands)
{
    STRAND_ERROR_ASSERT(commands.size() > 0, "There is no command in the array!")
    RegisterCommandRHI(commands);
}

void GraphicsDevice::SwapchainPresent()
{
    SwapchainPresentRHI();
}

void GraphicsDevice::RegisterDeviceObject(SharedHeap<DeviceObject> deviceObject)
{
    deviceObject->SetOwnerDevice(shared_from_this());
    DeviceObjects_.push_back(deviceObject);
}

} // Strand