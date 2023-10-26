// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Core.hpp>
#include <String.hpp>

#include <RHI/Common/DeviceObjectType.hpp>

using namespace Strand_Std;

namespace Strand
{

/*
 * @brief Base class for all device objects. None of the graphics api objects should be created directly
 * with this class. They should be created with the related classes. For example if user wants to create
 * DirectX11 Shader, they should inherit from Shader class. Same goes for other apis and objects.
 */
class ENGINE_API DeviceObject
{
    friend class GraphicsDevice;
public:
    FORCEINLINE void SetObjectName(const String& name) { SetObjectNameRHI(name); }

    NODISCARD FORCEINLINE const String& GetName() const { return Name_; }
    NODISCARD FORCEINLINE GraphicsDevice* GetOwnerDevice() const { return GraphicsDevice_; }
    NODISCARD FORCEINLINE virtual DeviceObjectType GetDeviceObjectType() const = 0;

protected:
    DeviceObject() = default;
    DeviceObject(const DeviceObject& other) noexcept = delete;
    DeviceObject(DeviceObject&& other) noexcept = delete;
    DeviceObject& operator=(const DeviceObject& other) = delete;
    DeviceObject& operator=(DeviceObject&& other) noexcept = delete;
    virtual ~DeviceObject() = default;

    FORCEINLINE virtual void SetObjectNameRHI(const String& name) {};

private:
    FORCEINLINE void SetOwnerDevice(GraphicsDevice* device) { GraphicsDevice_ = device; }

private:
    String Name_;
    GraphicsDevice* GraphicsDevice_;
};

} // Strand
