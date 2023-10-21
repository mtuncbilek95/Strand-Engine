// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>

namespace Strand
{

class GraphicsTextureView;
class PipelineResource;

class ImguiTexture
{
public:
    ImguiTexture(SharedHeap<GraphicsTextureView> texture);
    ~ImguiTexture() = default;

    SharedHeap<GraphicsTextureView> GetTexture() const { return Texture_; }
    SharedHeap<PipelineResource> GetResource() const { return Resource_; }

private:
    SharedHeap<GraphicsTextureView> Texture_;
    SharedHeap<PipelineResource> Resource_;
};

} // Strand
