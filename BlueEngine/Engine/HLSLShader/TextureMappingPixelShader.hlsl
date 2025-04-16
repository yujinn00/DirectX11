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

    float4 ambient = texColor * float4(0.1f, 0.1f, 0.1f, 1.0f);
    float4 diffuse = texColor * nDotL;
    float4 finalColor = ambient + diffuse;

    // Phong (specular).
    // float specular = CalcPhong(worldNormal, lightDir, input.cameraDirection);

    // Blinn-Phong (specular).
    float specular = 0;
    if (nDotL)
    {
        // Half Vector.
        float3 viewDirection = normalize(input.cameraDirection);
        float3 halfVector = normalize((-lightDir) + (-viewDirection));

        // nDotH.
        float nDotH = saturate(dot(worldNormal, halfVector));
        float shininess = 32.0f;
        specular = pow(nDotH, shininess);
    }

    finalColor += float4(0.4f, 0.6f, 0.8f, 1.0f) * specular;

    return finalColor;
}
