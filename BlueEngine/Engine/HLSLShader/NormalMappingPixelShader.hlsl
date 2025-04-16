#include "Common.hlsli"

struct PixelInput
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
    float2 texCoord : TEXCOORD;
    float3 normal : NORMAL;
    float3 cameraDirection : TEXCOORD1;
    float3 tangent : TANGENT;
    float3 bitangent : BITANGENT;
};

// Texture.
Texture2D diffuseMap : register(t0);
Texture2D normalMap : register(t1);
SamplerState diffuseSampler : register(s0);

float4 main(PixelInput input) : SV_TARGET
{
    // Sampling.
    float4 texColor = diffuseMap.Sample(diffuseSampler, input.texCoord);

    // tangent normal.
    float4 tangentNormal = normalMap.Sample(diffuseSampler, input.texCoord);
    tangentNormal = tangentNormal * 2 - 1;

    // tangent to world transformation matrix.
    float3x3 tangentToWorld = float3x3(
        normalize(input.tangent), // Tangent -> X축.
        normalize(input.bitangent), // Bitangent -> Y축.
        normalize(input.normal) // Normal -> Z축.
    );

    // Light Dir.
    float3 lightDir = -float3(500.f, 500.f, -500.f);
    lightDir = normalize(lightDir);

    // World Normal.
    float3 worldNormal = normalize(mul(tangentNormal.xyz, tangentToWorld));

    // Dot (Lambert cosine law) - diffuse.
    float nDotL = CalcLambert(worldNormal, lightDir);

    float4 ambient = texColor * float4(0.2f, 0.2f, 0.2f, 1.0f);
    float4 diffuse = texColor * nDotL;
    float4 finalColor = ambient + diffuse;

    // Phong (specular).
    // float specular = CalcPhong(worldNormal, lightDir, input.cameraDirection);

    // Blinn-Phong (specular).
    float specular = CalcBlinnPhong(worldNormal, lightDir, input.cameraDirection);

    finalColor += float4(0.4f, 0.6f, 0.8f, 1.0f) * specular;

    return finalColor;
}
