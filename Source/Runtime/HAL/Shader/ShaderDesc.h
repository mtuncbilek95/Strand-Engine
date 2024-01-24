#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/HAL/Shader/ShaderType.h>

namespace Strand
{
    struct RUNTIME_API ShaderDesc
    {
        String ShaderName;
        String EntryName;
        String ShaderModel;
        ShaderType Type;
        String Source;
    };
}
