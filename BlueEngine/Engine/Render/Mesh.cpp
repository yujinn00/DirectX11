#include "Mesh.h"
#include "Core/Engine.h"
#include "Shader/Shader.h"

namespace Blue
{
	MeshData::MeshData()
	{
	}

	MeshData::MeshData(
		const std::vector<Vertex>&vertices,
		const std::vector<uint32>& indices)
	{
		// 파라미터 복사.
		this->vertices.assign(vertices.begin(), vertices.end());
		stride = Vertex::Stride();
		this->indices.assign(indices.begin(), indices.end());

		// 버퍼 - 메모리 덩어리.
		D3D11_BUFFER_DESC vertexBufferDesc = {};
		vertexBufferDesc.ByteWidth = stride * (uint32)vertices.size();
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		// 정점 데이터.
		D3D11_SUBRESOURCE_DATA vertexData = {};
		vertexData.pSysMem = vertices.data();

		// 장치 얻어오기.
		ID3D11Device& device = Engine::Get().Device();

		// 정점 버퍼 생성.
		auto result = device.CreateBuffer(
			&vertexBufferDesc, &vertexData, &vertexBuffer
		);

		if (FAILED(result))
		{
			MessageBoxA(nullptr, "Failed to create vertex buffer", "Error", MB_OK);
			__debugbreak();
		}

		D3D11_BUFFER_DESC indexBufferDesc = {};
		indexBufferDesc.ByteWidth = sizeof(uint32) * (uint32)indices.size();
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		// 인덱스 데이터.
		D3D11_SUBRESOURCE_DATA indexData = {};
		indexData.pSysMem = indices.data();

		// 인덱스 버퍼 생성.
		result = device.CreateBuffer(
			&indexBufferDesc, &indexData, &indexBuffer
		);

		if (FAILED(result))
		{
			MessageBoxA(nullptr, "Failed to create index buffer", "Error", MB_OK);
			__debugbreak();
		}
	}

	MeshData::~MeshData()
	{
		// 리소스 해제.
		if (vertexBuffer)
		{
			vertexBuffer->Release();
		}

		if (indexBuffer)
		{
			indexBuffer->Release();
		}
	}

	void MeshData::Bind()
	{
		// 컨텍스트 얻어오기.
		static ID3D11DeviceContext& context = Engine::Get().Context();

		// 정점 및 인덱스 버퍼 바인딩.
		static uint32 offset = 0;
		context.IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		context.IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	}

	void MeshData::UpdateVertexBuffer(const std::vector<Vertex>& vertices)
	{
		// 파라미터 복사.
		this->vertices.assign(vertices.begin(), vertices.end());

		// 정점 버퍼가 있으면, 해제 후 재생성.
		if (vertexBuffer)
		{
			vertexBuffer->Release();
			vertexBuffer = nullptr;
		}

		// 버퍼 - 메모리 덩어리.
		D3D11_BUFFER_DESC vertexBufferDesc = {};
		vertexBufferDesc.ByteWidth = stride * (uint32)vertices.size();
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		// 정점 데이터.
		D3D11_SUBRESOURCE_DATA vertexData = {};
		vertexData.pSysMem = vertices.data();

		// 장치 얻어오기.
		ID3D11Device& device = Engine::Get().Device();

		// 정점 버퍼 생성.
		auto result = device.CreateBuffer(
			&vertexBufferDesc, &vertexData, &vertexBuffer
		);

		if (FAILED(result))
		{
			MessageBoxA(nullptr, "Failed to create vertex buffer", "Error", MB_OK);
			__debugbreak();
		}
	}

	Mesh::Mesh()
	{
	}

	//void Mesh::Draw()
	//{
	//	// 컨텍스트 얻어오기.
	//	static ID3D11DeviceContext& context = Engine::Get().Context();

	//	// 트랜스폼 바인딩.
	//	transform.Bind();

	//	// 루프 순회하면서 바인딩 & 드로우.
	//	for (int ix = 0; ix < (int32)meshes.size(); ++ix)
	//	{
	//		// 원래 리소스 가져오기.
	//		auto mesh = meshes[ix].lock();
	//		auto shader = shaders[ix].lock();

	//		// 리소스에 문제가 없으면 그리기.
	//		if (mesh && shader)
	//		{
	//			mesh->Bind();
	//			shader->Bind();
	//			context.DrawIndexed(mesh->IndexCount(), 0, 0);
	//		}

	//		//meshes[ix]->Bind();
	//		//shaders[ix].lock()->Bind();
	//		//context.DrawIndexed(meshes[ix]->IndexCount(), 0, 0);
	//	}
	//}

	uint32 Mesh::SubMeshCount() const
	{
		return (uint32)meshes.size();
	}

	std::weak_ptr<MeshData> Mesh::GetSubMesh(int index) const
	{
		// 예외 처리.
		if (index < 0 || index >= (int)meshes.size())
		{
			return std::weak_ptr<MeshData>();
		}

		return meshes[index];
	}
}
