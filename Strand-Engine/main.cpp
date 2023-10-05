#include <Window/Window.hpp>

#include <FileReader/FileReader.hpp>
#include <Graphics/Utils/DxgiUtils.hpp>

#include <Graphics/GraphicsDevice/GraphicsDevice.hpp>
#include <Graphics/Swapchain/Swapchain.hpp>
#include <Graphics/Framebuffer/Framebuffer.hpp>
#include <Graphics/Resources/GraphicsTextureView/GraphicsTextureView.hpp>
#include <Graphics/Command/CommandList.hpp>
#include <Graphics/Resources/SamplerState/SamplerState.hpp>
#include <Graphics/Shader/Shader.hpp>
#include <Graphics/Pipeline/Pipeline.hpp>
#include <Graphics/Resources/GraphicsBuffer/GraphicsBuffer.hpp>

#include <Graphics/Pipeline/InputLayout/InputLayout.hpp>
#include <Graphics/Pipeline/DepthStencil/DepthStencil.hpp>
#include <Graphics/Pipeline/Rasterizer/Rasterizer.hpp>
#include <Graphics/Pipeline/Blend/Blend.hpp>

// Use shared_ptr to create device objects

struct VertexS
{
    XMFLOAT3 Position;
    XMFLOAT4 Color;
};

