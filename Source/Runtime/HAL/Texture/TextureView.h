#pragma once

#include <Runtime/Core/Core.h>
#include <Runtime/HAL/Device/GraphicsDeviceObject.h>

#include <Runtime/HAL/Texture/TextureViewDesc.h>

namespace Strand
{
	class RUNTIME_API TextureView : public GraphicsDeviceObject
	{
	public:
		TextureView(const TextureViewDesc& desc) : mArraySize(desc.ArraySize), mMipLevels(desc.MipLevels),
		mTexture(desc.pTexture) 
		{
		}

		virtual ~TextureView() override = default;

		uint32 GetArraySize() const noexcept { return mArraySize; }
		uint32 GetMipLevels() const noexcept { return mMipLevels; }
		SharedPtr<Texture> GetTexture() const noexcept { return mTexture; }

		FORCEINLINE GraphicsDeviceObjectType GetDeviceObjectType() const noexcept override { return GraphicsDeviceObjectType::TextureView; }

		virtual void OnShutdown() override {};

	private:
		uint32 mArraySize;
		uint32 mMipLevels;
		SharedPtr<Texture> mTexture;
	};
}