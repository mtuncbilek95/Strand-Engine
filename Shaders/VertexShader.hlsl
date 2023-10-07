struct vOut
{
	float4 pos : SV_Position;
	float2 uv : TEXCOORD0;
};

struct vIn
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD0;
};

cbuffer cbPerObject : register(b0)
{
    matrix world;
    matrix view;
    matrix projection;
};

vOut vs_main( vIn input )
{
	vOut vso;
	vso.pos = mul(float4(input.pos, 1.0f), world);
	vso.pos = mul(vso.pos, view);
	vso.pos = mul(vso.pos, projection);
	vso.uv = input.uv;

	return vso;
}