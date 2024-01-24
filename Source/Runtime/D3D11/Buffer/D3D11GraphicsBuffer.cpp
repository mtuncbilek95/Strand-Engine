#include "D3D11GraphicsBuffer.h"

#include <Runtime/D3D11/Buffer/D3D11BufferUtils.h>

namespace Strand
{
	D3D11GraphicsBuffer::D3D11GraphicsBuffer(const GraphicsBufferDesc& desc, ID3D11Device* pDevice) : GraphicsBuffer(desc)
	{
		mDevice = pDevice;

		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.Usage = D3D11BufferUtils::GetResourceUsage(desc.ResourceUsage);
		bufferDesc.BindFlags = D3D11BufferUtils::GetBufferUsage(desc.Usage);
		bufferDesc.CPUAccessFlags = D3D11BufferUtils::GetBufferCPUAccess(desc.CPUAccess);
		bufferDesc.MiscFlags = desc.MiscFlags;
		bufferDesc.ByteWidth = desc.SizeInBytes;
		bufferDesc.StructureByteStride = desc.StructureByteStride;


		D3D11_SUBRESOURCE_DATA subresourceData = {};
		subresourceData.pSysMem = desc.InitialData;

		DEV_ASSERT(SUCCEEDED(mDevice->CreateBuffer(&bufferDesc, desc.InitialData ? &subresourceData : nullptr, mBuffer.GetAddressOf())), 
			"D3D11GraphicsBuffer", "Failed to create D3D11GraphicsBuffer");
	}
}
