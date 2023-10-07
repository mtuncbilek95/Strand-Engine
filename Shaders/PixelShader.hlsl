Texture2D tex : register(t0);
SamplerState samp : register(s0);

struct pIn
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
};

float4 ps_main(pIn input) : SV_Target
{
    return tex.Sample(samp, input.uv);
}
