// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wignored-attributes"

#pragma once

namespace Strand
{

/*
 * @brief Graphics API enum class that will decide which graphics API will be used.
 */
enum class ENGINE_API GraphicsApi
{
    DIRECTX11,
    VULKAN
};

} // Strand

#pragma clang diagnostic pop