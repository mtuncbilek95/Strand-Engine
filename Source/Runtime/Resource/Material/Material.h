#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/Resource/TextureResource/TextureResource.h>
#include <Runtime/HAL/Sampler/Sampler.h>
#include <Runtime/HAL/Manager/GraphicsManager.h>
#include <Runtime/HAL/ResourceLayout/ResourceLayout.h>

namespace Strand
{
	class RUNTIME_API Material
	{
	public:
		Material()
		{
			mBaseColor = nullptr;
			mNormal = nullptr;
			mMetallic = nullptr;
			mRoughness = nullptr;
			mAmbientOcclusion = nullptr;
			mEmissive = nullptr;

			SamplerDesc samplerDesc
			{
				.Filter = SamplerFilter::MinMagMipLinear,
				.AddressU = AddressMode::Wrap,
				.AddressV = AddressMode::Wrap,
				.AddressW = AddressMode::Wrap,
				.MipLODBias = 0.0f,
				.MaxAnisotropy = 1,
				.SamplerComparison = SamplerComparison::Never,
				.BorderColor = { 0.0f, 0.0f, 0.0f, 0.0f },
				.MinLOD = 0.0f,
				.MaxLOD = 0.0f
			};

			mSampler = GraphicsManager::GetInstance().GetDevice()->CreateSampler(samplerDesc);
		}
		~Material() = default;

		void SetBaseColor(TextureResult texture) { mBaseColor = std::make_shared<TextureResource>(texture); }
		void SetNormal(TextureResult texture) { mNormal = std::make_shared<TextureResource>(texture); }
		void SetMetallic(TextureResult texture) { mMetallic = std::make_shared<TextureResource>(texture); }
		void SetRoughness(TextureResult texture) { mRoughness = std::make_shared<TextureResource>(texture); }
		void SetAmbientOcclusion(TextureResult texture) { mAmbientOcclusion = std::make_shared<TextureResource>(texture); }
		void SetEmissive(TextureResult texture) { mEmissive = std::make_shared<TextureResource>(texture); }

		SharedPtr<TextureResource> GetBaseColor() const { return mBaseColor; }
		SharedPtr<TextureResource> GetNormal() const { return mNormal; }
		SharedPtr<TextureResource> GetMetallic() const { return mMetallic; }
		SharedPtr<TextureResource> GetRoughness() const { return mRoughness; }
		SharedPtr<TextureResource> GetAmbientOcclusion() const { return mAmbientOcclusion; }
		SharedPtr<TextureResource> GetEmissive() const { return mEmissive; }

		SharedPtr<Sampler> GetSampler() const { return mSampler; }
		SharedPtr<ResourceLayout>& GetPixelLayout() { return mPixelLayout; }

	private:
		SharedPtr<TextureResource> mBaseColor;
		SharedPtr<TextureResource> mNormal;
		SharedPtr<TextureResource> mMetallic;
		SharedPtr<TextureResource> mRoughness;
		SharedPtr<TextureResource> mAmbientOcclusion;
		SharedPtr<TextureResource> mEmissive;
		SharedPtr<Sampler> mSampler;

		SharedPtr<ResourceLayout> mPixelLayout;


	};
}
