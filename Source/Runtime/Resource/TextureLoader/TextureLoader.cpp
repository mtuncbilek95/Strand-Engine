#include "TextureLoader.h"

#include <stb_image.h>

namespace Strand
{
	TextureResult TextureLoader::LoadTexture(const String& path)
	{
		TextureResult result;

		result.Data = stbi_load(path.c_str(), &result.Size.x, &result.Size.y, &result.Size.z, STBI_rgb_alpha);

		DEV_ASSERT(result.Data != nullptr, "TextureLoader", "Failed to load texture: %s", path.c_str());

		return result;
	}
}
