// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>

#include <Graphics/GraphicsDevice/DeviceObject.hpp>
#include <Graphics/Swapchain/SwapchainDesc.hpp>

namespace Strand
{

class GraphicsDevice;

// @brief Swapchain class that handles the frame-buffers and the presentation of the images.
class STRAND_API Swapchain : public DeviceObject
{
public:
    Swapchain(GraphicsDevice* device, const SwapchainDesc& desc);
    Swapchain(const Swapchain&) = delete;
    Swapchain& operator=(const Swapchain&) = delete;
    ~Swapchain() override = default;

    void Present();
    DXHEAP<ID3D11Texture2D> GetBackBuffer();

    DeviceObjectType GetDeviceObjectType() override { return DeviceObjectType::SWAPCHAIN; }
private:
    DXHEAP<IDXGISwapChain> m_swapchain;

    DXHEAP<IDXGIDevice> m_dxgiDevice;
    DXHEAP<IDXGIAdapter> m_dxgiAdapter;
    DXHEAP<IDXGIFactory> m_dxgiFactory;
};

} // Strand
