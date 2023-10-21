// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#include "PipelineResource.hpp"

namespace Strand
{
PipelineResource::PipelineResource(SharedHeap<GraphicsDevice> device, const PipelineResourceDesc& desc)
{
    TextureViews_ = desc.TextureViews;
    HasTextureViews_ = desc.BufferViews.size() > 0;

    BufferViews_ = desc.BufferViews;
    HasBufferViews_ = desc.BufferViews.size() > 0;

    Samplers_ = desc.Samplers;
    HasSamplers_ = desc.Samplers.size() > 0;
}

} // Strand