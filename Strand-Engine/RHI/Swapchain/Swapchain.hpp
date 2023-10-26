// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <RHI/Swapchain/SwapchainDesc.hpp>
#include <RHI/GraphicsDevice/DeviceObject.hpp>

namespace Strand
{

class Framebuffer;

// @brief Swapchain is a collection of buffers that are used for presenting rendered images to the screen.
class ENGINE_API Swapchain : public DeviceObject
{
    friend class GraphicsDevice;

public:
    Swapchain(const SwapchainDesc& desc)
    { SwapchainDesc_ = desc; }

    Swapchain(const Swapchain&) = delete;
    Swapchain& operator=(const Swapchain&) = delete;
    Swapchain(Swapchain&&) = delete;
    Swapchain& operator=(Swapchain&&) = delete;
    virtual ~Swapchain() = default;

    [[nodiscard]] FORCEINLINE SwapchainDesc GetDesc() const
    { return SwapchainDesc_; }

/*    [[nodiscard]] FORCEINLINE Vector2i GetSize()
    { return SwapchainDesc_.SwapchainSize_; }*/

    [[nodiscard]] FORCEINLINE Framebuffer* GetFramebuffer() const
    { return Framebuffer_; }

    DeviceObjectType GetDeviceObjectType() const override
    { return DeviceObjectType::PIPELINE; }

protected:
    void SetFrameBuffer(Framebuffer* framebuffer)
    { Framebuffer_ = framebuffer; }

    virtual void Present() {};

private:
    SwapchainDesc SwapchainDesc_;
    Framebuffer* Framebuffer_;
};

} // Strand
