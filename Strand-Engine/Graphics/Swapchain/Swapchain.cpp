// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#include "Swapchain.hpp"

#include <Common/Log.hpp>
#include <Graphics/GraphicsDevice/GraphicsDevice.hpp>

namespace Strand
{

Swapchain::Swapchain(std::shared_ptr<GraphicsDevice> device, const SwapchainDesc& desc)
{
    GraphicsDevice_ = device;

    DXGI_SWAP_CHAIN_DESC SwapchainDesc = {};

    SwapchainDesc.BufferDesc.Width = desc.WindowSize_.x;
    SwapchainDesc.BufferDesc.Height = desc.WindowSize_.y;

    SwapchainDesc.BufferDesc.Format = DxgiUtils::GetDxgiFormat(desc.Format_);

    SwapchainDesc.BufferDesc.RefreshRate.Numerator = desc.Numerator_;
    SwapchainDesc.BufferDesc.RefreshRate.Denominator = desc.Denominator_;

    SwapchainDesc.BufferDesc.Scaling = SwapchainUtils::GetDxgiScaling(desc.Scaling_);
    SwapchainDesc.BufferDesc.ScanlineOrdering = SwapchainUtils::GetDxgiScanlineOrder(desc.ScanlineOrdering_);

    SwapchainDesc.SampleDesc.Count = desc.SampleCount_;
    SwapchainDesc.SampleDesc.Quality = desc.SampleQuality_;

    SwapchainDesc.BufferUsage = DxgiUtils::GetDxgiUsage(desc.BufferUsage_);
    SwapchainDesc.BufferCount = desc.BufferCount_;

    SwapchainDesc.OutputWindow = desc.WindowHandle_;
    SwapchainDesc.Windowed = desc.Windowed_;
    SwapchainDesc.SwapEffect = SwapchainUtils::GetDxgiSwapEffect(desc.SwapEffect_);
    SwapchainDesc.Flags = 0;

    DX_PRINT_LOG("Get DXGI Device", GraphicsDevice_->GetDevice().As(&m_dxgiDevice));
    DX_PRINT_LOG("Get DXGI Adapter", m_dxgiDevice->GetParent(IID_PPV_ARGS(m_dxgiAdapter.GetAddressOf())));
    DX_PRINT_LOG("Get DXGI Factory", m_dxgiAdapter->GetParent(IID_PPV_ARGS(m_dxgiFactory.GetAddressOf())));
    DX_PRINT_LOG("Create Swapchain", m_dxgiFactory->CreateSwapChain(GraphicsDevice_->GetDevice().Get(), &SwapchainDesc, &m_swapchain));

}

void Swapchain::Present()
{
    m_swapchain->Present(1, 0);
}

DXHEAP<ID3D11Texture2D> Swapchain::GetBackBuffer()
{
    auto backBuffer = new DXHEAP<ID3D11Texture2D>();
    m_swapchain->GetBuffer(0, IID_PPV_ARGS(backBuffer->GetAddressOf()));

    return *backBuffer;
}

} // Strand