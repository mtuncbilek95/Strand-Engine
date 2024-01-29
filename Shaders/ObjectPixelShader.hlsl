Texture2D baseColor : register(t0);
Texture2D normalMap : register(t1);
Texture2D emmisiveMap : register(t2);

sampler baseSampler : register(s0);

struct pixelIn
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL0;
};

float4 ps_main(pixelIn input) : SV_TARGET
{
    return baseColor.Sample(baseSampler, input.tex) + emmisiveMap.Sample(baseSampler, input.tex);
}