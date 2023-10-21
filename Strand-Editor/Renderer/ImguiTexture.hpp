// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>

namespace Strand
{

class GraphicsTextureView;

class ImguiTexture
{
public:
    ImguiTexture(const SharedHeap<GraphicsTextureView>& texture)
        : Texture_(texture)
    {
    }

public:

};

} // Strand
