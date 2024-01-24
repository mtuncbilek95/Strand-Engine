#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/HAL/Device/GraphicsDeviceObject.h>

#include <Runtime/HAL/Sampler/SamplerDesc.h>

namespace Strand
{
	class RUNTIME_API Sampler : public GraphicsDeviceObject
	{
	public:
		Sampler(const SamplerDesc& desc) : mFilter(desc.Filter), mAddressU(desc.AddressU), 
			mAddressV(desc.AddressV), mAddressW(desc.AddressW), mMipLODBias(desc.MipLODBias), 
			mMaxAnisotropy(desc.MaxAnisotropy), mSamplerComparison(desc.SamplerComparison), 
			mMinLOD(desc.MinLOD), mMaxLOD(desc.MaxLOD)
		{
			mBorderColor[0] = desc.BorderColor[0];
			mBorderColor[1] = desc.BorderColor[1];
			mBorderColor[2] = desc.BorderColor[2];
			mBorderColor[3] = desc.BorderColor[3];
		}
		virtual ~Sampler() override = default;

		FORCEINLINE SamplerFilter GetFilter() const noexcept { return mFilter; }
		FORCEINLINE AddressMode GetAddressU() const noexcept { return mAddressU; }
		FORCEINLINE AddressMode GetAddressV() const noexcept { return mAddressV; }
		FORCEINLINE AddressMode GetAddressW() const noexcept { return mAddressW; }
		FORCEINLINE float GetMipLODBias() const noexcept { return mMipLODBias; }
		FORCEINLINE uint32 GetMaxAnisotropy() const noexcept { return mMaxAnisotropy; }
		FORCEINLINE SamplerComparison GetSamplerComparison() const noexcept { return mSamplerComparison; }
		FORCEINLINE const float* GetBorderColor() const noexcept { return mBorderColor; }
		FORCEINLINE float GetMinLOD() const noexcept { return mMinLOD; }
		FORCEINLINE float GetMaxLOD() const noexcept { return mMaxLOD; }

		FORCEINLINE GraphicsDeviceObjectType GetDeviceObjectType() const noexcept override final { return GraphicsDeviceObjectType::Sampler; }

		virtual void OnShutdown() override {};

	private:
		SamplerFilter mFilter;
		AddressMode mAddressU;
		AddressMode mAddressV;
		AddressMode mAddressW;
		float mMipLODBias;
		uint32 mMaxAnisotropy;
		SamplerComparison mSamplerComparison;
		float mBorderColor[4];
		float mMinLOD;
		float mMaxLOD;
	};
}
