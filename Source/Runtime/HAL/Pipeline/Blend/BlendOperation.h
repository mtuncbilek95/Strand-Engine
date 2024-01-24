#pragma once

#include <Runtime/Core/Core.h>

namespace Strand
{
	enum class RUNTIME_API BlendOperation : byte
	{
		Add,
		Subtract,
		ReverseSubtract,
		Min,
		Max
	};
}
