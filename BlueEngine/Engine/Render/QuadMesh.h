#pragma once

#include "Mesh.h"

namespace Blue
{
	// �簢�� �޽� Ŭ����
	class QuadMesh : public Mesh
	{
	public:
		QuadMesh();

		void Update(float deltaTime);

	private:
		void Rotate(float angle);
	};
}
