#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/HAL/Pipeline/Rasterizer/FillMode.h>
#include <Runtime/HAL/Pipeline/Rasterizer/CullMode.h>
#include <Runtime/HAL/Pipeline/Rasterizer/FaceOrdering.h>

namespace Strand
{
	struct RUNTIME_API RasterizerDesc
	{
		FillMode FillMode;
		CullMode CullMode;
		FaceOrdering FaceOrdering;
		int DepthBias;
		float DepthClamp;
		float SlopeScaledDepthBias;
		bool DepthClipEnabled;
		bool ScissorEnabled;
		bool MultisampleEnabled;
		bool AntialiasedLineEnabled;
	};
}
