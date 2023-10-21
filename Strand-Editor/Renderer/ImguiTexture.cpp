// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#include "ImguiTexture.hpp"

#include <Graphics/Resources/GraphicsTextureView/GraphicsTextureView.hpp>
#include <Graphics/Resources/PipelineResource/PipelineResource.hpp>

#include <Graphics/GraphicsDevice/GraphicsDevice.hpp>

namespace Strand
{

ImguiTexture::ImguiTexture(SharedHeap<GraphicsTextureView> texture) : Texture_(texture)
{
    auto resource = texture->GetTextureBuffer();
    if(!resource)
        return;

    PipelineResourceDesc resourceDesc = {};
    resourceDesc.TextureViews.push_back(texture);

    Resource_ = Texture_->GetGraphicsDevice()->CreatePipelineResource(resourceDesc);
}

} // Strand