#pragma once

#include <Runtime/Core/Core.h>
#include <Runtime/HAL/Device/GraphicsDeviceObject.h>

#include <Runtime/HAL/Texture/TextureDesc.h>

namespace Strand
{
	class RUNTIME_API Texture : public GraphicsDeviceObject
	{
	public:
		Texture(const TextureDesc& desc) : mSize(desc.Size), mMipLevels(desc.MipLevels), 
			mArraySize(desc.ArraySize), mFormat(desc.Format), mUsage(desc.Usage), mType(desc.Type),
			mData(desc.RawData)
		{
		}
		virtual ~Texture() override = default;

		NODISCARD Vector3u GetSize() const noexcept { return mSize; }
		NODISCARD uint32 GetMipLevels() const noexcept { return mMipLevels; }
		NODISCARD uint32 GetArraySize() const noexcept { return mArraySize; }
		NODISCARD TextureFormat GetFormat() const noexcept { return mFormat; }
		NODISCARD TextureUsage GetUsage() const noexcept { return mUsage; }
		NODISCARD byte* GetRawData() const noexcept { return mData; }

		FORCEINLINE GraphicsDeviceObjectType GetDeviceObjectType() const noexcept override { return GraphicsDeviceObjectType::Texture; }

		virtual void OnShutdown() override {};

	private:
		Vector3u mSize;
		uint32 mMipLevels;
		uint32 mArraySize;
		TextureFormat mFormat;
		TextureUsage mUsage;
		TextureType mType;

		byte* mData;

	};
}
