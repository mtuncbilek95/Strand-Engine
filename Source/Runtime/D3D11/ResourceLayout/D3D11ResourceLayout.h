#pragma once

#include <Runtime/Core/Core.h>
#include <Runtime/HAL/ResourceLayout/ResourceLayout.h>

#include <d3d11.h>

namespace Strand
{
	class RUNTIME_API D3D11ResourceLayout : public ResourceLayout
	{
	public:
		D3D11ResourceLayout(const ResourceLayoutDesc& desc, ID3D11Device* pDevice);
		virtual ~D3D11ResourceLayout() override = default;

		virtual void Bind() const noexcept override;
	private:
		ID3D11Device* mD3D11Device;
		ID3D11DeviceContext* mD3D11Context;
	};
}
