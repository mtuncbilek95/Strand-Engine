#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/HAL/Device/GraphicsDeviceObject.h>
#include <Runtime/HAL/ResourceLayout/ResourceLayoutDesc.h>

namespace Strand
{
	class RUNTIME_API ResourceLayout : public GraphicsDeviceObject
	{
	public:
		ResourceLayout(const ResourceLayoutDesc& desc) : mTextureViews(desc.TextureViews),
			mSamplers(desc.Samplers), mGraphicsViews(desc.GraphicsViews), mStage(desc.Stage)
		{}
		virtual ~ResourceLayout() override = default;

		virtual void Bind() const noexcept = 0;

		const ArrayList<SharedPtr<TextureView>>& GetTextureViews() const { return mTextureViews; }
		const ArrayList<SharedPtr<Sampler>>& GetSamplers() const { return mSamplers; }
		const ArrayList<SharedPtr<GraphicsBuffer>>& GetGraphicsBuffers() const { return mGraphicsViews; }
		ShaderStage GetStage() const { return mStage; }

		FORCEINLINE GraphicsDeviceObjectType GetDeviceObjectType() const noexcept override final { return GraphicsDeviceObjectType::ResourceLayout; }

		virtual void OnShutdown() override {};

	private:
		ArrayList<SharedPtr<TextureView>> mTextureViews;
		ArrayList<SharedPtr<Sampler>> mSamplers;
		ArrayList<SharedPtr<GraphicsBuffer>> mGraphicsViews;
		ShaderStage mStage;
	};
}
