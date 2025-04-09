#pragma once

#include "Mesh.h"

namespace Blue
{
	// 사각형 메쉬 클래스.
	class QuadMesh : public Mesh
	{
	public:
		QuadMesh();

		void Update(float deltaTime);

	private:
		void Rotate(float angle);
	};
}
