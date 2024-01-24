#pragma once

#include <Runtime/Core/Core.h>

namespace Strand
{
	enum class RUNTIME_API DepthStencilComparisonFunc : byte
	{
		Never,
		Less,
		Equal,
		LessEqual,
		Greater,
		NotEqual,
		GreaterEqual,
		Always
	};
}
