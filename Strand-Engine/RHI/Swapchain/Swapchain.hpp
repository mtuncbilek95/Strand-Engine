// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <RHI/Swapchain/SwapchainDesc.hpp>
#include <RHI/GraphicsDevice/DeviceObject.hpp>
#include <Containers/Math.hpp>

namespace Strand
{

class Framebuffer;

// @brief Swapchain is a collection of buffers that are used for presenting rendered images to the screen.
class ENGINE_API Swapchain : public DeviceObject
{
public:
    [[nodiscard]] FORCEINLINE SwapchainDesc GetDesc() const { return SwapchainDesc_; }
    [[nodiscard]] FORCEINLINE Vector2i GetSize() { return SwapchainDesc_.SwapchainSize_; }
    [[nodiscard]] FORCEINLINE SharedHeap<Framebuffer> GetFramebuffer() const { return Framebuffer_; }

protected:
    Swapchain(const SwapchainDesc& desc)
    { SwapchainDesc_ = desc; }

    Swapchain(const Swapchain&) = delete;
    Swapchain& operator=(const Swapchain&) = delete;
    Swapchain(Swapchain&&) = delete;
    Swapchain& operator=(Swapchain&&) = delete;
    virtual ~Swapchain() = default;

    void SetFrameBuffer(SharedHeap<Framebuffer> framebuffer) { Framebuffer_ = framebuffer; }
private:
    SwapchainDesc SwapchainDesc_;
    SharedHeap<Framebuffer> Framebuffer_;
};

} // Strand
