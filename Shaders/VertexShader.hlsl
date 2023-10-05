struct vOut
{
	float4 pos : SV_Position;
	float4 color : COLOR0;
};

struct vIn
{
    float3 pos : POSITION;
    float4 color : COLOR0;
};

cbuffer cbPerObject : register( b0 )
{
    float4x4 world;
    float4x4 view;
    float4x4 projection;
};

vOut vs_main( vIn input )
{
	vOut vso;
	vso.pos = mul( float4(input.pos, 1.0f), world );
	vso.pos = mul( vso.pos, view );
	vso.pos = mul( vso.pos, projection );
	vso.color = input.color;

	return vso;
}