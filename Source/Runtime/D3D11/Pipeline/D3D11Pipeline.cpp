#include "D3D11Pipeline.h"

#include <Runtime/D3D11/Texture/D3D11TextureUtils.h>
#include <Runtime/D3D11/Pipeline/D3D11PipelineUtils.h>
#include <Runtime/D3D11/Sampler/D3D11Sampler.h>

namespace Strand
{
	D3D11Pipeline::D3D11Pipeline(const GraphicsPipelineDesc& desc, ID3D11Device* pDevice) : Pipeline(desc)
	{
		mDevice = pDevice;

		// Get SamplerState from desc
		if (desc.Sampler)
		{
			mSamplerState = static_cast<D3D11Sampler*>(desc.Sampler.get())->GetSamplerState();
			DEV_LOG(SE_INFO, "D3D11Pipeline", "SamplerState has been set");
		}

		ArrayList<D3D11_INPUT_ELEMENT_DESC> inputElements;

		// Create input layout
		for (auto& input : desc.InputLayout)
		{
			D3D11_INPUT_ELEMENT_DESC inputElement = {};

			switch (input.SemanticName)
			{
			case SemanticName::Position:
				inputElement.SemanticName = "POSITION";
				break;
			case SemanticName::Normal:
				inputElement.SemanticName = "NORMAL";
				break;
			case SemanticName::Tangent:
				inputElement.SemanticName = "TANGENT";
				break;
			case SemanticName::BiNormal:
				inputElement.SemanticName = "BINORMAL";
				break;
			case SemanticName::Color:
				inputElement.SemanticName = "COLOR";
				break;
			case SemanticName::TexCoord:
				inputElement.SemanticName = "TEXCOORD";
				break;
			default: break;
			}

			inputElement.SemanticIndex = input.SemanticIndex;
			inputElement.Format = D3D11TextureUtils::GetDXTextureFormat(input.InputFormat);
			inputElement.InputSlot = input.InputSlotIndex;
			inputElement.AlignedByteOffset = input.AlignedByteOffset;
			inputElement.InputSlotClass = D3D11PipelineUtils::GetInputClassification(input.SlotClass);
			inputElement.InstanceDataStepRate = input.InstanceDataStep;

			inputElements.push_back(inputElement);
		}

		// Create input layout according to vertex shader
		DEV_ASSERT(SUCCEEDED(mDevice->CreateInputLayout(inputElements.data(), inputElements.size(), GetShader(ShaderType::Vertex)->GetDataPointer(),
			GetShader(ShaderType::Vertex)->GetDataSize(), mInputLayout.GetAddressOf())), "D3D11Pipeline", "Failed to create input layout");

		DEV_LOG(SE_VERBOSE, "Created InputLayout of D3D11Pipeline");

		// Create rasterizer state
		D3D11_RASTERIZER_DESC rasterizerDesc = {};
		rasterizerDesc.FillMode = D3D11PipelineUtils::GetFillMode(desc.Rasterizer.FillMode);
		rasterizerDesc.CullMode = D3D11PipelineUtils::GetCullMode(desc.Rasterizer.CullMode);
		rasterizerDesc.FrontCounterClockwise = D3D11PipelineUtils::GetFaceOrdering(desc.Rasterizer.FaceOrdering);
		rasterizerDesc.DepthBias = desc.Rasterizer.DepthBias;
		rasterizerDesc.DepthBiasClamp = desc.Rasterizer.DepthClamp;
		rasterizerDesc.SlopeScaledDepthBias = desc.Rasterizer.SlopeScaledDepthBias;
		rasterizerDesc.DepthClipEnable = desc.Rasterizer.DepthClipEnabled;
		rasterizerDesc.ScissorEnable = desc.Rasterizer.ScissorEnabled;
		rasterizerDesc.MultisampleEnable = desc.Rasterizer.MultisampleEnabled;
		rasterizerDesc.AntialiasedLineEnable = desc.Rasterizer.AntialiasedLineEnabled;

		DEV_ASSERT(SUCCEEDED(mDevice->CreateRasterizerState(&rasterizerDesc, mRasterizerState.GetAddressOf())), "D3D11Pipeline",
			"Failed to create rasterizer state");

		DEV_LOG(SE_VERBOSE, "Created RasterizerState of D3D11Pipeline");

		// Create depth stencil state
		D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};
		depthStencilDesc.DepthEnable = desc.DepthStencil.DepthEnable;
		depthStencilDesc.DepthWriteMask = D3D11PipelineUtils::GetDepthWriteMask(desc.DepthStencil.DepthMask);
		depthStencilDesc.DepthFunc = D3D11PipelineUtils::GetComparisonFunc(desc.DepthStencil.DepthCompFunc);
		depthStencilDesc.StencilEnable = desc.DepthStencil.StencilEnable;
		depthStencilDesc.StencilReadMask = desc.DepthStencil.StencilReadMask;
		depthStencilDesc.StencilWriteMask = desc.DepthStencil.StencilWriteMask;

		DEV_ASSERT(SUCCEEDED(mDevice->CreateDepthStencilState(&depthStencilDesc, mDepthStencilState.GetAddressOf())), "D3D11Pipeline",
			"Failed to create depth stencil state");

		DEV_LOG(SE_VERBOSE, "Created DepthStencilState of D3D11Pipeline");

		// Create blend state
		D3D11_RENDER_TARGET_BLEND_DESC renderTargetBlendDesc = {};
		renderTargetBlendDesc.BlendEnable = desc.Blend.RenderTargetBlendDesc.BlendEnable;
		renderTargetBlendDesc.SrcBlend = D3D11PipelineUtils::GetBlendFactor(desc.Blend.RenderTargetBlendDesc.SrcBlend);
		renderTargetBlendDesc.DestBlend = D3D11PipelineUtils::GetBlendFactor(desc.Blend.RenderTargetBlendDesc.DestBlend);
		renderTargetBlendDesc.BlendOp = D3D11PipelineUtils::GetBlendOp(desc.Blend.RenderTargetBlendDesc.BlendOp);
		renderTargetBlendDesc.SrcBlendAlpha = D3D11PipelineUtils::GetBlendFactor(desc.Blend.RenderTargetBlendDesc.SrcBlendAlpha);
		renderTargetBlendDesc.DestBlendAlpha = D3D11PipelineUtils::GetBlendFactor(desc.Blend.RenderTargetBlendDesc.DestBlendAlpha);
		renderTargetBlendDesc.BlendOpAlpha = D3D11PipelineUtils::GetBlendOp(desc.Blend.RenderTargetBlendDesc.BlendOpAlpha);
		renderTargetBlendDesc.RenderTargetWriteMask = D3D11PipelineUtils::GetColorWriteMask(desc.Blend.RenderTargetBlendDesc.ColorWriteMask);

		D3D11_BLEND_DESC blendDesc = {};
		blendDesc.AlphaToCoverageEnable = desc.Blend.AlphaToCoverageEnable;
		blendDesc.IndependentBlendEnable = desc.Blend.IndependentBlendEnable;
		blendDesc.RenderTarget[0] = renderTargetBlendDesc;

		DEV_ASSERT(SUCCEEDED(mDevice->CreateBlendState(&blendDesc, mBlendState.GetAddressOf())), "D3D11Pipeline", 
			"Failed to create blend state");

		DEV_LOG(SE_VERBOSE, "Created BlendState of D3D11Pipeline");
	}
}