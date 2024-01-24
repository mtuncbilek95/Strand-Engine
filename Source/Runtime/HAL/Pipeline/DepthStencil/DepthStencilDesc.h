#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/HAL/Pipeline/DepthStencil/DepthMask.h>
#include <Runtime/HAL/Pipeline/DepthStencil/DepthStencilComparisonFunc.h>

namespace Strand
{
	struct RUNTIME_API DepthStencilDesc
	{
		bool DepthEnable;
		DepthMask DepthMask;
		DepthStencilComparisonFunc DepthCompFunc;
		bool StencilEnable;
		byte StencilReadMask;
		byte StencilWriteMask;
	};
}
