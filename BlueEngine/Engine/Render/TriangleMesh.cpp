#include "TriangleMesh.h"
#include "Vertex.h"
#include "Shader/Shader.h"

namespace Blue
{
	TriangleMesh::TriangleMesh()
	{
		// 정점 배열
		std::vector<Vertex> vertices =
		{
			// Vector(위치, 색상, 정점 기준 텍스처 좌표)
			Vertex(Vector3(0.0f, 0.5f, 0.5f), Vector3(1.0f, 0.0f, 0.0f), Vector2(0.5f, 0.0f)), // 중앙 상단
			Vertex(Vector3(0.5f, -0.5f, 0.5f), Vector3(0.0f, 1.0f, 0.0f), Vector2(1.0f, 1.0f)), // 우측 하단
			Vertex(Vector3(-0.5f, -0.5f, 0.5f), Vector3(0.0f, 0.0f, 1.0f), Vector2(0.0f, 1.0f)), /// 좌측 하단
		};

		// 인덱스 배열
		std::vector<uint32> indices = { 0, 1, 2 };

		meshes.emplace_back(std::make_shared<MeshData>(vertices, indices));
		shaders.emplace_back(std::make_shared<Shader>());
	}
}
