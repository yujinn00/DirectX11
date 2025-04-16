#include "Common.hlsli"

struct PixelInput
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
    float2 texCoord : TEXCOORD;
    float3 normal : NORMAL;
    float3 cameraDirection : TEXCOORD1;
};

// Texture
Texture2D diffuseMap : register(t0);
SamplerState diffuseSampler : register(s0);

float4 main(PixelInput input) : SV_TARGET
{
    // Sampling
    float4 texColor = diffuseMap.Sample(diffuseSampler, input.texCoord);

    // Light Dir.
    float3 lightDir = -float3(500.f, 500.f, -500.f);
    lightDir = normalize(lightDir);

    // World Normal.
    float3 worldNormal = normalize(input.normal);

    // Dot (Lambert).
    // float nDotl = saturate(dot(worldNormal, -lightDir));
    float nDotL = CalcLambert(worldNormal, lightDir);

    // Half Lambert.
    // nDotL = pow((nDotL * 0.7f) + (1.0 - 0.7), 1);

    // Phong (specular)
    

    float4 finalColor = texColor * nDotL;

    // return float4(1.0f, 0.0f, 0.0f, 1.0f);
    // return float4(input.color, 1.0f);
    // return float4(input.texCoord, 0.0f, 1.0f)
    // return float4(lightIntensity, lightIntensity, lightIntensity, 1);
    return finalColor;
}
