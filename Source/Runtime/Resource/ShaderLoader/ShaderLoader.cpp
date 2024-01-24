#include "ShaderLoader.h"

#include <Windows.h>

#define STRING(x) #x"/"
#define XSTRING(x) STRING(x)

namespace Strand
{
	String GetProjectFolderDirectory()
	{
#ifdef STRAND_DEBUG
		String workingDir = XSTRING(WORKING_ROOT);
		return workingDir;
#else
		char buffer[FILENAME_MAX];
		GetCurrentDirectory(FILENAME_MAX, buffer);
		String data = buffer;
		return data;
#endif
	}

	String ShaderLoader::LoadShader(const String& fileName)
	{
		std::string fullPath = GetProjectFolderDirectory() + "\\Shaders\\" + fileName + ".hlsl";

		HANDLE fileHandle;
		DWORD countByte;

		fileHandle = CreateFileA(fullPath.data(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_READONLY, nullptr);

		const DWORD fileSize = GetFileSize(fileHandle, nullptr);

		char* stringFile = new char[fileSize + 1];
		stringFile[fileSize] = '\0';

		if (ReadFile(fileHandle, stringFile, fileSize, &countByte, nullptr))
			return stringFile;
		else
			DEV_LOG(SE_ERROR, "ShaderReader", "Failed to read shader file.");

		delete[] stringFile;
		CloseHandle(fileHandle);

		return "";
	}
}
