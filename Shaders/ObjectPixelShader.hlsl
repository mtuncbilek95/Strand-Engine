Texture2D baseColor : register(t0);
Texture2D emissiveMap : register(t1);
Texture2D normalMap : register(t2);
Texture2D ambientOcclusionMap : register(t3);
Texture2D metallicMap : register(t4);

sampler baseSampler : register(s0);

struct pixelIn
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL0;
    float3 worldPos : WORLD_POSITION;
};

cbuffer AmbientLightObject : register(b0)
{
    float3 cameraPosition;
    float3 ambientColor;
    float3 ambientIntensity;
    
    float3 lightColor;
    float3 lightPosition;
    float3 lightIntensity;
};  

float3 decodeNormal(float3 n)
{
    return normalize(n * 2.0 - 1.0);
}

float4 ps_main(pixelIn input) : SV_TARGET
{
    float3 sampleColor = baseColor.Sample(baseSampler, input.tex).rgb;
    float3 sampleEmissive = emissiveMap.Sample(baseSampler, input.tex).rgb;
    float3 sampleNormal = decodeNormal(normalMap.Sample(baseSampler, input.tex).rgb);
    float3 sampleAmbientOcclusion = ambientOcclusionMap.Sample(baseSampler, input.tex).rgb;
    float sampleMetallic = metallicMap.Sample(baseSampler, input.tex).r;

    float3 ambientLight = ambientColor * ambientIntensity.x;
    float3 appliedLight = ambientLight;

    float3 vectorToLight = normalize(lightPosition - input.worldPos);
    float3 worldSpaceNormal = normalize(input.normal + sampleNormal);
    float diffuseLightIntensity = max(dot(worldSpaceNormal, vectorToLight), 0);
    float3 diffuseLight = lightColor * lightIntensity.x * diffuseLightIntensity;

    appliedLight += diffuseLight;

    float3 finalColor = (sampleColor) * appliedLight + sampleEmissive;
    finalColor *= sampleAmbientOcclusion;

    float3 viewDirection = normalize(cameraPosition - input.worldPos);
    float3 specularReflection = sampleColor * pow(max(dot(reflect(-vectorToLight, worldSpaceNormal), viewDirection), 0), 32);
    specularReflection *= sampleMetallic;

    finalColor += specularReflection;

    return float4(finalColor, 1);
    
}