// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

namespace Strand
{

enum class TextureType
{
    TEXTURE_2D,
    TEXTURE_3D,
    TEXTURE_CUBE
};

enum class TextureMaterialType
{
    BASE_COLOR,
    NORMAL,
    METALLIC,
    ROUGHNESS,
    AMBIENT_OCCLUSION,
    EMISSIVE,
    HEIGHT,
    UNKNOWN
};

} // Strand
