#include "TriangleMesh.h"
#include "Vertex.h"
#include "Shader/Shader.h"

namespace Blue
{
	TriangleMesh::TriangleMesh()
	{
		// ���� �迭
		std::vector<Vertex> vertices =
		{
			// Vector(��ġ, ����, ���� ���� �ؽ�ó ��ǥ)
			Vertex(Vector3(0.0f, 0.5f, 0.5f), Vector3(1.0f, 0.0f, 0.0f), Vector2(0.5f, 0.0f)), // �߾� ���
			Vertex(Vector3(0.5f, -0.5f, 0.5f), Vector3(0.0f, 1.0f, 0.0f), Vector2(1.0f, 1.0f)), // ���� �ϴ�
			Vertex(Vector3(-0.5f, -0.5f, 0.5f), Vector3(0.0f, 0.0f, 1.0f), Vector2(0.0f, 1.0f)), /// ���� �ϴ�
		};

		// �ε��� �迭
		std::vector<uint32> indices = { 0, 1, 2 };

		meshes.emplace_back(std::make_shared<MeshData>(vertices, indices));
		shaders.emplace_back(std::make_shared<Shader>());
	}
}
