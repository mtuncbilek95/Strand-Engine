#pragma once

#include <Runtime/Core/Core.h>
#include <Runtime/HAL/Device/GraphicsDeviceObject.h>

#include <Runtime/HAL/Pipeline/GraphicsPipelineDesc.h>

namespace Strand
{
	class RUNTIME_API Pipeline : public GraphicsDeviceObject
	{
	public:
		Pipeline(const GraphicsPipelineDesc& desc) : mInputLayout(desc.InputLayout), mRasterizer(desc.Rasterizer),
			mDepthStencil(desc.DepthStencil), mBlend(desc.Blend), mSampler(desc.Sampler), mShaders(desc.Shaders) 
		{
		}
		virtual ~Pipeline() override = default;

		SharedPtr<Shader> GetShader(ShaderType type) const noexcept
		{
			for (const auto& shader : mShaders)
			{
				if (shader->GetShaderType() == type)
					return shader;
			}

			return nullptr;
		}

		const InputLayoutDesc& GetInputLayout() const noexcept { return mInputLayout; }
		const RasterizerDesc& GetRasterizer() const noexcept { return mRasterizer; }
		const DepthStencilDesc& GetDepthStencil() const noexcept { return mDepthStencil; }
		const BlendStateDesc& GetBlend() const noexcept { return mBlend; }
		const SharedPtr<Sampler>& GetSampler() const noexcept { return mSampler; }

		FORCEINLINE GraphicsDeviceObjectType GetDeviceObjectType() const noexcept override { return GraphicsDeviceObjectType::Pipeline; }

		virtual void OnShutdown() override {};

	private:
		ArrayList<SharedPtr<Shader>> mShaders;
		InputLayoutDesc mInputLayout;
		RasterizerDesc mRasterizer;
		DepthStencilDesc mDepthStencil;
		BlendStateDesc mBlend;
		SharedPtr<Sampler> mSampler;
	};
}
