// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>

#include <Graphics/Framebuffer/FramebufferDesc.hpp>
#include <Graphics/GraphicsDevice/DeviceObject.hpp>

namespace Strand
{

class GraphicsDevice;

class STRAND_API Framebuffer : public DeviceObject
{
public:
    Framebuffer(GraphicsDevice* device, const FramebufferDesc& desc);
    ~Framebuffer() override = default;

    void CreateColorAttachment();
    void CreateDepthAttachment();

    DXHEAP<ID3D11RenderTargetView>& GetColorAttachmentRTV()
    { return ColorAttachmentRTV_; }
    DXHEAP<ID3D11DepthStencilView>& GetDepthAttachmentDSV()
    { return DepthAttachmentDSV_; }

    DeviceObjectType GetDeviceObjectType() override { return DeviceObjectType::FRAMEBUFFER; }
private:

    DXHEAP<ID3D11RenderTargetView> ColorAttachmentRTV_;
    DXHEAP<ID3D11DepthStencilView> DepthAttachmentDSV_;

    FramebufferDesc Desc_;
};

} // Strand
