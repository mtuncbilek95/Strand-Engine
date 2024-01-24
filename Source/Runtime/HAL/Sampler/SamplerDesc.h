#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/HAL/Sampler/SamplerFilter.h>
#include <Runtime/HAL/Sampler/AddressMode.h>
#include <Runtime/HAL/Sampler/SamplerComparison.h>

namespace Strand
{
	struct RUNTIME_API SamplerDesc
	{
		SamplerFilter Filter;
		AddressMode AddressU;
		AddressMode AddressV;
		AddressMode AddressW;
		float MipLODBias;
		uint32 MaxAnisotropy;
		SamplerComparison SamplerComparison;
		float BorderColor[4];
		float MinLOD;
		float MaxLOD;
	};
}
