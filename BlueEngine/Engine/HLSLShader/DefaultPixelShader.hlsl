struct PixelInput
{
    float4 position : SV_Position;
    float3 color : COLOR;
    float2 texCoord : TEXCOORD;
};

float4 main(PixelInput input) : SV_TARGET
{
    //return float4(1.0f, 0.0f, 0.0f, 0.0f);
    return float4(input.color, 1.0f);
}
