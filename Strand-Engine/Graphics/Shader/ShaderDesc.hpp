// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>

namespace Strand
{

enum class ShaderType
{
    VERTEX_SHADER,
    PIXEL_SHADER,
    GEOMETRY_SHADER,
    HULL_SHADER,
    DOMAIN_SHADER,
    COMPUTE_SHADER
};

struct ShaderDesc
{
    std::string ShaderName_;
    std::string EntryPoint_;
    ShaderType Type_;
};

} // Strand
