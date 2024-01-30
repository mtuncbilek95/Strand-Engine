#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/Resource/Game/GameObject.h>

namespace Strand
{
	class RUNTIME_API DamagedHelmet : public GameObject
	{
	public:
		DamagedHelmet();
		~DamagedHelmet() = default;

		virtual void Start() override;
		virtual void Update() override;
		virtual void Stop() override;
	};
}
