// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#include "Framebuffer.hpp"

#include <Common/Log.hpp>
#include <Graphics/GraphicsDevice/GraphicsDevice.hpp>
#include <Graphics/Utils/DxgiUtils.hpp>

namespace Strand
{

Framebuffer::Framebuffer(GraphicsDevice* device, const FramebufferDesc& desc)
{
    GraphicsDevice_ = device;
    Desc_ = desc;
}

void Framebuffer::CreateColorAttachment()
{
    D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
    rtvDesc.Format = DxgiUtils::GetDxgiFormat(Desc_.ColorAttachmentFormat);
    rtvDesc.ViewDimension = FrameBufferUtils::GetD3D11RTVDimension(Desc_.ColorAttachmentDimension);
    rtvDesc.Texture2D.MipSlice = 0;

    DX_PRINT_LOG("Create RenderTargetView", GraphicsDevice_->GetDevice()->CreateRenderTargetView(Desc_.ColorAttachment_.Get(), &rtvDesc, ColorAttachmentRTV_.GetAddressOf()));
}

void Framebuffer::CreateDepthAttachment()
{
    D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
    dsvDesc.Format = DxgiUtils::GetDxgiFormat(Desc_.DepthStencilFormat);
    dsvDesc.ViewDimension = FrameBufferUtils::GetD3D11DSVDimension(Desc_.DepthStencilDimension);
    dsvDesc.Texture2D.MipSlice = 0;

    DX_PRINT_LOG("Create DepthStencilView", GraphicsDevice_->GetDevice()->CreateDepthStencilView(Desc_.DepthAttachment_.Get(), &dsvDesc, DepthAttachmentDSV_.GetAddressOf()));
}

} // Strand