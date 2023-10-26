// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <iostream>

namespace Strand
{

#define STRAND_ERROR_ASSERT(condition, message)                     \
    if (!(condition))                                               \
    {                                                               \
        std::cerr << "Assertion failed: " << message << std::endl;  \
        std::terminate();                                           \
    }

} // Strand
