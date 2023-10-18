// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#include "Texture.hpp"

#include <Graphics/Manager/GraphicsManager.hpp>

namespace Strand
{

void Texture::AllocateTexture()
{

    GraphicsTextureViewDesc textureViewDesc = {
            .TextureImageSize_ = {TextureDesc_.width, TextureDesc_.height },
            .MipLevels_ = 1,
            .MostDetailedMip = 0,
            .ArraySize_ = 1,
            .Format_ = DxgiFormat::RGBA8_UNSIGNED_NORMALIZED,
            .SampleCount_ = 1,
            .SampleQuality_ = 0,
            .SRVDimension = ShaderResourceViewDimension::TEXTURE2D,
            .Usage_ = ResourceUsage::IMMUTABLE,
            .BindFlags_ = ResourceBindFlags::SHADER_RESOURCE,
            .CPUAccessFlags_ = ResourceCPUAccessFlags::NONE,
            .MiscFlags_ = 0,

            .CPUData = TextureDesc_.data,
            .CPUDataPitch = TextureDesc_.width * 4,
            .CPUDataSlicePitch = 0
    };

    TextureView_ = GraphicsManager::GetInstance().GetGraphicsDevice()->CreateGraphicsTextureView(textureViewDesc);
}

} // Strand