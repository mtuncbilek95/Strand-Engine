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
		String fullPath = GetProjectFolderDirectory() + "\\Shaders\\" + fileName + ".hlsl";

		HANDLE fileHandle;
		DWORD countByte;

		fileHandle = CreateFileA(fullPath.data(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_READONLY, nullptr);

		const DWORD fileSize = GetFileSize(fileHandle, nullptr);

		String fileSource;
		fileSource.resize(fileSize);

		if (ReadFile(fileHandle, fileSource.data(), fileSize, &countByte, nullptr))
			return fileSource;
		else
			DEV_LOG(SE_ERROR, "ShaderReader", "Failed to read shader file.");

		CloseHandle(fileHandle);

		return "";
	}
}
