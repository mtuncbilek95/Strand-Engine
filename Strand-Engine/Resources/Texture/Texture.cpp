// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#include "Texture.hpp"

#include <Graphics/Manager/GraphicsManager.hpp>

namespace Strand
{

void Texture::AllocateTexture()
{

    GraphicsTextureViewDesc textureViewDesc = {
            .TextureImageSize = { TextureDesc_.width, TextureDesc_.height },
            .MipLevels = 1,
            .MostDetailedMip = 0,
            .ArraySize = 1,
            .Format = DxgiFormat::RGBA8_UNSIGNED_NORMALIZED,
            .SampleCount = 1,
            .SampleQuality = 0,
            .SRVDimension = ShaderResourceViewDimension::TEXTURE2D,
            .Usage = ResourceUsage::IMMUTABLE,
            .BindFlags = ResourceBindFlags::SHADER_RESOURCE,
            .CPUAccessFlags = ResourceCPUAccessFlags::NONE,
            .MiscFlags = 0,

            .CPUData = TextureDesc_.data,
            .CPUDataPitch = TextureDesc_.width * 4,
            .CPUDataSlicePitch = 0
    };

    TextureView_ = GraphicsManager::GetInstance().GetGraphicsDevice()->CreateGraphicsTextureView(textureViewDesc);
}

} // Strand