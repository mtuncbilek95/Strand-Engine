#pragma once

#include <Runtime/Core/Core.h>
#include <Runtime/HAL/Buffer/GraphicsBuffer.h>

#include <d3d11.h>
#include <wrl.h>
using namespace Microsoft::WRL;

namespace Strand
{
	class RUNTIME_API D3D11GraphicsBuffer : public GraphicsBuffer
	{
	public:
		D3D11GraphicsBuffer(const GraphicsBufferDesc& desc, ID3D11Device* pDevice);
		~D3D11GraphicsBuffer() override = default;

		ComPtr<ID3D11Buffer>& GetBuffer() { return mBuffer; }

		void OnShutdown() override {};
	private:
		ComPtr<ID3D11Buffer> mBuffer;

		ID3D11Device* mDevice;
		ID3D11DeviceContext* mD3D11Context;
	};
}