std::vector<uint16_t> indices = {0, 1, 2, 0, 3, 1};
std::vector<VertexS> triangle =
        {
                {{-0.5f, 0.5f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
                {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
                {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},
                {{0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}}

        };

struct ConstantBuffer
{
    XMMATRIX world;
    XMMATRIX view;
    XMMATRIX projection;
};

#include <Resources/MeshLoader/MeshLoader.hpp>
#include <Resources/Mesh/Mesh.hpp>

using namespace Strand;

int main()
{
    ConstantBuffer cb;

    cb.world = XMMatrixIdentity();
    cb.view = XMMatrixIdentity();
    cb.projection = XMMatrixIdentity();

    FileReader::CopyShaders("Shaders/", "Shaders/");

    Window* window = new Window("Strand Engine", {1920, 1080}, false);

    GraphicsDevice* device = new GraphicsDevice();

    SwapchainDesc swapchainDesc{
            .WindowSize_ = window->GetWindowSize(),
            .Numerator_ = 0,
            .Denominator_ = 0,
            .Format_ = DxgiFormat::RGBA8_UNSIGNED_NORMALIZED,
            .ScanlineOrdering_ = DxgiModeScanlineOrder::UNSPECIFIED,
            .Scaling_ = DxgiModeScaling::UNSPECIFIED,
            .SampleCount_ = 1,
            .SampleQuality_ = 0,
            .BufferUsage_ = DxgiBufferUsage::RENDER_TARGET_OUTPUT,
            .BufferCount_ = 3,
            .WindowHandle_ = window->GetWindowHandle(),
            .Windowed_ = true,
            .SwapEffect_ = DxgiSwapEffect::DISCARD,
            .Flags_ = 0
    };

    Swapchain* swapchain = device->CreateSwapchain(swapchainDesc);

    GraphicsTextureViewDesc depthDesc = {
            .TextureImageSize = {static_cast<int32_t>(window->GetWindowSize().x), static_cast<int32_t>(window->GetWindowSize().y)},
            .MipLevels = 1,
            .ArraySize = 1,
            .Format = DxgiFormat::D24_UNSIGNED_NORMALIZED_S8_UNSIGNED_INT,
            .SampleCount = 1,
            .SampleQuality = 0,
            .Usage = ResourceUsage::DEFAULT,
            .BindFlags = ResourceBindFlags::DEPTH_STENCIL,
            .CPUAccessFlags = ResourceCPUAccessFlags::NONE,
            .MiscFlags = 0,

    };

    GraphicsTextureView* depthAttachment = device->CreateGraphicsTextureView(depthDesc);

    FramebufferDesc framebufferDesc = {
            .ColorAttachmentFormat = DxgiFormat::RGBA8_UNSIGNED_NORMALIZED,
            .ColorAttachmentDimension = RenderTargetViewDimension::TEXTURE2D,
            .DepthStencilFormat = DxgiFormat::D24_UNSIGNED_NORMALIZED_S8_UNSIGNED_INT,
            .DepthStencilDimension = DepthStencilViewDimension::TEXTURE2D,
            .ColorAttachment_ = swapchain->GetBackBuffer(),
            .DepthAttachment_ = depthAttachment->GetTextureBuffer()
    };

    Framebuffer* framebuffer = device->CreateFramebuffer(framebufferDesc);

    framebuffer->CreateColorAttachment();
    framebuffer->CreateDepthAttachment();

    CommandList* commandList = device->CreateCommandList();

    ShaderDesc vertexShaderDesc = {
            .ShaderName_ = "VertexShader",
            .EntryPoint_ = "vs_main",
            .Type_ = ShaderType::VERTEX_SHADER,
    };

    ShaderDesc pixelShaderDesc = {
            .ShaderName_ = "PixelShader",
            .EntryPoint_ = "ps_main",
            .Type_ = ShaderType::PIXEL_SHADER,
    };

    Shader* vertexShader = device->CreateShader(vertexShaderDesc);
    Shader* pixelShader = device->CreateShader(pixelShaderDesc);

    SamplerStateDesc samplerDesc = {
            .SamplerFilter_ = SampleFilter::MIN_MAG_MIP_LINEAR,
            .AddressModeU_ = TextureAddressMode::WRAP,
            .AddressModeV_ = TextureAddressMode::WRAP,
            .AddressModeW_ = TextureAddressMode::WRAP,
            .MipLODBias_ = 1.0f,
            .MaxAnisotropy_ = 16,
            .ComparisonFunc_ = SamplerComparisonFunc::ALWAYS,
            .BorderColor_ = {0.0f, 0.0f, 0.0f, 0.0f},
            .MinLOD_ = 0.0f,
            .MaxLOD_ = FloatMax
    };

    SamplerState* samplerState = device->CreateSamplerState(samplerDesc);

    InputLayoutDesc* inputAssembler = new InputLayoutDesc{
            .SemanticName_ = {InputLayoutSemanticName::POSITION, InputLayoutSemanticName::COLOR},
            .InputFormat = {DxgiFormat::RGB32_FLOAT, DxgiFormat::RGBA32_FLOAT},
            .SemanticIndex_ = {0, 0},
            .InputSlot_ = {0, 0},
            .AlignedByteOffset_ = {D3D11_APPEND_ALIGNED_ELEMENT, D3D11_APPEND_ALIGNED_ELEMENT},
            .InputSlotClass_ = {InputSlotClass::PER_VERTEX_DATA, InputSlotClass::PER_VERTEX_DATA},
            .InstanceDataStepRate_ = {0, 0},
            .MeshTopology_ = MeshTopology::TRIANGLE_LIST
    };

    RasterizerStateDesc* rasterizerState = new RasterizerStateDesc{
            .FillMode_ = FillMode::SOLID,
            .CullMode_ = CullMode::BACK,
            .FrontFace_ = FrontFace::CLOCKWISE,
            .DepthBias_ = 0,
            .DepthBiasClamp_ = 0.0f,
            .SlopeScaledDepthBias_ = 0.0f,
            .DepthClipEnable_ = false,
            .ScissorEnable_ = false,
            .MultisampleEnable_ = true,
            .AntialiasedLineEnable_ = true
    };

    DepthStencilStateDesc* depthStencilState = new DepthStencilStateDesc{
            .DepthEnable = true,
            .DepthWriteMask = DepthWriteMask::ALL,
            .DepthFunc = DepthStencilComparisonFunc::LESS,
            .StencilEnable = false,
            .StencilReadMask = 0xFF,
            .StencilWriteMask = 0xFF,
    };

    BlendStateDesc* blendState = new BlendStateDesc{
            .AlphaToCoverageEnable = false,
            .IndependentBlendEnable = true,
            .RenderTargetDesc = {
                    .BlendEnable = true,
                    .SrcBlend = BlendType::ONE,
                    .DestBlend = BlendType::ONE,
                    .BlendOp = BlendOperation::ADD,
                    .SrcBlendAlpha = BlendType::ONE,
                    .DestBlendAlpha = BlendType::ONE,
                    .BlendOpAlpha = BlendOperation::ADD,
                    .RenderTargetWriteMask = ColorWriteEnable::ALL
            }
    };

    PipelineDesc pipelineDesc = {
            .Shaders_ = {vertexShader, pixelShader},
            .InputAssemblerDesc_ = inputAssembler,
            .RasterizerStateDesc_ = rasterizerState,
            .DepthStencilStateDesc_ = depthStencilState,
            .BlendStateDesc_ = blendState,
            .SamplerStateDesc_ = samplerState
    };

    Pipeline* basicPipeline = device->CreatePipeline(pipelineDesc);

    GraphicsBufferDesc vertexBufferDesc = {
            .Usage = ResourceUsage::DEFAULT,
            .CPUAccessFlags = ResourceCPUAccessFlags::NONE,
            .BindFlags = ResourceBindFlags::VERTEX_BUFFER,
            .MiscFlags = 0,
            .ByteWidth = (sizeof(VertexS) * triangle.size()),
            .StructureByteStride = sizeof(VertexS),
            .CPUData = triangle.data()
    };

    GraphicsBufferDesc indexBufferDesc = {
            .Usage = ResourceUsage::DEFAULT,
            .CPUAccessFlags = ResourceCPUAccessFlags::NONE,
            .BindFlags = ResourceBindFlags::INDEX_BUFFER,
            .MiscFlags = 0,
            .ByteWidth = sizeof(uint16_t ) * indices.size(),
            .StructureByteStride = sizeof(uint16_t),
            .CPUData = indices.data()
    };

    GraphicsBuffer* vertexBuffer = device->CreateGraphicsBuffer(vertexBufferDesc);
    GraphicsBuffer* indexBuffer = device->CreateGraphicsBuffer(indexBufferDesc);

    GraphicsBufferDesc constantBufferDesc = {
            .Usage = ResourceUsage::DYNAMIC,
            .CPUAccessFlags = ResourceCPUAccessFlags::WRITE,
            .BindFlags = ResourceBindFlags::CONSTANT_BUFFER,
            .MiscFlags = 0,
            .ByteWidth = sizeof(ConstantBuffer),
            .StructureByteStride = sizeof(ConstantBuffer),
            .CPUData = &cb
    };

    GraphicsBuffer* constantBuffer = device->CreateGraphicsBuffer(constantBufferDesc);

    XMVECTOR pos = {0.0f, 0.0f, 0.0f};
    XMVECTOR rot = {0.0f, 0.0f, 0.0f};
    XMVECTOR scale = {1.0f, 1.0f, 1.0f};

    while(!window->ShouldClose()) {
        window->ProcessMessage();

        rot.m128_f32[2] += 0.01f;

        cb.world = XMMatrixTranspose(XMMatrixScalingFromVector(scale) * XMMatrixRotationRollPitchYawFromVector(rot) * XMMatrixTranslationFromVector(pos));
        cb.view = XMMatrixTranspose(XMMatrixLookAtLH({0.0f, 0.0f, -5.0f}, {0.0f, 0.0f, 0.0f}, {0.0f,1.0f,0.0f}));
        cb.projection = XMMatrixTranspose(XMMatrixPerspectiveFovLH(XMConvertToRadians(90.0f), window->GetWindowSize().x / window->GetWindowSize().y, 0.1f, 100.0f));

        D3D11_MAPPED_SUBRESOURCE mappedSubresource;
        commandList->GetDefferedContext()->Map(constantBuffer->GetBuffer().Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource);
        memcpy(mappedSubresource.pData, &cb, sizeof(ConstantBuffer));
        commandList->GetDefferedContext()->Unmap(constantBuffer->GetBuffer().Get(), 0);

        commandList->BindFramebuffer(framebuffer);
        commandList->BindPipeline(basicPipeline);
        commandList->BindVertexBuffer(vertexBuffer);
        commandList->BindIndexBuffer(indexBuffer);
        commandList->BindViewport({window->GetWindowSize().x, window->GetWindowSize().y});

        commandList->GetDefferedContext()->VSSetConstantBuffers(0, 1, constantBuffer->GetBuffer().GetAddressOf());

        commandList->ClearBuffer({0.0f, 0.0f, 0.0f, 1.0f});

        commandList->DrawIndexed(indices.size(), 0, 0);

        device->ExecuteCommandList({commandList});

        swapchain->Present();
    }

    return 0;
}
