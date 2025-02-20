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
		// �Ķ���� ����
		this->vertices.assign(vertices.begin(), vertices.end());
		stride = Vertex::Stride();
		this->indices.assign(indices.begin(), indices.end());

		// ���� - �޸� ���
		D3D11_BUFFER_DESC vertexBufferDesc = {};
		vertexBufferDesc.ByteWidth = stride * (uint32)vertices.size();
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		// ���� ������
		D3D11_SUBRESOURCE_DATA vertexData = {};
		vertexData.pSysMem = vertices.data();

		// ��ġ ������
		ID3D11Device& device = Engine::Get().Device();

		// ���� ���� ����
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

		// �ε��� ������
		D3D11_SUBRESOURCE_DATA indexData = {};
		indexData.pSysMem = indices.data();

		// �ε��� ���� ����
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
		// ���ҽ� ����.
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
		// ���ؽ�Ʈ ������
		static ID3D11DeviceContext& context = Engine::Get().Context();

		// ���� �� �ε��� ���� ���ε�
		static uint32 offset = 0;
		context.IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		context.IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	}

	Mesh::Mesh()
	{
	}

	void Mesh::Draw()
	{
		// ���ؽ�Ʈ ������
		static ID3D11DeviceContext& context = Engine::Get().Context();

		// ���� ��ȸ�ϸ鼭 ���ε� & ��ο�
		for (int ix = 0; ix < (int32)meshes.size(); ++ix)
		{
			meshes[ix]->Bind();
			shaders[ix]->Bind();
			context.DrawIndexed(meshes[ix]->IndexCount(), 0, 0);
		}
	}
}
