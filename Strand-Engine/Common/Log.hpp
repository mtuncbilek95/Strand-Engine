// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>

#define DX11_API_ON_USE

#define DX_PRINT_LOG(name, functionResult)                      \
    do {                                                        \
        Strand::SystemLog::PrintError(name, functionResult);    \
    } while (0)


namespace Strand::SystemLog
{
// @brief Prints error message to the console.
// @param functionName Name of the function that you want to print error message.
// @param hr HRESULT value of the function that you want to print error message.
static void PrintError(const String& functionName, int64_t hr) // TODO: Make it platform specific.
{

#if defined(DX11_API_ON_USE)

    if(FAILED(hr))
        std::cerr << "[GRAPHICS API ERROR] -- " << functionName.c_str() << " -- This operation has been failed. Please check your operation components.\n" << std::endl;
    else
        std::cout << "[GRAPHICS API SUCCESS] -- " << functionName.c_str() << " -- This operation has been completed successfully." << std::endl;

#elif defined(VULKAN_API_ON_USE)
#elif defined(GNMX_API_ON_USE)
#endif

}

}

// Strand
