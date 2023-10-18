// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>

#include <Graphics/Framebuffer/FramebufferDesc.hpp>
#include <Graphics/GraphicsDevice/DeviceObject.hpp>

namespace Strand
{

class GraphicsDevice;

// @brief Framebuffer class to create one buffer for whole frame structure and manage them.
class STRAND_API Framebuffer : public DeviceObject
{
public:
    Framebuffer(std::shared_ptr<GraphicsDevice> device, const FramebufferDesc& desc);
    ~Framebuffer() override = default;

    // @brief Create color attachment for framebuffer. AKA RenderTargetView
    void CreateColorAttachment();
    // @brief Create depth attachment for framebuffer. AKA DepthStencilView
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
