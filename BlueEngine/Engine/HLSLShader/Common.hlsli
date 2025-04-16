
// Lambert cosine law.
float CalcLambert(float3 worldNormal, float3 lightDirection)
{
    return saturate(dot(worldNormal, -lightDirection));
}

// Half Lambert.
float CalcHalfLambert(
    float3 worldNormal,
    float3 lightDirection,
    float param = 2)
{
    float nDotL = CalcLambert(worldNormal, lightDirection);
    return pow(nDotL * 0.5f + 0.5f, param);
}

// Phong.
float CalcPhong(
    float3 worldNormal,
    float3 lightDirection,
    float3 cameraDirection,
    float shininess = 16.0f)
{
    float nDotL = CalcLambert(worldNormal, lightDirection);

    float specular = 0;
    if (nDotL)
    {
        float3 reflection = reflect(lightDirection, worldNormal);
        float3 viewDirection = normalize(cameraDirection);
        float rDotV = saturate(dot(reflection, -viewDirection));
        specular = pow(rDotV, shininess);
    }

    return specular;
}
