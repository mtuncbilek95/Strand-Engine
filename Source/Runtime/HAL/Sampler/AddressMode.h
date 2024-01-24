#pragma once

#include <Runtime/Core/Core.h>

namespace Strand
{
    enum class RUNTIME_API AddressMode : byte
    {
        Wrap,
        Mirror,
        Clamp,
        Border,
        MirrorOnce
    };
}
