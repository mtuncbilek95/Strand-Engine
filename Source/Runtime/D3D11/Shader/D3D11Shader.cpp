#include "D3D11Shader.h"

#include <d3dcompiler.h>

namespace Strand
{
	D3D11Shader::D3D11Shader(const ShaderDesc& desc, ID3D11Device* pDevice) : Shader(desc)
	{
		mDevice = pDevice;

		ComPtr<ID3DBlob> errorBlob = {};

		D3DCompile(desc.Source.data(), desc.Source.length(), nullptr, nullptr, nullptr, desc.EntryName.c_str(),
			desc.ShaderModel.c_str(), D3DCOMPILE_ENABLE_STRICTNESS, 0, mShaderBlob.GetAddressOf(), errorBlob.GetAddressOf());

		if (errorBlob.Get() != nullptr && errorBlob->GetBufferPointer() != nullptr)
		{
			DEV_LOG(SE_ERROR, "Shader", "Failed to compile shader: %s", (char*)errorBlob->GetBufferPointer());
		}

		switch (desc.Type)
		{
		case ShaderType::Vertex:
		{
			DEV_ASSERT(SUCCEEDED(mDevice->CreateVertexShader(mShaderBlob->GetBufferPointer(), mShaderBlob->GetBufferSize(), nullptr, mVertexShader.GetAddressOf())), "D3D11Shader",
				"Failed to create vertex shader %s", desc.ShaderName.c_str());
			break;
		}
		case ShaderType::Pixel:
		{
			DEV_ASSERT(SUCCEEDED(mDevice->CreatePixelShader(mShaderBlob->GetBufferPointer(), mShaderBlob->GetBufferSize(), nullptr, mPixelShader.GetAddressOf())), "D3D11Shader",
				"Failed to create pixel shader %s", desc.ShaderName.c_str());
			break;
		}
		case ShaderType::Geometry:
		{
			DEV_ASSERT(SUCCEEDED(mDevice->CreateGeometryShader(mShaderBlob->GetBufferPointer(), mShaderBlob->GetBufferSize(), nullptr, mGeometryShader.GetAddressOf())), "D3D11Shader",
				"Failed to create geometry shader %s", desc.ShaderName.c_str());
			break;
		}
		case ShaderType::Domain:
		{
			DEV_ASSERT(SUCCEEDED(mDevice->CreateDomainShader(mShaderBlob->GetBufferPointer(), mShaderBlob->GetBufferSize(), nullptr, mDomainShader.GetAddressOf())), "D3D11Shader",
				"Failed to create domain shader %s", desc.ShaderName.c_str());
			break;
		}
		case ShaderType::Hull:
		{
			DEV_ASSERT(SUCCEEDED(mDevice->CreateHullShader(mShaderBlob->GetBufferPointer(), mShaderBlob->GetBufferSize(), nullptr, mHullShader.GetAddressOf())), "D3D11Shader",
				"Failed to create hull shader %s", desc.ShaderName.c_str());
			break;
		}
		case ShaderType::Compute:
		{
			DEV_ASSERT(SUCCEEDED(mDevice->CreateComputeShader(mShaderBlob->GetBufferPointer(), mShaderBlob->GetBufferSize(), nullptr, mComputeShader.GetAddressOf())), "D3D11Shader",
				"Failed to create compute shader %s", desc.ShaderName.c_str());
			break;
		}
		default:
			DEV_LOG(SE_WARNING, "Invalid shader type %d", desc.Type);
			break;
		}

		DEV_LOG(SE_INFO, "Created shader %s", desc.ShaderName.c_str());
	}
}
