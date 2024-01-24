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
		ArrayList<SemanticName> SemanticNames;
		ArrayList<TextureFormat> InputFormats;
		ArrayList<uint32> SemanticIndices;
		ArrayList<uint32> InputSlotIndices;
		ArrayList<uint32> AlignedByteOffsets;
		ArrayList<SlotClass> SlotClasses;
		ArrayList<uint32> InstanceDataSteps;
		PrimitiveMode PrimitiveMode;
	};
}
