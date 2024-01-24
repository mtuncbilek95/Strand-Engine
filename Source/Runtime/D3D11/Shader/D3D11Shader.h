#pragma once

#include <Runtime/Core/Core.h>
#include <Runtime/HAL/Shader/Shader.h>

#include <d3d11.h>
#include <wrl.h>
using namespace Microsoft::WRL;

namespace Strand
{
	class RUNTIME_API D3D11Shader : public Shader
	{
	public:
		D3D11Shader(const ShaderDesc& desc, ID3D11Device* pDevice);
		~D3D11Shader() override = default;

		ComPtr<ID3D11VertexShader>& GetVertexShader() { return mVertexShader; }
		ComPtr<ID3D11PixelShader>& GetPixelShader() { return mPixelShader; }
		ComPtr<ID3D11HullShader>& GetHullShader() { return mHullShader; }
		ComPtr<ID3D11DomainShader>& GetDomainShader() { return mDomainShader; }
		ComPtr<ID3D11GeometryShader>& GetGeometryShader() { return mGeometryShader; }
		ComPtr<ID3D11ComputeShader>& GetComputeShader() { return mComputeShader; }

		virtual void* GetDataPointer() noexcept override { return mShaderBlob->GetBufferPointer(); }
		virtual uint64 GetDataSize() noexcept override { return mShaderBlob->GetBufferSize(); }

	private:
		ComPtr<ID3D11VertexShader> mVertexShader;
		ComPtr<ID3D11PixelShader> mPixelShader;
		ComPtr<ID3D11HullShader> mHullShader;
		ComPtr<ID3D11DomainShader> mDomainShader;
		ComPtr<ID3D11GeometryShader> mGeometryShader;
		ComPtr<ID3D11ComputeShader> mComputeShader;

		ComPtr<ID3DBlob> mShaderBlob;

		ID3D11Device* mDevice;
	};
}
