#pragma once

#include <Runtime/Core/Core.h>

namespace Strand
{
	class Mesh;
	class Scene;

	class RUNTIME_API MeshLoader
	{
	public:
		static void LoadSingleMesh(const String& path, SharedPtr<Mesh>& mesh);
		static void LoadScene(const String& path, SharedPtr<Scene>& scene);

	public:
		MeshLoader() = delete;
		~MeshLoader() = delete;
	};
}
