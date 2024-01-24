#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/HAL/Buffer/BufferCPUAccess.h>
#include <Runtime/HAL/Buffer/BufferUsage.h>
#include <Runtime/HAL/Buffer/ResourceUsage.h>

namespace Strand
{
	struct RUNTIME_API GraphicsBufferDesc
	{
		BufferUsage Usage;
		BufferCPUAccess CPUAccess;
		ResourceUsage ResourceUsage;
		uint8 MiscFlags;
		uint32 SizeInBytes;
		uint64 StructureByteStride;

		void* InitialData;
	};
}
