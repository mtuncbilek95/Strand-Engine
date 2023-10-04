// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#include "SamplerState.hpp"

#include <Common/Log.hpp>
#include <Graphics/GraphicsDevice/GraphicsDevice.hpp>

namespace Strand
{

SamplerState::SamplerState(GraphicsDevice* graphicsDevice,const SamplerStateDesc& desc)
{
    GraphicsDevice_ = graphicsDevice;
    Desc_ = desc;

    D3D11_SAMPLER_DESC samplerDesc = {};
    samplerDesc.Filter = SamplerStateUtils::GetSampleFilter(Desc_.SamplerFilter_);
    samplerDesc.AddressU = SamplerStateUtils::GetTextureAddressMode(Desc_.AddressModeU_);
    samplerDesc.AddressV = SamplerStateUtils::GetTextureAddressMode(Desc_.AddressModeV_);
    samplerDesc.AddressW = SamplerStateUtils::GetTextureAddressMode(Desc_.AddressModeW_);
    samplerDesc.MipLODBias = Desc_.MipLODBias_;
    samplerDesc.MaxAnisotropy = Desc_.MaxAnisotropy_;
    samplerDesc.ComparisonFunc = SamplerStateUtils::GetComparisonFunc(Desc_.ComparisonFunc_);

    for(int i = 0; i < std::size(Desc_.BorderColor_); i++) {
        samplerDesc.BorderColor[i] = Desc_.BorderColor_[i];
    }

    samplerDesc.MinLOD = Desc_.MinLOD_;
    samplerDesc.MaxLOD = Desc_.MaxLOD_;

    DX_PRINT_LOG("Create SamplerState", GraphicsDevice_->GetDevice()->CreateSamplerState(&samplerDesc, SamplerState_.GetAddressOf()));
}

} // Strand