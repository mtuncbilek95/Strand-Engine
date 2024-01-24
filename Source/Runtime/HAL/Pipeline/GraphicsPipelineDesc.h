#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/HAL/Shader/Shader.h>
#include <Runtime/HAL/Pipeline/InputLayout/InputLayoutDesc.h>
#include <Runtime/HAL/Pipeline/Rasterizer/RasterizerDesc.h>
#include <Runtime/HAL/Pipeline/DepthStencil/DepthStencilDesc.h>
#include <Runtime/HAL/Pipeline/Blend/BlendStateDesc.h>
#include <Runtime/HAL/Sampler/Sampler.h>

namespace Strand
{
	struct RUNTIME_API GraphicsPipelineDesc
	{
		ArrayList<SharedPtr<Shader>> Shaders;
		InputLayoutDesc InputLayout;
		RasterizerDesc Rasterizer;
		DepthStencilDesc DepthStencil;
		BlendStateDesc Blend;
		SharedPtr<Sampler> Sampler;
	};
}
