// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Graphics/GraphicsDevice/DeviceObject.hpp>
#include <Graphics/Resources/GraphicsBuffer/GraphicsBufferDesc.hpp>

namespace Strand
{

class GraphicsDevice;

class STRAND_API GraphicsBuffer : public DeviceObject
{
public:
    GraphicsBuffer(GraphicsDevice* device, const GraphicsBufferDesc& desc);
    GraphicsBuffer(const GraphicsBuffer&) = delete;
    GraphicsBuffer& operator=(const GraphicsBuffer&) = delete;
    ~GraphicsBuffer() override = default;

    DeviceObjectType GetDeviceObjectType() override
    { return DeviceObjectType::BUFFER; }

    DXHEAP<ID3D11Buffer>& GetBuffer()
    { return Buffer_; }

    GraphicsBufferDesc& GetDesc()
    { return Desc_; }

private:
    GraphicsBufferDesc Desc_;
    DXHEAP<ID3D11Buffer> Buffer_;
};

} // Strand
