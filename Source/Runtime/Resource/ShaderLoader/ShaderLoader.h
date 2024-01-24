#pragma once

#include <Runtime/Core/Core.h>

namespace Strand
{
	class RUNTIME_API ShaderLoader
	{
	public:
		static String LoadShader(const String& path);
	
	public:
		ShaderLoader() = delete;
		~ShaderLoader() = delete;
	};
}
