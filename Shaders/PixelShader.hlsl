struct pIn
{
    float4 pos : SV_POSITION;
    float4 col : COLOR0;
};

float4 ps_main(pIn input) : SV_Target
{
    return input.col;
}
