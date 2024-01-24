#pragma once

#include <Runtime/Core/Core.h>

namespace Strand
{
	enum class RUNTIME_API BufferCPUAccess : byte
	{
		None,
		Read,
		Write
	};
}
