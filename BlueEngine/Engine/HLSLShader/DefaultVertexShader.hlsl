/*
POSITION�� �ø�ƽ�̸�, ���ؽ� �����͸� �����ϴ� �� ���ȴ�.
�ø�ƽ�� GPU�� ���ǵ� Ű�����̸�, DirectX�� HLSL���� ������ ��Ģ�� ����� �Ѵ�.
SV_POSITION�� ���̴��� ��� ����� ������ ���������ο� �����ϴ� ������ �Ѵ�.
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
