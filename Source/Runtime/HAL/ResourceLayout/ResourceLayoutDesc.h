#pragma once

#include <Runtime/Core/Core.h>
#include <Runtime/HAL/Shader/ShaderStage.h>
#include <Runtime/HAL/Texture/TextureView.h>
#include <Runtime/HAL/Buffer/GraphicsBuffer.h>
#include <Runtime/HAL/Sampler/Sampler.h>

namespace Strand
{
	struct RUNTIME_API ResourceLayoutDesc
	{
		ArrayList<SharedPtr<TextureView>> TextureViews;
		ArrayList<SharedPtr<Sampler>> Samplers;
		ArrayList<SharedPtr<GraphicsBuffer>> GraphicsViews;
		ShaderStage Stage;
	};
}
