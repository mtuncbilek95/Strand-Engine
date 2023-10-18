// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Graphics/GraphicsDevice/DeviceObject.hpp>
#include <Graphics/Resources/SamplerState/SamplerStateDesc.hpp>

namespace Strand
{
// @brief SamplerState class to create sampler states and manage them. It is used to sample textures in shaders.
class STRAND_API SamplerState : public DeviceObject
{
public:
    SamplerState(std::shared_ptr<GraphicsDevice> graphicsDevice,const SamplerStateDesc& desc);
    ~SamplerState() override = default;

    DXHEAP<ID3D11SamplerState>& GetSamplerState() { return SamplerState_; }
    DeviceObjectType GetDeviceObjectType() override { return DeviceObjectType::SAMPLER_STATE; }

private:
    DXHEAP<ID3D11SamplerState> SamplerState_;

    SamplerStateDesc Desc_;
};

} // Strand
