#pragma once

#include "Vertex.h"
#include "Core/Type.h"

#include <vector>
#include <memory>
#include <d3d11.h>

namespace Blue
{
	// �޽� ������ ����ü
	struct MeshData
	{
		MeshData();
		MeshData(
			const std::vector<Vertex>& vertices,
			const std::vector<uint32>& indices
		);
		~MeshData();

		void Bind();
		uint32 IndexCount() const { return (uint32)indices.size(); }

		// ���� ������
		std::vector<Vertex> vertices;
		uint32 stride = 0;
		ID3D11Buffer* vertexBuffer = nullptr;

		// �ε��� ������
		std::vector<uint32> indices;
		ID3D11Buffer* indexBuffer = nullptr;
	};

	class Mesh
	{
	public:
		Mesh();
		virtual ~Mesh() = default;

		virtual void Draw();

	protected:
		std::vector<std::shared_ptr<MeshData>> meshes;
		std::vector<std::shared_ptr<class Shader>> shaders;
	};
}
