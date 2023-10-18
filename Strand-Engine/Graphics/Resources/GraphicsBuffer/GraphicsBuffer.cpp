// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#include "GraphicsBuffer.hpp"

#include <Common/Log.hpp>
#include <Graphics/GraphicsDevice/GraphicsDevice.hpp>

namespace Strand
{

GraphicsBuffer::GraphicsBuffer(std::shared_ptr<GraphicsDevice> device, const GraphicsBufferDesc& desc)
{
    GraphicsDevice_ = device;
    Desc_ = desc;

    D3D11_BUFFER_DESC bufferDesc{};

    if(Desc_.ByteWidth % 64 == 0) {
        bufferDesc.ByteWidth = Desc_.ByteWidth;
    }
    else {
        bufferDesc.ByteWidth = Desc_.ByteWidth + (64 - Desc_.ByteWidth % 64);
    }

    bufferDesc.Usage = ResourceUtils::GetResourceUsage(Desc_.Usage);
    bufferDesc.BindFlags = ResourceUtils::GetResourceBindFlag(Desc_.BindFlags);
    bufferDesc.CPUAccessFlags = ResourceUtils::GetResourceCPUAccessFlag(Desc_.CPUAccessFlags);
    bufferDesc.MiscFlags = Desc_.MiscFlags;
    bufferDesc.StructureByteStride = Desc_.StructureByteStride;

    D3D11_SUBRESOURCE_DATA subresourceData{};
    subresourceData.pSysMem = Desc_.CPUData;

    DX_PRINT_LOG("Create Buffer", GraphicsDevice_->GetDevice()->CreateBuffer(&bufferDesc, &subresourceData, Buffer_.GetAddressOf()));
}

} // Strand