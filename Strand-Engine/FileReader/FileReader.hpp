// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>


#define STRING(x) #x"/"
#define XSTRING(x) STRING(x)

namespace Strand
{

// @brief Reads files from the folders
class FileReader
{
public:
    // @brief Returns the executable path
    static String GetExecutablePath()
    {
        char buffer[MAX_PATH];
        GetModuleFileNameA(nullptr, buffer, MAX_PATH);

        // Remove the executable name from the path
        for(int i = MAX_PATH - 1; i >= 0; i--) {
            if(buffer[i] == '\\') {
                buffer[i + 1] = '\0';
                break;
            }
        }

        return buffer;
    }

    // @brief This catches the shader data from the Shaders folder which is stored in the executable folder.
    static String GetShaderNearExe(const String& dataName)
    {
        String fullPath = GetExecutablePath();

        fullPath += "Shaders/" + dataName + ".hlsl";

        HANDLE fileHandle;
        DWORD countByte;

        fileHandle = CreateFileA(fullPath.data(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_ALWAYS,
                                 FILE_ATTRIBUTE_READONLY, nullptr);

        const DWORD fileSize = GetFileSize(fileHandle, nullptr);

        char* stringFile = new char[fileSize + 1];
        stringFile[fileSize] = {'\0'};

        if(ReadFile(fileHandle, stringFile, fileSize, &countByte, nullptr)) {
            return stringFile;
        } else
            std::cerr << "Unexpected file or path." << std::endl;

        return "";
    }

    static void CopyFiles(const String& sourcePath, const String& destPath)
    {
        String source = XSTRING(RENDER_ROOT) + sourcePath;
        String dest = GetExecutablePath() + destPath;

        std::filesystem::copy(source, dest, std::filesystem::copy_options::overwrite_existing);
    }
};

} // Strand
