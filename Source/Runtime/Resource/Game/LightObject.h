#pragma once

#include <Runtime/Core/Core.h>

namespace Strand
{
	enum class RUNTIME_API LightType
	{
		Ambient,
		Directional,
		Point,
		Spot
	};

	struct RUNTIME_API AmbientLightObject
	{
		XMVECTOR cameraPosition;

        XMVECTOR ambientColor;
		XMVECTOR ambientIntensity;

		XMVECTOR lightColor;
		XMVECTOR lightPosition;
		XMVECTOR lightIntensity;
	};

    struct RUNTIME_API DirectionalLightObject
    {
		Vector3f lightColor;
		float lightIntensity;
		Vector3f lightDirection;

		LightType lightType = LightType::Directional;
	};

	struct RUNTIME_API PointLightObject
	{
		Vector3f lightColor;
		float lightIntensity;
		Vector3f lightPosition;
		float lightRadius;

		LightType lightType = LightType::Point;

	};

	struct RUNTIME_API SpotLightObject
	{
		Vector3f lightColor;
		float lightIntensity;
		Vector3f lightPosition;
		float lightRadius;
		Vector3f lightDirection;
		float lightAngle;

		LightType lightType = LightType::Spot;
	};

	
}
