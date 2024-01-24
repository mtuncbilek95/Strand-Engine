#pragma once

namespace Strand
{
    enum class RUNTIME_API TextureUsage
    {
        Unknown,
        Dynamic,
        Read_Write,
        Scratch,
        Field,
        Shader_Input,
        Render_Target_Output,
        Back_Buffer,
        Shared,
        Read_Only,
        Discard,
        Unordered,
    };
}
