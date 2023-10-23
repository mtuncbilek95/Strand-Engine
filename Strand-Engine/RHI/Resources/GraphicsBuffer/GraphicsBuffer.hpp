// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <RHI/GraphicsDevice/DeviceObject.hpp>
#include <RHI/Resources/GraphicsBuffer/GraphicsBufferDesc.hpp>
namespace Strand
{

class ENGINE_API GraphicsBuffer : public DeviceObject
{
public:

protected:

private:
    GraphicsBufferDesc Desc_;
};

} // Strand
