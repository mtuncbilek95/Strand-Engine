#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/HAL/Pipeline/InputLayout/SemanticName.h>
#include <Runtime/HAL/Pipeline/InputLayout/SlotClass.h>
#include <Runtime/HAL/Pipeline/InputLayout/PrimitiveMode.h>

#include <Runtime/HAL/Texture/TextureFormat.h>

namespace Strand
{
	struct RUNTIME_API InputLayoutDesc
	{
		SemanticName SemanticName;
		TextureFormat InputFormat;
		uint32 SemanticIndex;
		uint32 InputSlotIndex;
		uint32 AlignedByteOffset;
		SlotClass SlotClass;
		uint32 InstanceDataStep;
	};
}
