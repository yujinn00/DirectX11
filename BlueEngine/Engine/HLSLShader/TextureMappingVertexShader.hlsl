struct VertexInput
{
    float3 position : POSITION;
    float3 color : COLOR;
    float2 texCoord : TEXCOORD;
    float3 normal : NORMAL;
};

// ConstantBuffer.
cbuffer Transform : register(b0)
{
    matrix worldMatrix;
};

// Camera Buffer.
cbuffer Camera : register(b1)
{
    matrix view;
    matrix projection;
};

struct VertexOutput
{
    float4 position : SV_Position;
    float3 color : COLOR;
    float2 texCoord : TEXCOORD;
    float3 normal : NORMAL;
};

VertexOutput main(VertexInput input)
{
    VertexOutput output;
    //output.position = float4(input.position, 1);
    output.position = mul(float4(input.position, 1), worldMatrix); // worldMatrix에는 TRS 정보가 들어가 있음.
    output.position = mul(output.position, view);
    output.position = mul(output.position, projection);

    output.color = input.color;
    output.texCoord = input.texCoord;
    output.normal = normalize(mul(input.normal, (float3x3)worldMatrix));

    return output;
}
