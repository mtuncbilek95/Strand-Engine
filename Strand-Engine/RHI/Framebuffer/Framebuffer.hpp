// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <RHI/GraphicsDevice/DeviceObject.hpp>
#include <RHI/Framebuffer/FramebufferDesc.hpp>

namespace Strand
{

class ENGINE_API Framebuffer : public DeviceObject
{
public:
    Framebuffer(const FramebufferDesc& desc)
    { FramebufferDesc_ = desc; }

    Framebuffer(const Framebuffer&) = delete;
    Framebuffer& operator=(const Framebuffer&) = delete;
    Framebuffer(Framebuffer&&) = delete;
    Framebuffer& operator=(Framebuffer&&) = delete;
    virtual ~Framebuffer() = default;

    NODISCARD FORCEINLINE FramebufferDesc GetDesc() const
    { return FramebufferDesc_; }

    NODISCARD FORCEINLINE DeviceObjectType GetDeviceObjectType() const override final
    { return DeviceObjectType::FRAMEBUFFER; }


private:
    FramebufferDesc FramebufferDesc_;
};

} // Strand
