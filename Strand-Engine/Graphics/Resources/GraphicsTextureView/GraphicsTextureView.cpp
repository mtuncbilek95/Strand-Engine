// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#include "GraphicsTextureView.hpp"

#include <Common/Log.hpp>
#include <Graphics/Utils/DxgiUtils.hpp>
#include <Graphics/Resources/ResourceUtils.hpp>
#include <Graphics/GraphicsDevice/GraphicsDevice.hpp>
namespace Strand
{
GraphicsTextureView::GraphicsTextureView(SharedHeap<GraphicsDevice> device, const GraphicsTextureViewDesc& desc)
{
    GraphicsDevice_ = device;
    Desc_ = desc;

    D3D11_TEXTURE2D_DESC textureDesc = {};

    textureDesc.Width = Desc_.TextureImageSize_.x;
    textureDesc.Height = Desc_.TextureImageSize_.y;
    textureDesc.MipLevels = Desc_.MipLevels_;
    textureDesc.ArraySize = Desc_.ArraySize_;
    textureDesc.Format = DxgiUtils::GetDxgiFormat(Desc_.Format_);
    textureDesc.SampleDesc.Count = Desc_.SampleCount_;
    textureDesc.SampleDesc.Quality = Desc_.SampleQuality_;
    textureDesc.Usage = ResourceUtils::GetResourceUsage(Desc_.Usage_);
    textureDesc.BindFlags = ResourceUtils::GetResourceBindFlag(Desc_.BindFlags_);
    textureDesc.CPUAccessFlags = ResourceUtils::GetResourceCPUAccessFlag(Desc_.CPUAccessFlags_);
    textureDesc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA subresourceData = {};
    subresourceData.pSysMem = Desc_.CPUData;
    subresourceData.SysMemPitch = Desc_.CPUDataPitch;
    //subresourceData.SysMemSlicePitch = Desc_.CPUDataSlicePitch;

    if(Desc_.BindFlags_ == ResourceBindFlags::DEPTH_STENCIL)
        DX_PRINT_LOG("Create Depth Stencil Texture", GraphicsDevice_->GetDevice()->CreateTexture2D(&textureDesc, nullptr, TextureBuffer_.GetAddressOf()));
    else
        DX_PRINT_LOG("Create Texture2D", GraphicsDevice_->GetDevice()->CreateTexture2D(&textureDesc, &subresourceData, TextureBuffer_.GetAddressOf()));

    if(Desc_.BindFlags_ == ResourceBindFlags::SHADER_RESOURCE) {
        D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};

        srvDesc.Format = DxgiUtils::GetDxgiFormat(Desc_.Format_);
        srvDesc.ViewDimension = ResourceUtils::GetResourceSRVDimension(Desc_.SRVDimension);
        srvDesc.Texture2D.MostDetailedMip = Desc_.MostDetailedMip;
        srvDesc.Texture2D.MipLevels = Desc_.MipLevels_;

        DX_PRINT_LOG("Create ShaderResourceView", GraphicsDevice_->GetDevice()->CreateShaderResourceView(TextureBuffer_.Get(), &srvDesc, ShaderResourceView_.GetAddressOf()));
    }
}

} // Strand