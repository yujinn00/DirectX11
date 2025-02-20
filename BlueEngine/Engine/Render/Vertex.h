#pragma once

#include "Math/Vector3.h"
#include "Math/Vector2.h"

namespace Blue
{
	class Vertex
	{
	public:
		Vertex(
			const Vector3& position,
			const Vector3& color,
			const Vector2& texCoord)
			: position(position), color(color), texCoord(texCoord)
		{
		}

		static unsigned int Stride() { return sizeof(Vertex); }

	public:
		// ������ ��ġ
		Vector3 position;

		// ������ ����
		Vector3 color;

		// ���� ���� �ؽ�ó ��ǥ
		Vector2 texCoord;
	};
}
