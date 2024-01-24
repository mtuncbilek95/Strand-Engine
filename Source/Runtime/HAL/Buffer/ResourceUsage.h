#pragma once

#include <Runtime/Core/Core.h>

namespace Strand
{
	enum class RUNTIME_API ResourceUsage : byte
	{
		Default,
		Immutable,
		Dynamic,
		Staging
	};
}
