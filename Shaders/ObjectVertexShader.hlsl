struct vertexOut
{
    float4 pos : SV_POSITION;
    float4 color : COLOR0;
};

struct vertexIn
{
    float3 pos : POSITION;
    float3 color : COLOR;
};

vertexOut vs_main(vertexIn input)
{
    vertexOut output;
    output.pos = float4(input.pos, 1.0f);
    output.color = float4(input.color, 1.0f);
    
    return output;
}