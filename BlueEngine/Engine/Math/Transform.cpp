#include "Transform.h"
#include "Core/Common.h"
#include "Core/Engine.h"

namespace Blue
{
	Transform::Transform()
	{
		// 트랜스폼 행렬 계산 (SRT).
		transformMatrix =
			Matrix4::Scale(scale)
			* Matrix4::Rotation(rotation)
			* Matrix4::Translation(position);

		// 전치 행렬 (CPU와 GPU가 행렬을 다루는 방식이 달라서).
		// 행 기준 행렬을 열 기준 행렬로 반환하기 위해 전치 행렬 처리.
		transformMatrix = Matrix4::Transpose(transformMatrix);

		// 상수 버퍼.
		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.ByteWidth = Matrix4::Stride();
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		
		// 버퍼에 담을 데이터 설정.
		D3D11_SUBRESOURCE_DATA bufferData = {};
		bufferData.pSysMem = &transformMatrix;

		// 버퍼 생성.
		ID3D11Device& device = Engine::Get().Device();
		ThrowIfFailed(
			device.CreateBuffer(&bufferDesc, &bufferData, &constantBuffer),
			TEXT("Failed to create a transform buffer."));
	}

	Transform::~Transform()
	{
		// 리소스 해제.
		if (constantBuffer)
		{
			constantBuffer->Release();
			constantBuffer = nullptr;
		}
	}

	void Transform::Tick()
	{
		// 데이터 업데이트
		// 트랜스폼 행렬 계산 (SRT).
		transformMatrix =
			Matrix4::Scale(scale)
			* Matrix4::Rotation(rotation)
			* Matrix4::Translation(position);

		// 전치 행렬 (CPU와 GPU가 행렬을 다루는 방식이 달라서).
		// 행 기준 행렬을 열 기준 행렬로 반환하기 위해 전치 행렬 처리.
		transformMatrix = Matrix4::Transpose(transformMatrix);
	}

	void Transform::Bind()
	{
		static ID3D11DeviceContext& context = Engine::Get().Context();

		// 버퍼 업데이트.
		D3D11_MAPPED_SUBRESOURCE resource = {};
		context.Map(constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
		memcpy(resource.pData, &transformMatrix, sizeof(Matrix4)); // 대입하는 것보다는 메모리 카피하는 것이 낫다.
		context.Unmap(constantBuffer, 0);

		// 버퍼 바인딩.
		context.VSSetConstantBuffers(0, 1, &constantBuffer);
	}
}
