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

vOut vs_main( vIn input )
{
	vOut vso;
	vso.pos = float4(input.pos, 1.0f);
	vso.color = input.color;

	return vso;
}