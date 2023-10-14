// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>

namespace Strand
{

struct TextureDesc
{
    int32_t width;
    int32_t height;
    int32_t channels;

    uint8_t* data;
};

}