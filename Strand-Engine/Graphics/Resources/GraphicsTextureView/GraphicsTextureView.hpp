// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Graphics/GraphicsDevice/DeviceObject.hpp>

#include <Graphics/Resources/GraphicsTextureView/GraphicsTextureViewDesc.hpp>
namespace Strand
{
// @brief GraphicsTextureView class to create texture views and manage them.
class STRAND_API GraphicsTextureView : public DeviceObject
{
public:
    GraphicsTextureView(SharedHeap<GraphicsDevice> device, const GraphicsTextureViewDesc& desc);
    GraphicsTextureView(const GraphicsTextureView&) = delete;
    GraphicsTextureView& operator=(const GraphicsTextureView&) = delete;
    ~GraphicsTextureView() override = default;

    DeviceObjectType GetDeviceObjectType() override
    { return DeviceObjectType::TEXTURE_VIEW; }

    DXHEAP<ID3D11Texture2D>& GetTextureBuffer()
    { return TextureBuffer_; }

    DXHEAP<ID3D11ShaderResourceView>& GetShaderResourceView()
    { return ShaderResourceView_; }

    GraphicsTextureViewDesc& GetDesc()
    { return Desc_; }

private:
    GraphicsTextureViewDesc Desc_{};

    DXHEAP<ID3D11Texture2D> TextureBuffer_;
    DXHEAP<ID3D11ShaderResourceView> ShaderResourceView_;
};

} // Strand
