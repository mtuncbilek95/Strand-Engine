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

GraphicsDevice::GraphicsDevice(const GraphicsDeviceDesc& desc)
{
    Desc_ = desc;
}

SharedHeap<GraphicsDevice> GraphicsDevice::CreateGraphicsDevice(const GraphicsDeviceDesc& desc)
{
    SharedHeap<GraphicsDevice> graphicsDevice = nullptr;

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

void GraphicsDevice::RegisterDeviceObject(SharedHeap<DeviceObject> deviceObject)
{
    deviceObject->SetOwnerDevice(shared_from_this());
    DeviceObjects_.push_back(deviceObject);

}

} // Strand