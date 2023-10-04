// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>

#define DX_PRINT_LOG(name, functionResult)                      \
    do {                                                        \
        Strand::SystemLog::PrintError(name, functionResult);    \
    } while (0)


namespace Strand::SystemLog
{

static void PrintError(const std::string& functionName, HRESULT hr)
{
    if(FAILED(hr))
        std::cerr << "[GRAPHICS API ERROR] -- " << functionName.c_str() << " -- This operation has been failed. Please check your operation components.\n" << std::endl;
    else
        std::cout << "[GRAPHICS API SUCCESS] -- " << functionName.c_str() << " -- This operation has been completed successfully." << std::endl;
}

}

// Strand
