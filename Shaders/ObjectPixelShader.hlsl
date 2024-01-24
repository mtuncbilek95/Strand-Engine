struct pixelIn
{
    float4 pos : SV_POSITION;
    float4 color : COLOR0;
};

float4 ps_main(pixelIn input) : SV_TARGET
{
    return input.color;
    
}