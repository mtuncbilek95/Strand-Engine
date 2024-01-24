#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/HAL/Device/GraphicsDevice.h>
#include <Runtime/Manager/ManagerAPI.h>

namespace Strand
{
	class RUNTIME_API GraphicsManager : public ManagerAPI<GraphicsManager>
	{
	public:
		GraphicsManager() = default;
		~GraphicsManager() = default;

		SharedPtr<GraphicsDevice> CreateDevice(const GraphicsDeviceDesc& desc)
		{
			if (mDevice == nullptr)
				mDevice = SharedPtr<GraphicsDevice>(GraphicsDevice::CreateDevice(desc));
			return mDevice;
		}

		SharedPtr<GraphicsDevice>& GetDevice() { return mDevice; }

	private:
		SharedPtr<GraphicsDevice> mDevice;
	};
}
