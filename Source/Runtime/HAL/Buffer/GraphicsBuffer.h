#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/HAL/Device/GraphicsDeviceObject.h>

#include <Runtime/HAL/Buffer/GraphicsBufferDesc.h>

namespace Strand
{
	class RUNTIME_API GraphicsBuffer : public GraphicsDeviceObject
	{
	public:
		GraphicsBuffer(const GraphicsBufferDesc& desc) : Usage(desc.Usage), CPUAccess(desc.CPUAccess), ResourceUsage(desc.ResourceUsage),
			MiscFlags(desc.MiscFlags), SizeInBytes(desc.SizeInBytes), StructureByteStride(desc.StructureByteStride), mData(desc.InitialData) {}
		virtual ~GraphicsBuffer() override = default;

		FORCEINLINE BufferUsage GetUsage() const noexcept { return Usage; }
		FORCEINLINE BufferCPUAccess GetCPUAccess() const noexcept { return CPUAccess; }
		FORCEINLINE ResourceUsage GetResourceUsage() const noexcept { return ResourceUsage; }
		FORCEINLINE uint8 GetMiscFlags() const noexcept { return MiscFlags; }
		FORCEINLINE uint32 GetSizeInBytes() const noexcept { return SizeInBytes; }
		FORCEINLINE uint64 GetStructureByteStride() const noexcept { return StructureByteStride; }

		FORCEINLINE void* GetData() const noexcept { return mData; }

		FORCEINLINE GraphicsDeviceObjectType GetDeviceObjectType() const noexcept override { return GraphicsDeviceObjectType::GraphicsBuffer; }

		virtual void OnShutdown() override {};

	private:
		BufferUsage Usage;
		BufferCPUAccess CPUAccess;
		ResourceUsage ResourceUsage;
		uint8 MiscFlags;
		uint32 SizeInBytes;
		uint64 StructureByteStride;

		void* mData;
	};

}
