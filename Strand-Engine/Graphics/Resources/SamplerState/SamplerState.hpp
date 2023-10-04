// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Graphics/GraphicsDevice/DeviceObject.hpp>
#include <Graphics/Resources/SamplerState/SamplerStateDesc.hpp>

namespace Strand
{

class STRAND_API SamplerState : public DeviceObject
{
public:
    SamplerState(GraphicsDevice* graphicsDevice,const SamplerStateDesc& desc);
    ~SamplerState() override = default;

    DXHEAP<ID3D11SamplerState>& GetSamplerState() { return SamplerState_; }
    DeviceObjectType GetDeviceObjectType() override { return DeviceObjectType::SAMPLER_STATE; }

private:
    DXHEAP<ID3D11SamplerState> SamplerState_;

    SamplerStateDesc Desc_;
};

} // Strand
