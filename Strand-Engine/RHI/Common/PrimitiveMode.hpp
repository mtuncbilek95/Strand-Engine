// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wignored-attributes"

#pragma once

namespace Strand
{

enum class ENGINE_API PrimitiveMode
{
    POINT_LIST,
    LINE_LIST,
    LINE_STRIP,
    TRIANGLE_LIST,
    TRIANGLE_STRIP,
    TRIANGLE_FAN
};

} // Strand

#pragma clang diagnostic pop