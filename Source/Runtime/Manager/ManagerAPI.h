#pragma once

#include <Runtime/Core/Core.h>

namespace Strand
{
	/**
	 * @class ManagerAPI
	 *
	 * @brief Highly protected dynamic singleton class for Low Level
	 * Abstraction Layers.
	 */
	template<typename T>
	class RUNTIME_API ManagerAPI
	{
	public:
		static T& GetInstance()
		{
			static T instance;
			return instance;
		}

	public:
		ManagerAPI() = default;
		~ManagerAPI() = default;
	};
}