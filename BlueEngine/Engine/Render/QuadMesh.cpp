#include "QuadMesh.h"
#include "Vertex.h"
#include "Shader/Shader.h"
#include "Shader/TextureMappingShader.h"
#include "Resource/ShaderLoader.h"
#include "Math/Matrix4.h"
#include "Math/Vector3.h"

namespace Blue
{
	QuadMesh::QuadMesh()
	{
		// ���� �迭
		std::vector<Vertex> vertices =
		{
			// Vector(��ġ, ����, ���� ���� �ؽ�ó ��ǥ)
			Vertex(Vector3(-0.5f, 0.5f, 0.5f), Vector3(1.0f, 1.0f, 1.0f), Vector2(0.0f, 0.0f)), // ���� ���
			Vertex(Vector3(0.5f, 0.5f, 0.5f), Vector3(1.0f, 1.0f, 1.0f), Vector2(1.0f, 0.0f)), // ���� ���
			Vertex(Vector3(0.5f, -0.5f, 0.5f), Vector3(1.0f, 1.0f, 1.0f), Vector2(1.0f, 1.0f)), // ���� �ϴ�
			Vertex(Vector3(-0.5f, -0.5f, 0.5f), Vector3(1.0f, 1.0f, 1.0f), Vector2(0.0f, 1.0f)), // ���� �ϴ�
		};

		// �ε��� �迭
		std::vector<uint32> indices = { 0, 1, 3, 1, 2, 3 };

		//// ��ȯ.
		//vertices[0].position = vertices[0].position * Matrix4::Scale(0.5f);
		//vertices[1].position = vertices[1].position * Matrix4::Scale(0.5f);
		//vertices[2].position = vertices[2].position * Matrix4::Scale(0.5f);
		//vertices[3].position = vertices[3].position * Matrix4::Scale(0.5f);

		meshes.emplace_back(std::make_shared<MeshData>(vertices, indices));
		//shaders.emplace_back(std::make_shared<TextureMappingShader>("T_coord.png"));
		std::weak_ptr<TextureMappingShader> shader;
		if (ShaderLoader::Get().Load<TextureMappingShader>(shader, "T_coord.png"))
		{
			shaders.emplace_back(shader);
		}
	}

	void QuadMesh::Update(float deltaTime)
	{
		// ȸ�� ó��.
		static float angle = 0.0f;
		angle += 60.0f * deltaTime;

		Rotate(angle);
	}

	void QuadMesh::Rotate(float angle)
	{
		// ���� �迭
		std::vector<Vertex> vertices =
		{
			// Vector(��ġ, ����, ���� ���� �ؽ�ó ��ǥ)
			Vertex(Vector3(-0.5f, 0.5f, 0.5f), Vector3(1.0f, 1.0f, 1.0f), Vector2(0.0f, 0.0f)), // ���� ���
			Vertex(Vector3(0.5f, 0.5f, 0.5f), Vector3(1.0f, 1.0f, 1.0f), Vector2(1.0f, 0.0f)), // ���� ���
			Vertex(Vector3(0.5f, -0.5f, 0.5f), Vector3(1.0f, 1.0f, 1.0f), Vector2(1.0f, 1.0f)), // ���� �ϴ�
			Vertex(Vector3(-0.5f, -0.5f, 0.5f), Vector3(1.0f, 1.0f, 1.0f), Vector2(0.0f, 1.0f)), // ���� �ϴ�
		};

		static std::vector<Vertex> result;
		static bool hasInitialized = false;
		if (!hasInitialized)
		{
			hasInitialized = true;
			result.assign(vertices.begin(), vertices.end());
		}

		// ȸ��.
		Matrix4 rotation = Matrix4::RotationZ(angle);
		result[0].position = vertices[0].position * rotation;
		result[1].position = vertices[1].position * rotation;
		result[2].position = vertices[2].position * rotation;
		result[3].position = vertices[3].position * rotation;

		// �޽��� ���� ���� ������Ʈ.
		meshes[0]->UpdateVertexBuffer(result);
	}
}
