struct vertexOut
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL0;
    float3 worldPos : WORLD_POSITION;
};

struct vertexIn
{
    float3 pos : POSITION;
    float2 tex : TEXCOORD;
    float3 normal : NORMAL;
};

cbuffer cbPerObject : register(b0)
{
    float4x4 worldMatrix;
    float4x4 viewMatrix;
    float4x4 projectionMatrix;
};

vertexOut vs_main(vertexIn input)
{
    vertexOut output;
    output.pos = mul(float4(input.pos, 1.0f), worldMatrix);
    output.pos = mul(output.pos, viewMatrix);
    output.pos = mul(output.pos, projectionMatrix);
    output.tex = input.tex;
    output.normal = normalize(mul(float4(input.normal, 0.0f), worldMatrix).xyz);
    output.worldPos = mul(float4(input.pos, 1.0f), worldMatrix).xyz;
    return output;
}