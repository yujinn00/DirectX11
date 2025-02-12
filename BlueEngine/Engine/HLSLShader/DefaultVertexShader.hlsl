/*
POSITION은 시맨틱이며, 버텍스 데이터를 전달하는 데 사용된다.
시맨틱은 GPU에 정의된 키워드이며, DirectX와 HLSL에서 정해진 규칙을 따라야 한다.
SV_POSITION은 셰이더의 출력 결과를 렌더링 파이프라인에 전달하는 역할을 한다.
*/
struct VertexInput
{
    float3 position : POSITION;
    float3 color : COLOR;
};

struct VertexOutput
{
    float4 position : SV_Position;
    float3 color : COLOR;
};

VertexOutput main(VertexInput input)
{
    VertexOutput output;
    output.position = float4(input.position, 1);
    output.color = input.color;

    return output;
}
