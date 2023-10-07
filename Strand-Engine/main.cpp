#include <FileReader/FileReader.hpp>
#include <Graphics/Utils/DxgiUtils.hpp>

#include <Window/Manager/WindowManager.hpp>
#include <Graphics/Manager/GraphicsManager.hpp>
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
#include <Resources/Mesh/Mesh.hpp>
#include <Resources/MeshImporter/MeshImporter.hpp>

#include <Graphics/Pipeline/ShaderStage.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using namespace Strand;

struct CB
{
    XMMATRIX mWorld;
    XMMATRIX mView;
    XMMATRIX mProjection;
};

int main()
{
    FileReader::CopyShaders("Shaders/", "Shaders/");

    WindowManager& windowManager = WindowManager::GetInstance();
    windowManager.InitializeWindow("Strand Engine", {2560, 1440}, true);

    GraphicsManager& graphicsManager = GraphicsManager::GetInstance();

    SwapchainDesc swapchainDesc{
            .WindowSize_ = windowManager.GetWindow()->GetWindowSize(),
            .Numerator_ = 0,
            .Denominator_ = 0,
            .Format_ = DxgiFormat::RGBA8_UNSIGNED_NORMALIZED,
            .ScanlineOrdering_ = DxgiModeScanlineOrder::UNSPECIFIED,
            .Scaling_ = DxgiModeScaling::UNSPECIFIED,
            .SampleCount_ = 1,
            .SampleQuality_ = 0,
            .BufferUsage_ = DxgiBufferUsage::RENDER_TARGET_OUTPUT,
            .BufferCount_ = 3,
            .WindowHandle_ = windowManager.GetWindow()->GetWindowHandle(),
            .Windowed_ = true,
            .SwapEffect_ = DxgiSwapEffect::DISCARD,
            .Flags_ = 0
    };

    Swapchain* swapchain = graphicsManager.GetGraphicsDevice()->CreateSwapchain(swapchainDesc);

    GraphicsTextureViewDesc depthDesc = {
            .TextureImageSize = {static_cast<int32_t>(windowManager.GetWindow()->GetWindowSize().x), static_cast<int32_t>(windowManager.GetWindow()->GetWindowSize().y)},
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

    GraphicsTextureView* depthAttachment = graphicsManager.GetGraphicsDevice()->CreateGraphicsTextureView(depthDesc);

    FramebufferDesc framebufferDesc = {
            .ColorAttachmentFormat = DxgiFormat::RGBA8_UNSIGNED_NORMALIZED,
            .ColorAttachmentDimension = RenderTargetViewDimension::TEXTURE2D,
            .DepthStencilFormat = DxgiFormat::D24_UNSIGNED_NORMALIZED_S8_UNSIGNED_INT,
            .DepthStencilDimension = DepthStencilViewDimension::TEXTURE2D,
            .ColorAttachment_ = swapchain->GetBackBuffer(),
            .DepthAttachment_ = depthAttachment->GetTextureBuffer()
    };

    Framebuffer* framebuffer = graphicsManager.GetGraphicsDevice()->CreateFramebuffer(framebufferDesc);

    framebuffer->CreateColorAttachment();
    framebuffer->CreateDepthAttachment();

    CommandList* commandList = graphicsManager.GetGraphicsDevice()->CreateCommandList();

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

    Shader* vertexShader = graphicsManager.GetGraphicsDevice()->CreateShader(vertexShaderDesc);
    Shader* pixelShader = graphicsManager.GetGraphicsDevice()->CreateShader(pixelShaderDesc);

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

    SamplerState* samplerState = graphicsManager.GetGraphicsDevice()->CreateSamplerState(samplerDesc);

    InputLayoutDesc* inputAssembler = new InputLayoutDesc{
            .SemanticName_ = {InputLayoutSemanticName::POSITION, InputLayoutSemanticName::TEXCOORD},
            .InputFormat = {DxgiFormat::RGB32_FLOAT, DxgiFormat::RG32_FLOAT},
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
                    .BlendEnable = false,
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

    Pipeline* basicPipeline = graphicsManager.GetGraphicsDevice()->CreatePipeline(pipelineDesc);

    Mesh* testMesh = new Mesh();

    MeshImporter::ReadStaticMeshFile("D:\\Projects\\glTF-Sample-Models\\2.0\\DamagedHelmet\\glTF\\DamagedHelmet.gltf", testMesh);

    int width, height, channels;

    uint8_t* data = stbi_load("D:\\Projects\\glTF-Sample-Models\\2.0\\DamagedHelmet\\glTF\\Default_albedo.jpg", &width, &height, &channels, STBI_rgb_alpha);

    GraphicsTextureViewDesc textureDesc = {
            .TextureImageSize = {width, height},
            .MipLevels = 1,
            .MostDetailedMip = 0,
            .ArraySize = 1,
            .Format = DxgiFormat::RGBA8_UNSIGNED_NORMALIZED,
            .SampleCount = 1,
            .SampleQuality = 0,
            .SRVDimension = ShaderResourceViewDimension::TEXTURE2D,
            .Usage = ResourceUsage::IMMUTABLE,
            .BindFlags = ResourceBindFlags::SHADER_RESOURCE,
            .CPUAccessFlags = ResourceCPUAccessFlags::NONE,
            .MiscFlags = 0,
            .CPUData = data,
            .CPUDataPitch = width * 4
    };

    GraphicsTextureView* textureView = graphicsManager.GetGraphicsDevice()->CreateGraphicsTextureView(textureDesc);

    GraphicsBufferDesc vertexDesc = {
            .Usage = ResourceUsage::DEFAULT,
            .CPUAccessFlags = ResourceCPUAccessFlags::NONE,
            .BindFlags = ResourceBindFlags::VERTEX_BUFFER,
            .MiscFlags = 0,
            .ByteWidth = sizeof(Vertex) * testMesh->GetVertices().size(),
            .StructureByteStride = sizeof(Vertex),
            .CPUData = testMesh->GetVertices().data()
    };

    GraphicsBuffer* vertexBuffer = graphicsManager.GetGraphicsDevice()->CreateGraphicsBuffer(vertexDesc);

    GraphicsBufferDesc indexBufferDesc = {
            .Usage = ResourceUsage::DEFAULT,
            .CPUAccessFlags = ResourceCPUAccessFlags::NONE,
            .BindFlags = ResourceBindFlags::INDEX_BUFFER,
            .MiscFlags = 0,
            .ByteWidth = sizeof(uint16_t) * testMesh->GetIndices().size(),
            .StructureByteStride = sizeof(uint16_t),
            .CPUData = testMesh->GetIndices().data()
    };

    GraphicsBuffer* indexBuffer = graphicsManager.GetGraphicsDevice()->CreateGraphicsBuffer(indexBufferDesc);

    CB modelMatrix = {
            .mWorld = XMMatrixIdentity(),
            .mView = XMMatrixIdentity(),
            .mProjection = XMMatrixIdentity()
    };

    GraphicsBufferDesc constantBufferDesc = {
            .Usage = ResourceUsage::DYNAMIC,
            .CPUAccessFlags = ResourceCPUAccessFlags::WRITE,
            .BindFlags = ResourceBindFlags::CONSTANT_BUFFER,
            .MiscFlags = 0,
            .ByteWidth = sizeof(CB),
            .StructureByteStride = sizeof(CB),
            .CPUData = &modelMatrix
    };

    GraphicsBuffer* constantBuffer = graphicsManager.GetGraphicsDevice()->CreateGraphicsBuffer(constantBufferDesc);

    XMFLOAT3 pos = {0.0f, 0.0f, 0.0f};
    XMFLOAT3 rot = {90.0f, 0.0f, 0.0f};
    XMFLOAT3 scale = {1.0f, 1.0f, 1.0f};

    while(!windowManager.GetWindow()->ShouldClose()) {
        windowManager.GetWindow()->ProcessMessage();

        rot.y += 0.3f;

        modelMatrix.mWorld = XMMatrixTranspose(XMMatrixScaling(scale.x, scale.y, scale.z) * XMMatrixRotationRollPitchYaw(XMConvertToRadians(rot.x), XMConvertToRadians(rot.y), XMConvertToRadians(rot.z)) * XMMatrixTranslation(pos.x, pos.y, pos.z));
        modelMatrix.mView = XMMatrixTranspose(XMMatrixLookAtLH({0.0f, 0.0f, -2.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0, 0.0f}));
        modelMatrix.mProjection = XMMatrixTranspose(XMMatrixPerspectiveFovLH(XMConvertToRadians(74.0f), static_cast<float>(windowManager.GetWindow()->GetWindowSize().x) / static_cast<float>(windowManager.GetWindow()->GetWindowSize().y), 0.1f, 100.0f));

        commandList->BindFramebuffer(framebuffer);
        commandList->BindPipeline(basicPipeline);
        commandList->BindVertexBuffer(vertexBuffer);
        commandList->BindIndexBuffer(indexBuffer);
        commandList->BindViewport({windowManager.GetWindow()->GetWindowSize().x, windowManager.GetWindow()->GetWindowSize().y});

        commandList->UpdateDynamicBuffer(constantBuffer, &modelMatrix, sizeof(CB));
        commandList->BindResources({textureView},{samplerState}, {}, ShaderStage::PIXEL_SHADER);
        commandList->BindResources({}, {}, {constantBuffer}, ShaderStage::VERTEX_SHADER);

        commandList->ClearBuffer({0.0f, 0.0f, 0.0f, 1.0f});

        commandList->DrawIndexed(testMesh->GetIndices().size(), 0, 0);

        graphicsManager.GetGraphicsDevice()->ExecuteCommandList({commandList});

        swapchain->Present();
    }

    return 0;
}
