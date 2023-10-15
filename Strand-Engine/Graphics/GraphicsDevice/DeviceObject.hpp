// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>
#include <Graphics/GraphicsDevice/DeviceObjectDesc.hpp>

namespace Strand
{

class GraphicsDevice;

// @brief Base class for all device objects such as buffers, textures, etc.
class STRAND_API DeviceObject
{
public:
    DeviceObject() = default;
    DeviceObject(const DeviceObject&) = delete;
    virtual DeviceObject& operator=(const DeviceObject&) = delete;
    virtual ~DeviceObject() = default;

    virtual DeviceObjectType GetDeviceObjectType() = 0;

protected:
    GraphicsDevice* GraphicsDevice_ = nullptr;
};

} // Strand
